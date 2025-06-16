#pragma once

#ifndef __ywlib_export
#define __ywlib_dummy(d, ...) d
#define __ywlib_exportc \
  extern "C" {           \
  static_assert(true)
#define __ywlib_exportcend \
  }                         \
  static_assert(true)
#else
#define __ywlib_dummy(d, ...) __VA_ARGS__
#define __ywlib_exportc \
  export extern "C" {    \
    static_assert(true)
#define __ywlib_exportcend \
  }                         \
  static_assert(true)
#endif

#define _ACRTIMP
#define _ALLOW_COMPILER_AND_STL_VERSION_MISMATCH
#define _CONSTEXPR20 constexpr
#define _CRT_ASSERT 2
#define _CRT_BLOCK 2
#define _CRT_GUARDOVERFLOW
#define _CRT_PACKING 8
#define _CRT_SATELLITE_1
#define _CRT_SATELLITE_CODECVT_IDS
#define _CRT_SATELLITE_CODECVT_IDS_NOIMPORT
#define _CRTIMP2
#define _CRTIMP2_PURE
#define _HAS_CXX17 1
#define _HAS_CXX20 1
#define _HAS_CXX23 1
#define _HAS_EXCEPTIONS 1
#define _MRTIMP2
#define _MSVC_CONSTEXPR [[msvc::constexpr]]
#define _MSVC_LIFETIMEBOUND [[msvc::lifetimebound]]
#define _NODISCARD [[nodiscard]]
#define _PGLOBAL
#define _RPTF0(rptno, msg)

#define __CLR_OR_THIS_CALL
#define __CLRCALL_OR_CDECL __cdecl
#define __CLRCALL_PURE_OR_CDECL __cdecl
#define __CRTDECL __cdecl

#define _Analysis_assume_(...)
#define _Deref_post_opt_valid_
#define _Guarded_by_(...)
#define _In_
#define _In_opt_
#define _In_range_(...)
#define _In_reads_(...)
#define _Inout_
#define _Inout_opt_
#define _In_opt_z_
#define _In_z_
#define _Out_
#define _Out_opt_
#define _Out_writes_(...)
#define _Out_writes_all_(...)
#define _Out_writes_bytes_(...)
#define _Out_writes_opt_(...)
#define _Out_writes_z_(...)
#define _Post_equal_to_(...)
#define _Post_readable_size_(...)
#define _Post_satisfies_(...)
#define _Pre_satisfies_(...)
#define _Ret_range_(...)
#define _Ret_z_
#define _Success_(...)
#define _When_(...)

#define _UPPER 0x01
#define _LOWER 0x02
#define _DIGIT 0x04
#define _SPACE 0x08
#define _PUNCT 0x10
#define _CONTROL 0x20
#define _BLANK 0x40
#define _HEX 0x80

#define stdin (::__acrt_iob_func(0))
#define stdout (::__acrt_iob_func(1))
#define stderr (::__acrt_iob_func(2))

#define _CRT_INTERNAL_LOCAL_PRINTF_OPTIONS (*::__local_stdio_printf_options())
#define _CRT_INTERNAL_LOCAL_SCANF_OPTIONS (*::__local_stdio_scanf_options())
// #define _CRT_INTERNAL_PRINTF_LEGACY_VSPRINTF_NULL_TERMINATION (1ULL << 0)
#define _CRT_INTERNAL_PRINTF_STANDARD_SNPRINTF_BEHAVIOR (1ULL << 1)
// #define _CRT_INTERNAL_PRINTF_LEGACY_WIDE_SPECIFIERS (1ULL << 2)
// #define _CRT_INTERNAL_PRINTF_LEGACY_MSVCRT_COMPATIBILITY (1ULL << 3)
// #define _CRT_INTERNAL_PRINTF_LEGACY_THREE_DIGIT_EXPONENTS (1ULL << 4)
// #define _CRT_INTERNAL_PRINTF_STANDARD_ROUNDING (1ULL << 5)

// #define _CRT_INTERNAL_SCANF_SECURECRT (1ULL << 0)
// #define _CRT_INTERNAL_SCANF_LEGACY_WIDE_SPECIFIERS (1ULL << 1)
// #define _CRT_INTERNAL_SCANF_LEGACY_MSVCRT_COMPATIBILITY (1ULL << 2)

