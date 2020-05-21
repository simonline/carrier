
#include <assert.h>
#include <node_api.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "zz/carrier/net_tcp_server.h"

napi_value js_io_wait(napi_env env, napi_callback_info info);
napi_value js_string_append_bytes(napi_env env, napi_callback_info info);
napi_value js_io_read_slice(napi_env env, napi_callback_info info);
napi_value js_string_slen(napi_env env, napi_callback_info info);
napi_value js_string_slice(napi_env env, napi_callback_info info);
napi_value js_io_select(napi_env env, napi_callback_info info);
napi_value js_slice_slice_borrow(napi_env env, napi_callback_info info);
napi_value js_net_address_none(napi_env env, napi_callback_info info);
napi_value js_slice_mut_slice_mem(napi_env env, napi_callback_info info);
napi_value js_io_read_bytes(napi_env env, napi_callback_info info);
napi_value js_net_address_from_string(napi_env env, napi_callback_info info);
napi_value js_net_address_ip_to_string(napi_env env, napi_callback_info info);
napi_value js_io_write_bytes(napi_env env, napi_callback_info info);
napi_value js_net_address_set_port(napi_env env, napi_callback_info info);
napi_value js_slice_mut_slice_append_cstr(napi_env env, napi_callback_info info);
napi_value js_string_clear(napi_env env, napi_callback_info info);
napi_value js_string_cstr(napi_env env, napi_callback_info info);
napi_value js_string_append_slice(napi_env env, napi_callback_info info);
napi_value js_slice_mut_slice_borrow(napi_env env, napi_callback_info info);
napi_value js_slice_mut_slice_make(napi_env env, napi_callback_info info);
napi_value js_net_address_get_port(napi_env env, napi_callback_info info);
napi_value js_slice_mut_slice_push64(napi_env env, napi_callback_info info);
napi_value js_slice_slice_make(napi_env env, napi_callback_info info);
napi_value js_string_starts_with_cstr(napi_env env, napi_callback_info info);
napi_value js_err_eprintf(napi_env env, napi_callback_info info);
napi_value js_string_eq_cstr(napi_env env, napi_callback_info info);
napi_value js_net_tcp_send(napi_env env, napi_callback_info info);
napi_value js_slice_slice_eq_cstr(napi_env env, napi_callback_info info);
napi_value js_err_check(napi_env env, napi_callback_info info);
napi_value js_slice_mut_slice_push32(napi_env env, napi_callback_info info);
napi_value js_string_append_cstr(napi_env env, napi_callback_info info);
napi_value js_net_tcp_close(napi_env env, napi_callback_info info);
napi_value js_err_fail(napi_env env, napi_callback_info info);
napi_value js_string_format(napi_env env, napi_callback_info info);
napi_value js_slice_slice_eq_bytes(napi_env env, napi_callback_info info);
napi_value js_net_address_from_str_ipv4(napi_env env, napi_callback_info info);
napi_value js_err_fail_with_errno(napi_env env, napi_callback_info info);
napi_value js_io_timeout(napi_env env, napi_callback_info info);
napi_value js_net_udp_close(napi_env env, napi_callback_info info);
napi_value js_io_write(napi_env env, napi_callback_info info);
napi_value js_time_to_seconds(napi_env env, napi_callback_info info);
napi_value js_net_udp(napi_env env, napi_callback_info info);
napi_value js_err_backtrace(napi_env env, napi_callback_info info);
napi_value js_err_fail_with_errno(napi_env env, napi_callback_info info);
napi_value js_symbols_nameof_checked(napi_env env, napi_callback_info info);
napi_value js_symbols_nameof(napi_env env, napi_callback_info info);
napi_value js_err_fail(napi_env env, napi_callback_info info);
napi_value js_io_select(napi_env env, napi_callback_info info);
napi_value js_net_tcp_server_accept(napi_env env, napi_callback_info info);
napi_value js_io_await(napi_env env, napi_callback_info info);
napi_value js_net_address_get_ip(napi_env env, napi_callback_info info);
napi_value js_net_address_set_ip(napi_env env, napi_callback_info info);
napi_value js_string_push(napi_env env, napi_callback_info info);
napi_value js_net_tcp_recv(napi_env env, napi_callback_info info);
napi_value js_string_space(napi_env env, napi_callback_info info);
napi_value js_io_wake(napi_env env, napi_callback_info info);
napi_value js_net_address_from_str(napi_env env, napi_callback_info info);
napi_value js_net_tcp_server(napi_env env, napi_callback_info info);
napi_value js_slice_mut_slice_push16(napi_env env, napi_callback_info info);
napi_value js_string_vformat(napi_env env, napi_callback_info info);
napi_value js_slice_mut_slice_push(napi_env env, napi_callback_info info);
napi_value js_net_tcp_server_os_new(napi_env env, napi_callback_info info);
napi_value js_err_abort(napi_env env, napi_callback_info info);
napi_value js_err_elog(napi_env env, napi_callback_info info);
napi_value js_string_pop(napi_env env, napi_callback_info info);
napi_value js_string_fgets(napi_env env, napi_callback_info info);
napi_value js_net_udp_sendto(napi_env env, napi_callback_info info);
napi_value js_io_valid(napi_env env, napi_callback_info info);
napi_value js_net_address_eq(napi_env env, napi_callback_info info);
napi_value js_io_readline(napi_env env, napi_callback_info info);
napi_value js_slice_mut_slice_append_bytes(napi_env env, napi_callback_info info);
napi_value js_io_channel(napi_env env, napi_callback_info info);
napi_value js_string_substr(napi_env env, napi_callback_info info);
napi_value js_err_make(napi_env env, napi_callback_info info);
napi_value js_io_close(napi_env env, napi_callback_info info);
napi_value js_time_more_than(napi_env env, napi_callback_info info);
napi_value js_slice_slice_eq(napi_env env, napi_callback_info info);
napi_value js_net_address_to_string(napi_env env, napi_callback_info info);
napi_value js_io_write_cstr(napi_env env, napi_callback_info info);
napi_value js_err_to_str(napi_env env, napi_callback_info info);
napi_value js_string_split(napi_env env, napi_callback_info info);
napi_value js_string_ends_with_cstr(napi_env env, napi_callback_info info);
napi_value js_string_append(napi_env env, napi_callback_info info);
napi_value js_net_udp_recvfrom(napi_env env, napi_callback_info info);
napi_value js_time_to_millis(napi_env env, napi_callback_info info);
napi_value js_net_address_from_str_ipv6(napi_env env, napi_callback_info info);
napi_value js_net_address_valid(napi_env env, napi_callback_info info);
napi_value js_net_address_from_cstr(napi_env env, napi_callback_info info);
napi_value js_net_tcp_server_close(napi_env env, napi_callback_info info);
napi_value js_string_make(napi_env env, napi_callback_info info);
napi_value js_io_read(napi_env env, napi_callback_info info);


