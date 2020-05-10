use certificate;
use dirs;
use error::Error;
use identity;
use rand::{RngCore, thread_rng, OsRng};
use std::collections::HashMap;
use std::fs::File;
use std::fs::OpenOptions;
use std::io::Seek;
use std::io::SeekFrom;
use std::io::{Read, Write};
use std::mem;
use toml;
use std::os::unix::fs::OpenOptionsExt;
use mtdparts::parse_mtd;

#[derive(Clone, Debug, Default, Deserialize, Serialize)]
pub struct Protocol {
    pub min_latency:            Option<u64>,
    pub max_tlps:               Option<u16>,
    pub max_rtos:               Option<u16>,
    pub reordering_threshold:   Option<u64>,
    pub time_loss_detection:    Option<bool>,
    pub min_tlp_timeout:        Option<u64>,
    pub min_rto_timeout:        Option<u64>,
    pub stream_rx_queue:        Option<u64>,
    pub stream_tx_queue:        Option<usize>,
    pub p2p:                    Option<bool>,
    pub local_port:             Option<u16>,
    pub tcp:                    Option<bool>,
}

#[derive(Deserialize, Serialize)]
pub struct AuthorizationToml {
    pub identity: String,
    pub resource: String,
}

#[derive(Deserialize, Serialize)]
pub struct NetworkConfigToml {
    address:    String,
    secret:     Option<String>,
}

#[derive(Deserialize, Serialize)]
pub struct PublisherConfigToml {
    shadow:  String,
    secret:  Option<String>,
}

#[derive(Clone, Debug, Deserialize, Serialize)]
pub struct Axon {
    pub path:   String,
    pub exec:   Vec<String>,
}

#[derive(Deserialize, Default, Serialize)]
pub struct ConfigToml {
    pub broker:    Option<Vec<String>>,
    pub secret:    Option<String>,
    pub principal: Option<String>,
    pub keepalive: Option<u16>,
    pub clock:     Option<String>,
    pub port:      Option<u16>,
    pub network:   Option<NetworkConfigToml>,
    pub publish:   Option<PublisherConfigToml>,
    pub names:     Option<HashMap<String, String>>,
    pub authorize: Option<Vec<AuthorizationToml>>,
    pub axons:     Option<Vec<Axon>>,
    pub protocol:  Option<Protocol>,
}


pub fn persistence_dir() -> std::path::PathBuf {
    #[cfg(feature = "openwrt")]
    {
        let gdir : std::path::PathBuf = "/etc/config/devguard/".into();
        std::fs::create_dir_all(&gdir).expect(&format!("cannot create {:?}", gdir));

        let cf = gdir.join("carrier.toml");
        let of =
            dirs::home_dir()
            .unwrap_or("/root/".into())
            .join(".devguard/carrier.toml");

        if !cf.exists() && of.exists() {
            match std::fs::copy(&of, &cf) {
                Ok(_) => {
                    log::warn!("config file {:?} was copied to new location {:?}", of, cf);
                },
                Err(_) => {
                    return of.parent().unwrap().into();
                }
            }
        }

        return gdir;
    }
    #[cfg(target_os = "android",)]
    let gdir =  {
        "/data/.devguard/".into()
    };
    #[cfg(not(target_os = "android",))]
    let gdir = {

        let gdir =
            dirs::home_dir()
            .unwrap_or("/root/".into())
            .join(".devguard/");
        gdir
    };
    std::fs::create_dir_all(&gdir).expect(&format!("cannot create {:?}", gdir));
    gdir
}

