/**
 * Architecture name, word size and version defines.
 * @brief Architecture defines.
 * @file arch.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_defines_arch_)
#	define _stick_lib_defines_arch_



namespace stick {


	/**
	 * Create a standardized version integer format for the architecture
	 * (v.vv.vvvvv).
	 * @param [in] major Major version number.
	 * @param [in] minor Minor 2-digits version number.
	 * @param [in] patch Patch 5-digits version number.
	 * @return Standardized integer version of the architecture.
	 */
#	define stick_ARCH_MAKE_VERSION(major, minor, patch)                       \
		((major)*10000000 + (minor) % 100 * 100000 + (patch) % 100000)


	/**
	 * @def stick_ARCH_ID
	 * 			System current architecture name.
	 * @def stick_ARCH_NAME
	 * 			System current architecture name.
	 * @def stick_ARCH_VERSION
	 * 			System current architecture version.
	 * @def stick_ARCH_WORD_SIZE
	 * 			System current word size.
	 */


#	define stick_ARCH_ID_x86_64 1   ///< System architecture ID for x86_64.
#	define stick_ARCH_ID_x86_32 2   ///< System architecture ID for x86_32.
#	define stick_ARCH_ID_ARM 3   ///< System architecture ID for ARM.
#	define stick_ARCH_ID_SPARK 4   ///< System architecture ID for SPARK.
#	define stick_ARCH_ID_UNKNOWN 0   ///< System architecture ID for unknown.

#	define stick_ARCH_NAME_x86_64                                             \
		"x86_64"   ///< System architecture name for x86_64.
#	define stick_ARCH_NAME_x86_32                                             \
		"x86_32"   ///< System architecture name for x86_32.
#	define stick_ARCH_NAME_ARM "ARM"   ///< System architecture name for ARM.
#	define stick_ARCH_NAME_SPARK                                              \
		"SPARK"   ///< System architecture name for SPARK.
#	define stick_ARCH_NAME_UNKNOWN                                            \
		"arch_unknown"   ///< System architecture name for unknown.


#	define stick_ARCH_WORD_SIZE_64_BIT 64   ///< System word size for 64 bits.
#	define stick_ARCH_WORD_SIZE_32_BIT 32   ///< System word size for 32 bits.
#	define stick_ARCH_WORD_SIZE_UNKNOWN 0   ///< System word size for unknown.


/* ____________________ x86_64 ____________________ */
#	if defined(__x86_64) || defined(__x86_64__) || defined(__amd64__)         \
	    || defined(__amd64) || defined(_M_X64)
#		define stick_ARCH_ID stick_ARCH_ID_x86_64
#		define stick_ARCH_NAME stick_ARCH_NAME_x86_64
#		define stick_ARCH_WORD_SIZE stick_ARCH_WORD_SIZE_64_BIT

/* ____________________ x86_32 ____________________ */
#	elif defined(i386) || defined(__i386__) || defined(__i486__)              \
	    || defined(__i586__) || defined(__i686__) || defined(__i386)           \
	    || defined(_M_IX86) || defined(_X86_) || defined(__THW_INTEL__)        \
	    || defined(__I86__) || defined(__INTEL__)
#		define stick_ARCH_ID stick_ARCH_ID_x86_32
#		define stick_ARCH_NAME stick_ARCH_NAME_x86_32
#		define stick_ARCH_WORD_SIZE stick_ARCH_WORD_SIZE_32_BIT

#		if defined(__I86__)
#			define stick_ARCH_VERSION stick_ARCH_MAKE_VERSION(__I86__, 0, 0)
#		elif defined(_M_IX86)
#			define stick_ARCH_VERSION                                         \
				stick_ARCH_MAKE_VERSION((_M_IX86) / 100 % 100, 0, 0)
#		elif defined(__i686__)
#			define stick_ARCH_VERSION stick_ARCH_MAKE_VERSION(6, 0, 0)
#		elif defined(__i586__)
#			define stick_ARCH_VERSION stick_ARCH_MAKE_VERSION(5, 0, 0)
#		elif defined(__i486__)
#			define stick_ARCH_VERSION stick_ARCH_MAKE_VERSION(4, 0, 0)
#		elif defined(__i386__)
#			define stick_ARCH_VERSION stick_ARCH_MAKE_VERSION(3, 0, 0)
#		endif

/* ____________________ ARM ____________________ */
#	elif defined(__ARM_ARCH) || defined(__TARGET_ARCH_ARM)                    \
	    || defined(__TARGET_ARCH_THUMB) || defined(_M_ARM) || defined(__arm__) \
	    || defined(__arm64) || defined(__thumb__) || defined(_M_ARM64)         \
	    || defined(__aarch64__) || defined(__AARCH64EL__)                      \
	    || defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__)                 \
	    || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__)                \
	    || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__)                \
	    || defined(__ARM_ARCH_6KZ__) || defined(__ARM_ARCH_6T2__)              \
	    || defined(__ARM_ARCH_5TE__) || defined(__ARM_ARCH_5TEJ__)             \
	    || defined(__ARM_ARCH_4T__) || defined(__ARM_ARCH_4__)
#		define stick_ARCH_ID stick_ARCH_ID_ARM
#		define stick_ARCH_NAME stick_ARCH_NAME_ARM