napi_value jsGet_net_tcp_server_Server_ctx(napi_env env, napi_callback_info info) {
  napi_status status;

  napi_value jsthis;
  status = napi_get_cb_info(env, info, 0, 0, &jsthis, 0);
  assert(status == napi_ok);

  void *mem;
  status = napi_unwrap(env, jsthis, &mem);
  assert(status == napi_ok);
  mem += sizeof(size_t);
  net_tcp_server_Server * obj = (net_tcp_server_Server*)mem;

  napi_value value;

  assert(status == napi_ok);
  return value;
}


napi_value jsGet_net_tcp_server_Server_impl_close(napi_env env, napi_callback_info info) {
  napi_status status;

  napi_value jsthis;
  status = napi_get_cb_info(env, info, 0, 0, &jsthis, 0);
  assert(status == napi_ok);

  void *mem;
  status = napi_unwrap(env, jsthis, &mem);
  assert(status == napi_ok);
  mem += sizeof(size_t);
  net_tcp_server_Server * obj = (net_tcp_server_Server*)mem;

  napi_value value;

  assert(status == napi_ok);
  return value;
}


napi_value jsGet_net_tcp_server_Server_impl_accept(napi_env env, napi_callback_info info) {
  napi_status status;

  napi_value jsthis;
  status = napi_get_cb_info(env, info, 0, 0, &jsthis, 0);
  assert(status == napi_ok);

  void *mem;
  status = napi_unwrap(env, jsthis, &mem);
  assert(status == napi_ok);
  mem += sizeof(size_t);
  net_tcp_server_Server * obj = (net_tcp_server_Server*)mem;

  napi_value value;

  assert(status == napi_ok);
  return value;
}


