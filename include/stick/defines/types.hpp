/**
 * Define aliases for common types.
 * @brief Common types definitions.
 * @file types.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_defines_types_)
#	define _stick_lib_defines_types_


namespace stick {


#	define null __null


	typedef void void_t;
	typedef void *voidptr_t;
	typedef const void *voidconstptr_t;
	typedef decltype(nullptr) nullptr_t;
	typedef const decltype(nullptr) nullconstptr_t;

	typedef bool bool_t;

	typedef signed char schar_t;
	typedef char char_t;
	typedef unsigned char uchar_t;

	typedef signed short int short_t;
	typedef unsigned short int ushort_t;

	typedef signed int int_t;
	typedef unsigned int uint_t;

	typedef signed long int long_t;
	typedef unsigned long int ulong_t;

	typedef signed long long int llong_t;
	typedef unsigned long long int ullong_t;

	typedef signed char int8_t;
	typedef unsigned char uint8_t;

	typedef signed short int int16_t;
	typedef unsigned short int uint16_t;

	typedef signed int int32_t;
	typedef unsigned int uint32_t;

	typedef signed long long int int64_t;
	typedef unsigned long long int uint64_t;

	typedef float float_t;
	typedef float float32_t;

	typedef double double_t;
	typedef double double64_t;

	typedef long double double128_t;
	typedef long double ldouble_t;

	typedef unsigned char byte_t;
	typedef unsigned short byte2_t;
	typedef unsigned int byte4_t;
	typedef unsigned long long int byte8_t;

	typedef signed long int ssize_t;
	typedef unsigned long int size_t;


	typedef char_t *cstring;
	typedef const char_t *const_cstring;

	typedef wchar_t *wcstring;
	typedef const wchar_t *const_wcstring;


}   // namespace stick



#endif   //_stick_lib_defines_types_