impl ConfigToml {
    fn secret(o: Option<&String>) -> Result<identity::Secret, Error> {
        if let Some(ref s) = o {
            if s.starts_with(":") {
                let mut fu_brwcheck: String;
                let mut s: Vec<&str> = s.split(":").collect();

                if s.get(1) == Some(&"mtdname") || s.get(1) == Some(&"mtdblock") {
                    if let Some(name) = s.get(2).map(|v| v.to_string()) {
                        let f = File::open("/proc/mtd").expect("open /proc/mtd");
                        let names = parse_mtd(f).expect("parsing /proc/mtd");
                        let dev = names.get(&name).expect(&format!("mtd partition {} not found", name));
                        fu_brwcheck = format!("/dev/{}", dev);

                        if s.get(1) == Some(&"mtdblock") {
                            if !fu_brwcheck.contains("mtdblock") {
                                fu_brwcheck = fu_brwcheck.replace("mtd", "mtdblock");
                            }
                        }
                        s[1] = "mtd";
                        s[2] = &fu_brwcheck;
                    }
                }

                if s.get(1) == Some(&"mtd") {
                    if let Some(mtd) = s.get(2) {
                        info!("reading secret from mtd {}", mtd);
                        let offset = s.get(3).and_then(|v| v.parse().ok()).unwrap_or(40);
                        let mut f = OpenOptions::new()
                            .read(true)
                            .write(true)
                            .open(mtd)
                            .expect(&format!("cannot open {}", mtd));
                        f.seek(SeekFrom::Start(offset))?;
                        let mut b = [0u8; 32];
                        f.read_exact(&mut b)?;

                        if b == [0xff; 32] || b == [0x0; 32] {
                            f.seek(SeekFrom::Start(offset))?;
                            firstgen_identity(&mut b);
                            f.write(&b)?;
                        }
                        return Ok(identity::Secret::from_array(b));
                    }
                } else if s.get(1) == Some(&"efi") {
                #[cfg(feature = "uefi")]
                {
                    info!("reading secret from UEFI");
                    let path = "/sys/firmware/efi/efivars/DevguardIdentity-287d44ea-82f4-11e9-bd4d-d0509993593e";

                    if std::fs::metadata(path).is_err() {
                        let mut b = [0u8; 68];
                        b[0] = 0x7;
                        firstgen_identity(&mut b[4..]);
                        let mut f = OpenOptions::new()
                            .write(true)
                            .create(true)
                            .open(path)
                            .expect(&format!("cannot open {}", path));
                        f.write(&b)?;
                    }

                    let mut f = OpenOptions::new()
                        .read(true)
                        .open(path)
                        .expect(&format!("cannot open {}", path));

                    let mut bb = [0u8; 68];
                    f.read_exact(&mut bb)?;
                    let mut b = [0u8; 32];
                    b.copy_from_slice(&bb[4..36]);

                    if let Some(xor) = s.get(2) {
                        let s2: identity::Secret = xor.parse()?;
                        let b2 = s2.as_bytes();
                        for i in 0..32 {
                            b[i] ^= b2[i];
                        }
                    }

                    return Ok(identity::Secret::from_array(b));
                }

                return Err(Error::NoSecrets);
            }}

            let s: identity::Secret = s.parse()?;
            return Ok(s);
        }
        Err(Error::NoSecrets)
    }

    fn publisher(&mut self, identity: identity::Identity) -> Result<Option<PublisherConfig>, Error> {

        let address = match (&self.publish, &self.network) {
            (Some(a), _)    => a.shadow.parse::<identity::Address>()?,
            (None, Some(a)) => a.address.parse::<identity::Address>()?,
            (None, None)    => panic!("publish config missing network="),
        };

        let mut auth = certificate::Authenticator::new(identity, address.clone());
        if let Some(authorize) = mem::replace(&mut self.authorize, None) {
            for i in authorize {
                match i.identity.parse() {
                    Ok(identity) => {
                        auth.allow(identity, vec![i.resource]);
                    }
                    Err(e) => {
                        warn!("in config: {}", e);
                    }
                }
            }
        }

        Ok(Some(PublisherConfig { address, auth }))
    }

    fn subscriber(&mut self) -> Result<Option<SubscriberConfig>, Error> {
        let address = match (&self.publish, &self.network) {
            (Some(a), _)    => a.shadow.parse::<identity::Address>()?,
            (None, Some(a)) => a.address.parse::<identity::Address>()?,
            (None, None)    => panic!("publish config missing network="),
        };

        Ok(Some(SubscriberConfig { address }))
    }

    fn names(&mut self) -> Result<HashMap<String, identity::Identity>, Error> {
        let mut r = HashMap::new();
        if let Some(names) = mem::replace(&mut self.names, None) {
            for (k, v) in names {
                r.insert(k, v.parse()?);
            }
        }
        Ok(r)
    }

    fn clock(&mut self) -> Result<ClockSource, Error> {
        let c = match &self.clock {
            None => return Ok(Default::default()),
            Some(v) => v,
        };

        if c.starts_with(":") {
            match c.as_str() {
                ":system" => {
                    return Ok(ClockSource::System);
                }
                _ => {
                    return Err(Error::InvalidClock(c.clone()));
                }
            }
        }

        return Ok(ClockSource::File(std::path::PathBuf::from(&c)));
    }