using int8_t = signed char;
using int16_t = short;
using int32_t = int;
using int64_t = long long;
using intmax_t = long long;
using intptr_t = long long;
using uint8_t = unsigned char;
using uint16_t = unsigned short;
using uint32_t = unsigned int;
using uint64_t = unsigned long long;
using uintmax_t = unsigned long long;
using uintptr_t = unsigned long long;

using va_list = char*;

namespace std {

using ::int16_t;
using ::int32_t;
using ::int64_t;
using ::int8_t;
using ::intmax_t;
using ::intptr_t;
using ::uint16_t;
using ::uint32_t;
using ::uint64_t;
using ::uint8_t;
using ::uintmax_t;
using ::uintptr_t;

using ::va_list;
} // namespace std

#ifndef __ywlib_import
extern "C" {
typedef struct _iobuf {
  void* _Placeholder;
} FILE;
typedef struct _Mbstatet {
  unsigned long _Wchar;
  unsigned short _Byte, _State;
} _Mbstatet, mbstate_t;
struct tm {
  int tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year, tm_wday, tm_yday, tm_isdst;
};
typedef struct __crt_locale_pointers {
  struct __crt_locale_data* locinfo;
  struct __crt_multibyte_data* mbcinfo;
} __crt_locale_pointers, *_locale_t;
struct _Ctypevec;

export FILE* __cdecl __acrt_iob_func(unsigned);
export __declspec(noinline) inline uint64_t* __cdecl __local_stdio_printf_options() {
  static uint64_t _OptionsStorage;
  return &_OptionsStorage;
}
export __declspec(noinline) inline uint64_t* __cdecl __local_stdio_scanf_options() {
  static uint64_t _OptionsStorage;
  return &_OptionsStorage;
}

long __cdecl _InterlockedCompareExchange(volatile long*, long, long);
uint8_t __cdecl _InterlockedCompareExchange128(volatile int64_t*, int64_t, int64_t, int64_t*);
long __cdecl _InterlockedDecrement(volatile long*);
long __cdecl _InterlockedExchange(volatile long*, long);
long __cdecl _InterlockedIncrement(volatile long*);
void __cdecl _ReadWriteBarrier();

short __cdecl _Getwctype(wchar_t, const _Ctypevec*) noexcept;
const wchar_t* __cdecl _Getwctypes(const wchar_t*, const wchar_t*, short*, const _Ctypevec*) noexcept;
long __cdecl _Stolx(const char*, char**, int, int*) noexcept;
unsigned long __cdecl _Stoulx(const char*, char**, int, int*) noexcept;
long long __cdecl _Stollx(const char*, char**, int, int*) noexcept;
unsigned long long __cdecl _Stoullx(const char*, char**, int, int*) noexcept;

uint16_t __cdecl _byteswap_ushort(uint16_t);
unsigned long __cdecl _byteswap_ulong(unsigned long);
uint64_t __cdecl _byteswap_uint64(uint64_t);
uint64_t __cdecl _umul128(uint64_t, uint64_t, uint64_t*);

void __cdecl _mm_pause();

int32_t __cdecl __iso_volatile_load32(const volatile int32_t*);
void __cdecl __iso_volatile_store32(volatile int32_t*, int32_t);
uint64_t __cdecl __shiftright128(uint64_t, uint64_t, unsigned char);
_NODISCARD size_t __stdcall __std_system_error_allocate_message(unsigned long, char**) noexcept;
void __stdcall __std_system_error_deallocate_message(char*) noexcept;
}
export namespace std {
using ::FILE;
using ::mbstate_t;
using ::tm;

using ::_Getwctype;
using ::_Getwctypes;
using ::_Stollx;
using ::_Stolx;
using ::_Stoullx;
using ::_Stoulx;

using ::__std_system_error_allocate_message;
using ::__std_system_error_deallocate_message;
} // namespace std
#endif