void js_delete_net_tcp_server_Server(napi_env env, void *obj, void*hint) {
    free(obj);
}
napi_value js_new_net_tcp_server_Server(napi_env env, napi_callback_info info) {
    napi_status status;

    napi_value target;
    status = napi_get_new_target(env, info, &target);
    assert(status == napi_ok);
    bool is_constructor = target != 0;

    assert (is_constructor);

    size_t argc = 1;
    napi_value args[1];
    napi_value jsthis;
    status = napi_get_cb_info(env, info, &argc, args, &jsthis, 0);
    assert(status == napi_ok);

    size_t tail = 0;
    napi_valuetype valuetype;
    status = napi_typeof(env, args[0], &valuetype);
    assert(status == napi_ok);

    if (valuetype != napi_undefined) {
        status = napi_get_value_uint32(env, args[0], (uint32_t*)&tail);
        assert(status == napi_ok);
    }
    
    void *obj = malloc(sizeof(size_t) + sizeof_net_tcp_server_Server);
    memset(obj, 0, sizeof(size_t) + sizeof_net_tcp_server_Server);

    *((size_t *)obj) = tail;

    status = napi_wrap(env,
            jsthis,
            obj,
            js_delete_net_tcp_server_Server, // destructor
            0,  // finalize_hint
            0
    );
    assert(status == napi_ok);
    return jsthis;

}

void js_register_net_tcp_server_Server (napi_env env, napi_value exports) {
    napi_property_descriptor properties[] = {
        { "tcp_server", 0, js_net_tcp_server, 0, 0, 0, napi_default, 0 },
        { "accept", 0, js_net_tcp_server_accept, 0, 0, 0, napi_default, 0 },
        { "close", 0, js_net_tcp_server_close, 0, 0, 0, napi_default, 0 },
        { "ctx", 0, 0, jsGet_net_tcp_server_Server_ctx, 0, 0, napi_default, 0},
        { "impl_close", 0, 0, jsGet_net_tcp_server_Server_impl_close, 0, 0, napi_default, 0},
        { "impl_accept", 0, 0, jsGet_net_tcp_server_Server_impl_accept, 0, 0, napi_default, 0},
    };
    napi_value cc;
    napi_status status = napi_define_class(env, "Server", NAPI_AUTO_LENGTH, js_new_net_tcp_server_Server, 0, 6, properties, &cc);
    assert(status == napi_ok);
    status = napi_set_named_property(env, exports, "Server", cc);
    assert(status == napi_ok);
}



napi_value js_net_tcp_server_accept(napi_env env, napi_callback_info info) {
    napi_status status;

    size_t argc = 16;
    napi_value argv[16];
    napi_value jsthis;
    status = napi_get_cb_info(env, info, &argc, argv, &jsthis, 0);
    assert(argc < 16);
    assert(status == napi_ok);



                    void * thismem;
                    status = napi_unwrap(env, jsthis, &thismem);
                    assert(status == napi_ok);
                    size_t local_0_tail = (*(size_t*)thismem);
                    void * local_0 = thismem + sizeof(size_t);

                
                    if (0 >= argc) {
                        napi_throw_error(env, 0, "call argument count mismatch");
                        return 0;
                    }
                
    err_Err * local_1;

    void * tttt_local_1 = 0;
    size_t local_1_tail = 0;
    status = napi_unwrap(env, argv[0], &tttt_local_1);
    if (tttt_local_1 == 0 || status != napi_ok) {
        local_1 = 0;
    } else {
        local_1_tail = *((size_t*)tttt_local_1);
        local_1 = tttt_local_1 + sizeof(size_t*);
    }
    
                    if (status != napi_ok) {
                        napi_throw_type_error(env, 0, "1'th arg requires type ::err::Err*+et");
                        return 0;
                    }
                
                    if (1 >= argc) {
                        napi_throw_error(env, 0, "call argument count mismatch");
                        return 0;
                    }
                
    net_tcp_Socket * local_3;

    void * tttt_local_3 = 0;
    size_t local_3_tail = 0;
    status = napi_unwrap(env, argv[1], &tttt_local_3);
    if (tttt_local_3 == 0 || status != napi_ok) {
        local_3 = 0;
    } else {
        local_3_tail = *((size_t*)tttt_local_3);
        local_3 = tttt_local_3 + sizeof(size_t*);
    }
    
                    if (status != napi_ok) {
                        napi_throw_type_error(env, 0, "2'th arg requires type ::net::tcp::Socket*");
                        return 0;
                    }
                    napi_value jsreturn = 0;
    io_Result  frrr = net_tcp_server_accept( local_0, local_1, local_1_tail, local_3);
    assert(status == napi_ok);
    return jsreturn;
}