    fn broker(&mut self) -> Result<Vec<String>, Error> {
        Ok(self.broker.clone().unwrap_or(Config::default_brokers()))
    }
}

#[derive(Debug, Clone)]
pub enum ClockSource {
    File(std::path::PathBuf),
    System,
}

impl Default for ClockSource {
    fn default() -> Self {
        ClockSource::File(persistence_dir().join(".devguard/clock"))
    }
}

#[derive(Debug, Clone)]
pub struct Authorization {
    pub identity: identity::Identity,
    pub path:     String,
}

#[derive(Debug, Clone)]
pub struct PublisherConfig {
    pub address:    identity::Address,
    pub auth:       certificate::Authenticator,
}

#[derive(Debug, Clone)]
pub struct SubscriberConfig {
    pub address: identity::Address,
}

#[derive(Clone, Debug)]
pub struct Config {
    pub secret:    identity::Secret,
    pub principal: Option<identity::Secret>,
    pub keepalive: Option<u16>,
    pub publish:   Option<PublisherConfig>,
    pub axons:     Vec<Axon>,
    pub subscribe: Option<SubscriberConfig>,
    pub names:     HashMap<String, identity::Identity>,
    pub clock:     ClockSource,
    pub broker:    Vec<String>,
    pub port:      Option<u16>,
    pub protocol:  Protocol,
}

pub fn load() -> Result<Config, Error> {

    let filename =
        persistence_dir()
        .join("carrier.toml");

    let mut buffer = String::default();
    File::open(&filename)
        .expect(&format!(
            "cannot open config file {:?}. maybe run carrier setup",
            filename
        ))
        .read_to_string(&mut buffer)
        .expect(&format!("cannot read config file {:?}", filename));
    let mut config: ConfigToml = toml::from_str(&buffer).expect(&format!(
        "cannot open config file {:?}. maybe run carrier setup",
        filename
    ));

    let secret = ConfigToml::secret(config.secret.as_ref())?;
    Ok(Config {
        principal:  ConfigToml::secret(config.principal.as_ref()).ok(),
        publish:    config.publisher(secret.identity())?,
        secret,
        keepalive:  config.keepalive,
        subscribe:  config.subscriber()?,
        names:      config.names()?,
        clock:      config.clock()?,
        broker:     config.broker()?,
        port:       config.port,
        protocol:   config.protocol.unwrap_or_default(),
        axons:      config.axons.unwrap_or_default(),
    })
}

impl Config {
    pub fn resolve_identity<S: Into<String>>(&self, s: S) -> Result<identity::Identity, Error> {
        let s = s.into();
        if let Some(v) = self.names.get(&s) {
            return Ok(v.clone());
        }
        s.parse()
    }

    fn default_brokers() -> Vec<String> {
        vec!["4.carrier.devguard.io".into(), "x.carrier.devguard.io".into()]
    }

    pub fn new(secret: identity::Secret) -> Self {
        Self {
            secret,
            broker:     Self::default_brokers(),
            principal:  Default::default(),
            keepalive:  Default::default(),
            publish:    Default::default(),
            subscribe:  Default::default(),
            names:      Default::default(),
            clock:      Default::default(),
            port:       Default::default(),
            protocol:   Default::default(),
            axons:      Default::default(),
        }
    }
}

pub fn setup() -> Result<(), Error> {

    let persistence_dir = persistence_dir();
    std::fs::create_dir_all(&persistence_dir).expect(&format!("create dir {:?}", persistence_dir));
    let filename = persistence_dir.join("carrier.toml");

    let mut config: ConfigToml = if let Ok(mut f) = File::open(&filename) {
        let mut buffer = String::default();
        f.read_to_string(&mut buffer)
            .expect(&format!("cannot read config file {:?}", filename));
        toml::from_str(&buffer).expect(&format!(
            "cannot parse config file {:?}",
            filename
        ))
    } else {
        ConfigToml::default()
    };

    if config.secret.is_none() {
        config.secret = Some(identity::Secret::gen().to_string());
    }

    if config.publish.is_none() {
        let xsecret = identity::Secret::gen();
        config.network = Some(NetworkConfigToml{
            address: xsecret.address().to_string(),
            secret:  Some(xsecret.to_string()),
        });
    }

    let secret: identity::Secret = config.secret.as_ref().unwrap().parse().unwrap();
    println!("identity: {}", secret.identity());

    let shadow : identity::Address = config.network.as_ref().unwrap().address.parse().unwrap();
    println!("shadow: {}", shadow);
    if let Some(secret) = &config.publish.as_ref().unwrap().secret {
        let secret : identity::Secret = secret.parse().unwrap();
        println!("shadow-secret: {}", secret.to_string());
    }

    let s = toml::to_vec(&config).unwrap();



    let mut f = OpenOptions::new()
        .create(true)
        .write(true)
        .truncate(true)
        .mode(0o600)
        .open(&filename)
        .expect(&format!("cannot create config file {:?}", filename));
    f.write_all(&s)
        .expect(&format!("cannot write config file {:?}", filename));

    Ok(())
}