// for <complex>
#ifndef __ywlib_import
extern "C" {
#define _C_COMPLEX_T
struct _C_double_complex {
  double _Val[2];
};
struct _C_float_complex {
  float _Val[2];
};
struct _C_ldouble_complex {
  long double _Val[2];
};
double __cdecl _Cosh(double, double) noexcept;
double __cdecl _Sinh(double, double) noexcept;
short __cdecl _Exp(double*, double, short) noexcept;
float __cdecl _FCosh(float, float) noexcept;
float __cdecl _FSinh(float, float) noexcept;
short __cdecl _FExp(float*, float, short) noexcept;
long double __cdecl _LCosh(long double, long double) noexcept;
short __cdecl _LDtest(long double*) noexcept;
long double __cdecl _LSinh(long double, long double) noexcept;
short __cdecl _LExp(long double*, long double, short) noexcept;
}
export namespace std {
using ::_C_double_complex;
using ::_C_float_complex;
using ::_C_ldouble_complex;

using ::_Cosh;
using ::_Exp;
using ::_FCosh;
using ::_FExp;
using ::_FSinh;
using ::_LCosh;
using ::_LDtest;
using ::_LExp;
using ::_LSinh;
using ::_Sinh;
} // namespace std
#endif

// for <exection>
#ifndef __ywlib_import
extern "C" {
_NODISCARD unsigned int __stdcall __std_parallel_algorithms_hw_threads() noexcept;
}
export namespace std {
using ::__std_parallel_algorithms_hw_threads;
}
#endif

// for <filesystem>
#ifndef __ywlib_import
extern "C" {
int __cdecl _fflush_nolock(FILE*);
int __cdecl _fseeki64(FILE*, int64_t, int);
size_t __cdecl _fwrite_nolock(const void*, size_t, size_t, FILE*);
int __cdecl _get_stream_buffer_pointers(FILE*, char***, char***, int**);
void __cdecl _lock_file(FILE*);
void __cdecl _unlock_file(FILE*);
}
export namespace std {
using ::_fflush_nolock;
using ::_fseeki64;
using ::_fwrite_nolock;
using ::_get_stream_buffer_pointers;
using ::_lock_file;
using ::_unlock_file;
}
#endif

template<typename T>
struct __ywlib_type_identity {
  using type = T;
};
template<typename T> struct __ywlib_remove_cv_ : __ywlib_type_identity<T> {};
template<typename T> struct __ywlib_remove_cv_<const T> : __ywlib_type_identity<T> {};
template<typename T> struct __ywlib_remove_cv_<volatile T> : __ywlib_type_identity<T> {};
template<typename T> struct __ywlib_remove_cv_<const volatile T> : __ywlib_type_identity<T> {};
template<typename T> using __ywlib_remove_cv = __ywlib_remove_cv_<T>::type;
template<bool B, typename T, typename U> struct __ywlib_conditional_ : __ywlib_type_identity<U> {};
template<typename T, typename U> struct __ywlib_conditional_<true, T, U> : __ywlib_type_identity<T> {};
template<bool B, typename T, typename U> using __ywlib_conditional = __ywlib_conditional_<B, T, U>::type;
template<typename T> inline constexpr bool __ywlib_is_reference = false;
template<typename T> inline constexpr bool __ywlib_is_reference<T&> = true;
template<typename T> inline constexpr bool __ywlib_is_reference<T&&> = true;
template<typename T, typename U> inline constexpr bool __ywlib_is_same = false;
template<typename T> inline constexpr bool __ywlib_is_same<T, T> = true;
template<typename T, typename... Ts> concept __ywlib_same_as = (__ywlib_is_same<T, Ts> && ...);
template<typename T, typename... Ts> concept __ywlib_included_in = (__ywlib_is_same<T, Ts> || ...);
template<typename T> concept __ywlib_integral = __ywlib_included_in<__ywlib_remove_cv<T>, bool, char, wchar_t, char8_t, char16_t, char32_t, int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t, long, long long>;
template<typename T> concept __ywlib_signed_integral = __ywlib_integral<T> && requires { requires T(-1) < T(0); };
template<typename T> concept __ywlib_unsigned_integral = __ywlib_integral<T> && !__ywlib_signed_integral<T>;
template<typename T> concept __ywlib_floating = __ywlib_included_in<__ywlib_remove_cv<T>, float, double, long double>;
template<typename T> concept __ywlib_arithmetic = __ywlib_integral<T> || __ywlib_floating<T>;
template<typename T> constexpr T __ywlib_bitcast(auto&& x) noexcept { return __builtin_bit_cast(T, x); }
