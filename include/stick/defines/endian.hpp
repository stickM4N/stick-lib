/**
 * Endian and byte order defines. Endian byte order. Byte priority goes from 4
 * (high) to 1 (low).
 * @brief Endian defines.
 * @file endian.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_defines_endian_)
#	define _stick_lib_defines_endian_



namespace stick {


	/**
	 * @def stick_ENDIAN
	 * 			Current byte order.
	 */


#	define stick_ENDIAN_LITTLE 1234   ///< Byte order for little endian.
#	define stick_ENDIAN_BIG 4321   ///< Byte order for big endian.
#	define stick_ENDIAN_UNKNOWN 0   ///< Byte order for unknown endian.


#	if defined(__BYTE_ORDER__)
#		if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#			define stick_ENDIAN stick_ENDIAN_BIG
#		elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#			define stick_ENDIAN stick_ENDIAN_LITTLE
#		endif

#	elif defined(__BYTE_ORDER)
#		if __BYTE_ORDER == __BIG_ENDIAN
#			define stick_ENDIAN stick_ENDIAN_BIG
#		elif __BYTE_ORDER == __LITTLE_ENDIAN
#			define stick_ENDIAN stick_ENDIAN_LITTLE
#		endif

#	elif defined(BYTE_ORDER) && BYTE_ORDER
#		if BYTE_ORDER == BIG_ENDIAN
#			define stick_ENDIAN stick_ENDIAN_BIG
#		elif BYTE_ORDER == LITTLE_ENDIAN
#			define stick_ENDIAN stick_ENDIAN_LITTLE
#		endif

#	elif (defined(__LITTLE_ENDIAN__) && __LITTLE_ENDIAN__ == 1)               \
	    || defined(__i386) || defined(__i386__) || defined(_X86_)              \
	    || defined(__X86__) || defined(_M_IX86) || defined(__THW_INTEL__)      \
	    || defined(__x86_64) || defined(__x86_64__) || defined(__amd64)        \
	    || defined(__amd64__) || defined(_M_AMD64) || defined(_M_X64)          \
	    || defined(__ia64) || defined(_IA64) || defined(__IA64__) ||           \
	    || defined(__ia64__) || defined(_M_IA64) || defined(__itanium__)       \
	    || defined(__ARMEL__) || defined(__THUMBEL__)                          \
	    || defined(__AARCH64EL__) || defined(__alpha) || defined(__alpha__)    \
	    || defined(_M_ALPHA) || defined(__riscv) || defined(__riscv__)         \
	    || defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__)
#		define stick_ENDIAN stick_ENDIAN_LITTLE

#	elif (defined(__BIG_ENDIAN__) && __BIG_ENDIAN__ == 1)                     \
	    || defined(__ARMEB__) || defined(__THUMBEB__)                          \
	    || defined(__AARCH64EB__) || defined(_MIPSEB) || defined(__MIPSEB)     \
	    || defined(__MIPSEB__) || defined(_ARCH_PPC) || defined(_ARCH_PPC64)   \
	    || defined(__ppc) || defined(__ppc__) || defined(__sparc)              \
	    || defined(__sparc__) || defined(__sparc64__) || defined(__or1k__)     \
	    || defined(__OR1K__)
#		define stick_ENDIAN stick_ENDIAN_BIG

#	else
#		define stick_ENDIAN stick_ENDIAN_UNKNOWN
#	endif


	/**
	 * Endian types.
	 */
	enum class endian {
		little = stick_ENDIAN_LITTLE,   ///< Byte order for little endian.
		big = stick_ENDIAN_BIG,   ///< Byte order for little endian.
		native = stick_ENDIAN   ///< Current endian byte order.
	};


}   // namespace stick



#endif   //_stick_lib_defines_endian_