pub fn authorize(identity: identity::Identity, resource: String) -> Result<(), Error> {
    let filename =
        persistence_dir()
        .join("carrier.toml");

    let mut buffer = String::default();
    File::open(&filename)?
        .read_to_string(&mut buffer)?;

    let mut config: ConfigToml = match toml::from_str(&buffer) {
        Ok(v) => v,
        Err(e) => return Err(std::io::Error::new(std::io::ErrorKind::Other, format!("{:?}", e)).into()),
    };

    if  config.authorize.is_none() {
        config.authorize = Some(Vec::new());
    }

    for auth in config.authorize.as_ref().unwrap() {
        if auth.identity == identity.to_string() {
            println!("{} already authorized", identity);
            return Ok(())
        }
    }

    config.authorize.as_mut().unwrap().push(AuthorizationToml{
        identity: identity.to_string(),
        resource,
    });

    let s = toml::to_vec(&config).unwrap();


    // make sure the config still parses before writing
    match toml::from_slice::<ConfigToml>(&s) {
        Ok(v) => v,
        Err(e) => {
            println!("{}", String::from_utf8_lossy(&s));
            return Err(std::io::Error::new(std::io::ErrorKind::Other, e).into());
        }
    };


    let mut f = OpenOptions::new()
        .create(true)
        .write(true)
        .truncate(true)
        .mode(0o600)
        .open(&filename)?;
    f.write_all(&s)?;

    Ok(())
}


pub fn deauthorize(identity: identity::Identity) -> Result<(), Error> {
    let filename =
        persistence_dir()
        .join("carrier.toml");

    let mut buffer = String::default();
    File::open(&filename)?
        .read_to_string(&mut buffer)?;

    let mut config: ConfigToml = match toml::from_str(&buffer) {
        Ok(v) => v,
        Err(e) => return Err(std::io::Error::new(std::io::ErrorKind::Other, e).into()),
    };

    if  config.authorize.is_none() {
        config.authorize = Some(Vec::new());
    }

    let mut nur = Vec::new();
    for auth in std::mem::replace(&mut config.authorize, None).unwrap() {
        if auth.identity != identity.to_string() {
            nur.push(auth);
        }
    }
    config.authorize = Some(nur);

    let s = match toml::to_vec(&config) {
        Ok(v) => v,
        Err(e) => return Err(std::io::Error::new(std::io::ErrorKind::Other, e).into()),
    };

    // make sure the config still parses before writing
    match toml::from_slice::<ConfigToml>(&s) {
        Ok(v) => v,
        Err(e) => return Err(std::io::Error::new(std::io::ErrorKind::Other, e).into()),
    };


    let mut f = OpenOptions::new()
        .create(true)
        .write(true)
        .truncate(true)
        .mode(0o600)
        .open(&filename)?;
    f.write_all(&s)?;

    Ok(())
}




pub static mut IDENTITY_GENERATOR: Option<Box<Fn(&mut[u8])>> = None;

fn firstgen_identity(b: &mut [u8]) {
    unsafe {
        if let Some(cb) = &mut IDENTITY_GENERATOR {
            cb(b);
        }
    }

    if b == [0xff; 32] || b == [0x0; 32] {
        panic!("secret file is zero and IDENTITY_GENERATOR is not set or not working. check your system specific carrier manual why identity might be missing");
    }
}

pub fn default_identity_generator(b: &mut [u8]) {
    use error;
    let mut err = error::ZZError::new();
    unsafe {
        super::zz::carrier_rand::rand(err.as_mut_ptr(), error::ZERR_TAIL, b.as_mut_ptr(), b.len());
    }
    err.check().unwrap();
}