napi_value js_net_tcp_server_os_new(napi_env env, napi_callback_info info) {
    napi_status status;

    size_t argc = 16;
    napi_value argv[16];
    napi_value jsthis;
    status = napi_get_cb_info(env, info, &argc, argv, &jsthis, 0);
    assert(argc < 16);
    assert(status == napi_ok);



                    if (0 >= argc) {
                        napi_throw_error(env, 0, "call argument count mismatch");
                        return 0;
                    }
                
    net_Engine * local_0;

    void * tttt_local_0 = 0;
    size_t local_0_tail = 0;
    status = napi_unwrap(env, argv[0], &tttt_local_0);
    if (tttt_local_0 == 0 || status != napi_ok) {
        local_0 = 0;
    } else {
        local_0_tail = *((size_t*)tttt_local_0);
        local_0 = tttt_local_0 + sizeof(size_t*);
    }
    
                    if (status != napi_ok) {
                        napi_throw_type_error(env, 0, "1'th arg requires type ::net::Engine*");
                        return 0;
                    }
                
                    if (1 >= argc) {
                        napi_throw_error(env, 0, "call argument count mismatch");
                        return 0;
                    }
                
    err_Err * local_1;

    void * tttt_local_1 = 0;
    size_t local_1_tail = 0;
    status = napi_unwrap(env, argv[1], &tttt_local_1);
    if (tttt_local_1 == 0 || status != napi_ok) {
        local_1 = 0;
    } else {
        local_1_tail = *((size_t*)tttt_local_1);
        local_1 = tttt_local_1 + sizeof(size_t*);
    }
    
                    if (status != napi_ok) {
                        napi_throw_type_error(env, 0, "2'th arg requires type ::err::Err*+et");
                        return 0;
                    }
                
                    if (2 >= argc) {
                        napi_throw_error(env, 0, "call argument count mismatch");
                        return 0;
                    }
                
    net_address_Address * local_3;

    void * tttt_local_3 = 0;
    size_t local_3_tail = 0;
    status = napi_unwrap(env, argv[2], &tttt_local_3);
    if (tttt_local_3 == 0 || status != napi_ok) {
        local_3 = 0;
    } else {
        local_3_tail = *((size_t*)tttt_local_3);
        local_3 = tttt_local_3 + sizeof(size_t*);
    }
    
                    if (status != napi_ok) {
                        napi_throw_type_error(env, 0, "3'th arg requires type ::net::address::Address*");
                        return 0;
                    }
                
                    if (3 >= argc) {
                        napi_throw_error(env, 0, "call argument count mismatch");
                        return 0;
                    }
                
    io_Async * local_4;

    void * tttt_local_4 = 0;
    size_t local_4_tail = 0;
    status = napi_unwrap(env, argv[3], &tttt_local_4);
    if (tttt_local_4 == 0 || status != napi_ok) {
        local_4 = 0;
    } else {
        local_4_tail = *((size_t*)tttt_local_4);
        local_4 = tttt_local_4 + sizeof(size_t*);
    }
    
                    if (status != napi_ok) {
                        napi_throw_type_error(env, 0, "4'th arg requires type ::io::Async*");
                        return 0;
                    }
                    napi_value jsreturn = 0;
    net_tcp_server_Server  frrr = net_tcp_server_os_new( local_0, local_1, local_1_tail, local_3, local_4);
    assert(status == napi_ok);
    return jsreturn;
}


napi_value js_net_tcp_server_close(napi_env env, napi_callback_info info) {
    napi_status status;

    size_t argc = 16;
    napi_value argv[16];
    napi_value jsthis;
    status = napi_get_cb_info(env, info, &argc, argv, &jsthis, 0);
    assert(argc < 16);
    assert(status == napi_ok);



                    void * thismem;
                    status = napi_unwrap(env, jsthis, &thismem);
                    assert(status == napi_ok);
                    size_t local_0_tail = (*(size_t*)thismem);
                    void * local_0 = thismem + sizeof(size_t);

                    napi_value jsreturn = 0;
    net_tcp_server_close( local_0);
    return jsreturn;
}


napi_value js_net_tcp_server_Init(napi_env env, napi_value exports)
{
    js_register_net_tcp_server_Server(env, exports);
    napi_value ff;
    napi_status status;
    status = napi_create_function(env, "accept", NAPI_AUTO_LENGTH, js_net_tcp_server_accept, 0, &ff);
    assert(status == napi_ok);
    status = napi_set_named_property(env, exports, "accept", ff);
    assert(status == napi_ok);
    status = napi_create_function(env, "os_new", NAPI_AUTO_LENGTH, js_net_tcp_server_os_new, 0, &ff);
    assert(status == napi_ok);
    status = napi_set_named_property(env, exports, "os_new", ff);
    assert(status == napi_ok);
    status = napi_create_function(env, "close", NAPI_AUTO_LENGTH, js_net_tcp_server_close, 0, &ff);
    assert(status == napi_ok);
    status = napi_set_named_property(env, exports, "close", ff);
    assert(status == napi_ok);
    return exports;
}