#		if defined(__ARM_ARCH)
#			define stick_ARCH_VERSION stick_ARCH_MAKE_VERSION(__ARM_ARCH, 0, 0)
#		elif defined(__TARGET_ARCH_ARM)
#			define stick_ARCH_VERSION                                         \
				stick_ARCH_MAKE_VERSION(__TARGET_ARCH_ARM, 0, 0)
#		elif defined(__TARGET_ARCH_THUMB)
#			define stick_ARCH_VERSION                                         \
				stick_ARCH_MAKE_VERSION(__TARGET_ARCH_THUMB, 0, 0)
#		elif defined(_M_ARM)
#			define stick_ARCH_VERSION stick_ARCH_MAKE_VERSION(_M_ARM, 0, 0)
#		elif defined(__arm64) || defined(_M_ARM64) || defined(__aarch64__)    \
		    || defined(__AARCH64EL__)
#			define stick_ARCH_VERSION stick_ARCH_MAKE_VERSION(8, 0, 0)
#		elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__)              \
		    || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__)
#			define stick_ARCH_VERSION stick_ARCH_MAKE_VERSION(7, 0, 0)
#		elif defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__)
	|| defined(__ARM_ARCH_6KZ__) || defined(__ARM_ARCH_6T2__)
#			define stick_ARCH_VERSION stick_ARCH_MAKE_VERSION(6, 0, 0)
#		elif defined(__ARM_ARCH_5TE__) || defined(__ARM_ARCH_5TEJ__)
#			define stick_ARCH_VERSION stick_ARCH_MAKE_VERSION(5, 0, 0)
#		elif defined(__ARM_ARCH_4T__) || defined(__ARM_ARCH_4__)
#			define stick_ARCH_VERSION stick_ARCH_MAKE_VERSION(4, 0, 0)
#		endif

#		if defined(stick_ARCH_VERSION)                                        \
		    and stick_ARCH_VERSION >= stick_ARCH_MAKE_VERSION(8, 0, 0)
#			define stick_ARCH_WORD_SIZE stick_ARCH_WORD_SIZE_64_BIT
#		else
#			define stick_ARCH_WORD_SIZE stick_ARCH_WORD_SIZE_32_BIT
#		endif

/* ____________________ SPARK ____________________ */
#	elif defined(__sparc__) || defined(__sparc)
#		define stick_ARCH_ID stick_ARCH_ID_SPARK
#		define stick_ARCH_NAME stick_ARCH_NAME_SPARK

#		if defined(__sparcv9) || defined(__sparc_v9__)
#			define stick_ARCH_VERSION stick_ARCH_MAKE_VERSION(9, 0, 0)
#		elif defined(__sparcv8) || defined(__sparc_v8__)
#			define stick_ARCH_VERSION stick_ARCH_MAKE_VERSION(8, 0, 0)
#		elif not defined(stick_ARCH_VERSION)
#			define stick_ARCH_VERSION stick_ARCH_MAKE_VERSION(0, 0, 0)
#		endif

#		if defined(stick_ARCH_VERSION)                                        \
		    and stick_ARCH_VERSION >= stick_ARCH_MAKE_VERSION(9, 0, 0)
#			define stick_ARCH_WORD_SIZE stick_ARCH_WORD_SIZE_64_BIT
#		else
#			define stick_ARCH_WORD_SIZE stick_ARCH_WORD_SIZE_32_BIT
#		endif

/* ____________________ unknown ____________________ */
#	else
#		define stick_ARCH_ID stick_ARCH_ID_UNKNOWN
#		define stick_ARCH_NAME stick_ARCH_NAME_UNKNOWN

#	endif


#	if not defined(stick_ARCH_VERSION)
#		define stick_ARCH_VERSION stick_ARCH_MAKE_VERSION(0, 0, 0)
#	endif

#	if not defined(stick_ARCH_WORD_SIZE)
#		define stick_ARCH_WORD_SIZE stick_ARCH_WORD_SIZE_UNKNOWN
#	endif


	/**
	 * Checks if current architecture is a specific one.
	 * @def stick_IS_ARCH_x86_64
	 *	 	Checks if current arch is x86_64.
	 * @def stick_IS_ARCH_x86_32
	 * 		Checks if current arch is x86_32.
	 * @def stick_IS_ARCH_ARM
	 * 		Checks if current arch is ARM.
	 * @def stick_IS_ARCH_SPARK
	 * 		Checks if current arch is SPARK.
	 * @def stick_IS_ARCH_UNKNOWN
	 * 		Checks if current arch is unknown.
	 */
#	define stick_IS_ARCH_x86_64 (stick_ARCH_ID == stick_ARCH_ID_x86_64)
#	define stick_IS_ARCH_x86_32 (stick_ARCH_ID == stick_ARCH_ID_x86_32)
#	define stick_IS_ARCH_ARM (stick_ARCH_ID == stick_ARCH_ID_ARM)
#	define stick_IS_ARCH_SPARK (stick_ARCH_ID == stick_ARCH_ID_SPARK)
#	define stick_IS_ARCH_UNKNOWN (stick_ARCH_ID == stick_ARCH_ID_UNKNOWN)


}   // namespace stick



#endif   //_stick_lib_defines_arch_
