#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#ifndef ZZ_EXPORT_HEADER__err
#define ZZ_EXPORT_HEADER__err
struct slice_slice_Slice_t;
typedef struct slice_slice_Slice_t slice_slice_Slice;
struct err_Err_t;
typedef struct err_Err_t err_Err;
struct string_String_t;
typedef struct string_String_t string_String;
struct slice_mut_slice_MutSlice_t;
typedef struct slice_mut_slice_MutSlice_t slice_mut_slice_MutSlice;
struct slice_slice_Slice_t;
typedef struct slice_slice_Slice_t slice_slice_Slice;
struct slice_mut_slice_MutSlice_t;
typedef struct slice_mut_slice_MutSlice_t slice_mut_slice_MutSlice;
struct string_String_t;
typedef struct string_String_t string_String;
struct err_Err_t;
typedef struct err_Err_t err_Err;
slice_slice_Slice  const * slice_slice_borrow (slice_slice_Slice const *  const  self);
#include <stddef.h>
void err_backtrace (err_Err*  const  self, uintptr_t const  tail, char const *  const  file, char const *  const  scope, uintptr_t const  line);
#include <stdio.h>
#include <stdlib.h>
void err_abort (err_Err*  const  self, uintptr_t const  tail, char const *  const  file, char const *  const  scope, uintptr_t const  line);

#ifndef ZZ_EXPORT_err_OutOfTail
#define ZZ_EXPORT_err_OutOfTail
extern const __attribute__ ((unused)) size_t err_OutOfTail;

#endif
uintptr_t string_space (string_String const *  const  self, uintptr_t const  tail);
char  const * symbols_nameof (uintptr_t const  s);
void slice_mut_slice_make (slice_mut_slice_MutSlice*  const  self, uint8_t*  const  mem, uintptr_t const  size);
bool string_fgets (string_String*  const  self, uintptr_t const  tail, FILE*  const  stream);
#include <string.h>
void string_clear (string_String*  const  self, uintptr_t const  tail);
void err_make (err_Err*  const  self, uintptr_t const  tail);
bool string_push (string_String*  const  self, uintptr_t const  t, char const  cstr);
char  const * symbols_nameof_checked (uintptr_t const  s);
#include <stdarg.h>
void err_fail (err_Err*  const  self, uintptr_t const  tail, uintptr_t const  e, char const *  const  file, char const *  const  scope, uintptr_t const  line, char const *  const  fmt, ...);

#ifndef ZZ_EXPORT_slice_slice_Slice
#define ZZ_EXPORT_slice_slice_Slice
struct slice_slice_Slice_t {
   uintptr_t size ;
   uint8_t const *  mem ;
}
;
const size_t sizeof_slice_slice_Slice;

#endif

#ifndef ZZ_EXPORT_slice_mut_slice_MutSlice
#define ZZ_EXPORT_slice_mut_slice_MutSlice
struct slice_mut_slice_MutSlice_t {
   slice_slice_Slice slice ;
   uintptr_t at ;
}
;
const size_t sizeof_slice_mut_slice_MutSlice;

#endif
bool string_ends_with_cstr (string_String const *  const  self, uintptr_t const  tail, char const *  const  a);
int string_vformat (string_String*  const  self, uintptr_t const  tail, char const *  const  fmt, va_list args);
void string_make (string_String*  const  self, uintptr_t const  tail);
void err_to_str (err_Err const *  const  self, char*  const  dest, uintptr_t const  dest_len);
void string_append_bytes (string_String*  const  self, uintptr_t const  t, uint8_t const *  const  bytes, uintptr_t inlen);
void string_append (string_String*  const  self, uintptr_t const  t, string_String const *  const  other, uintptr_t const  t2);
int string_format (string_String*  const  self, uintptr_t const  tail, char const *  const  fmt, ...);
slice_mut_slice_MutSlice  const * slice_mut_slice_borrow (slice_mut_slice_MutSlice*  const  self);
bool slice_slice_eq_bytes (slice_slice_Slice const *  const  self, uint8_t const *  const  other, uintptr_t const  othersize);
void err_eprintf (err_Err*  const  self, uintptr_t const  tail, FILE*  const  out);
bool slice_mut_slice_append_cstr (slice_mut_slice_MutSlice*  const  self, char const *  const  b);
bool string_pop (string_String*  const  self, uintptr_t const  t);
bool slice_mut_slice_push32 (slice_mut_slice_MutSlice*  const  self, uint32_t const  b);
bool slice_slice_eq (slice_slice_Slice const *  const  self, slice_slice_Slice const *  const  other);
void log_error (char const *  const  module, char const *  const  fmt, ...);
void err_elog (err_Err*  const  self, uintptr_t const  tail);

