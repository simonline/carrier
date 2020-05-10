use std::fmt;
use std::iter::Iterator;
use error;
use super::zz::{
    slice_mut_slice as mut_slice,
    slice_slice as slice,
    hpack_encoder,
    hpack_decoder,
};

#[derive(Default, Clone)]
pub struct Headers {
    f: Vec<(Vec<u8>, Vec<u8>)>,
}

impl Headers {
    pub fn new() -> Self {
        Self::default()
    }

    pub fn ok() -> Self {
        Self {
            f: vec![(":status".into(), "200".into())],
        }
    }

    pub fn ok_proto() -> Self {
        Self {
            f: vec![
                (":status".into(), "200".into()),
                ("content-type".into(), "application/protobuf".into()),
            ],
        }
    }

    pub fn with_error<P: Into<Vec<u8>>>(status: u32, p: P) -> Self {
        Self {
            f: vec![
                (":status".into(), format!("{}", status).as_bytes().to_vec()),
                (":error".into(), p.into()),
            ],
        }
    }

    pub fn with_path<P: Into<Vec<u8>>>(p: P) -> Self {
        Self {
            f: vec![(":path".into(), p.into())],
        }
    }

    pub fn with<K: Into<Vec<u8>>, V: Into<Vec<u8>>>(k: K, v: V) -> Self {
        Self {
            f: vec![(k.into(), v.into())],
        }
    }

    pub fn into_inner(self) -> Vec<(Vec<u8>, Vec<u8>)> {
        self.f
    }

    pub fn get(&self, key: &[u8]) -> Option<&[u8]> {
        let mut val = None;
        for header in &self.f {
            if header.0 == key {
                val = Some(header.1.as_slice());
            }
        }
        val
    }

    pub fn path(&self) -> Option<&[u8]> {
        let mut path = None;
        for header in &self.f {
            if header.0 == b":path" {
                path = Some(header.1.as_slice());
            }
        }
        path
    }

    pub fn status(&self) -> Option<u32> {
        let mut status = None;
        for header in &self.f {
            if header.0 == b":status" {
                status = String::from_utf8_lossy(&header.1.as_slice()).parse().ok();
            }
        }
        status
    }

    pub fn add(&mut self, k: Vec<u8>, v: Vec<u8>) {
        self.f.push((k, v));
    }

    pub fn and(mut self, k: Vec<u8>, v: Vec<u8>) -> Self {
        self.f.push((k, v));
        self
    }

    pub fn encode(&self) -> Vec<u8> {
        let mut err = error::ZZError::new();

        let mut mem     = vec![0;2000];
        let mut slice   = mut_slice::rsMutSlice::new();
        unsafe {
            mut_slice::make(slice._self_mut(), mem.as_mut_ptr(), mem.len());
        }

        let mut at = 0;
        for (k,v) in &self.f {
            unsafe{
                hpack_encoder::encode(
                    slice._self_mut(),

                    err.as_mut_ptr(),
                    error::ZERR_TAIL,

                    k.as_ptr(),
                    k.len(),

                    v.as_ptr(),
                    v.len()
                );
                at = slice.inner.at;
            };

            err.check().unwrap();
        }
        mem.truncate(at);
        mem
    }

    pub fn decode(b: &[u8]) -> Result<Self, error::Error> {
        let mut nu = Self::default();
        let mut err = error::ZZError::new();

        let mut slice = slice::rsSlice::new();
        unsafe {
            slice::make(slice._self_mut(), b.as_ptr(), b.len());
        }

        let mut decoder = hpack_decoder::rsIterator::new();
        unsafe {
            hpack_decoder::decode(decoder._self_mut(), slice._self());
        }

        unsafe {
            while hpack_decoder::next(decoder._self_mut(), err.as_mut_ptr(), error::ZERR_TAIL)
            {
                let k = std::slice::from_raw_parts(decoder.key.mem, decoder.key.size).to_vec();
                let v = std::slice::from_raw_parts(decoder.val.mem, decoder.val.size).to_vec();
                nu.f.push((k, v));
            }
        }


        err.check()?;

        Ok(nu)
    }

    pub fn iter<'a>(&'a self) -> impl Iterator<Item = (&[u8], &[u8])> + 'a {
        self.f.iter().map(|v| (v.0.as_slice(), v.1.as_slice()))
    }
}

impl fmt::Debug for Headers {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "[")?;
        for (k, v) in &self.f {
            write!(f, "{} = {}, ", String::from_utf8_lossy(&k), String::from_utf8_lossy(&v))?;
        }
        write!(f, "]")?;
        Ok(())
    }
}