#ifndef ZZ_EXPORT_err_NotImplemented
#define ZZ_EXPORT_err_NotImplemented
extern const __attribute__ ((unused)) size_t err_NotImplemented;

#endif

#ifndef ZZ_EXPORT_string_String
#define ZZ_EXPORT_string_String
struct string_String_t {
   uintptr_t len ;
   char mem[] ;
}
;
size_t sizeof_string_String(size_t tail);

#endif

#ifndef ZZ_EXPORT_err_Err
#define ZZ_EXPORT_err_Err
struct err_Err_t {
   uintptr_t error ;
   int system ;
   string_String trace ;
}
;
size_t sizeof_err_Err(size_t tail);

#endif
slice_mut_slice_MutSlice string_append_slice (string_String*  const  self, uintptr_t const  tail);
char  const * string_cstr (string_String const *  const  self);
void err_panic (char const *  const  file, char const *  const  scope, uintptr_t const  line, char const *  const  fmt, ...);
bool string_split (string_String const *  const  self, uintptr_t const  tail, char const  token, uintptr_t*  const  iterator, string_String*  const  other, uintptr_t const  tail2);
slice_slice_Slice string_slice (string_String*  const  self, uintptr_t const  tail);

#ifndef ZZ_EXPORT_err_InvalidArgument
#define ZZ_EXPORT_err_InvalidArgument
extern const __attribute__ ((unused)) size_t err_InvalidArgument;

#endif

#ifndef ZZ_EXPORT_err_SystemError
#define ZZ_EXPORT_err_SystemError
extern const __attribute__ ((unused)) size_t err_SystemError;

#endif
bool string_eq_cstr (string_String const *  const  self, uintptr_t const  tail, char const *  const  b);
#include <errno.h>
uintptr_t string_slen (string_String const *  const  self);
bool slice_mut_slice_push16 (slice_mut_slice_MutSlice*  const  self, uint16_t const  b);
bool string_starts_with_cstr (string_String const *  const  self, uintptr_t const  tail, char const *  const  a);
void err_fail_with_errno (err_Err*  const  self, uintptr_t const  tail, char const *  const  file, char const *  const  scope, uintptr_t const  line, char const *  const  fmt, ...);
uint8_t * slice_mut_slice_mem (slice_mut_slice_MutSlice*  const  self);
void string_substr (string_String const *  const  self, uintptr_t const  tail, uintptr_t const  from, uintptr_t size, string_String*  const  other, uintptr_t const  tail2);
bool slice_mut_slice_append_bytes (slice_mut_slice_MutSlice*  const  self, uint8_t const *  const  b, uintptr_t const  l);
bool err_check (err_Err*  const  self, uintptr_t const  tail, char const *  const  file, char const *  const  scope, uintptr_t const  line);
void err_backtrace (err_Err*  const  self, uintptr_t const  tail, char const *  const  file, char const *  const  scope, uintptr_t const  line);
void slice_slice_make (slice_slice_Slice*  const  self, uint8_t const *  const  mem, uintptr_t const  size);
void string_append_cstr (string_String*  const  self, uintptr_t const  t, char const *  const  cstr);
bool slice_mut_slice_push64 (slice_mut_slice_MutSlice*  const  self, uint64_t const  b);
void err_assert (bool const  a, char const *  const  file, char const *  const  scope, uintptr_t const  line);
void err_assert2 (bool const  a, char const *  const  file, char const *  const  scope, uintptr_t const  line, char const *  const  fmt, ...);
bool slice_slice_eq_cstr (slice_slice_Slice const *  const  self, char const *  const  other);
void err_assert_safe (void const *  const  a, char const *  const  file, char const *  const  scope, uintptr_t const  line);
bool slice_mut_slice_push (slice_mut_slice_MutSlice*  const  self, uint8_t const  b);
#endif