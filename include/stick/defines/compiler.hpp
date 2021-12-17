/**
 * Compiler name and version defines.
 * @brief Architectures defines.
 * @file compiler.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_defines_compiler_)
#	define _stick_lib_defines_compiler_



namespace stick {


	/**
	 * Create a standardized version integer format for the compiler
	 * (v.vv.vvvvv).
	 * @param [in] major Major version number.
	 * @param [in] minor Minor 2-digits version number.
	 * @param [in] patch Patch 5-digits version number.
	 * @return Standardized integer version of the compiler.
	 */
#	define stick_COMPILER_MAKE_VERSION(major, minor, patch)                   \
		((major) % 100 * 10000000 + (minor) % 100 * 100000 + (patch) % 100000)


	/**
	 * @def stick_COMPILER
	 * 			Current compiler name.
	 * @def stick_COMPILER_VERSION
	 * 			Current compiler version.
	 */


#	define stick_COMPILER_CLANG "Clang"   ///< Compiler name for Clang.
#	define stick_COMPILER_GCC                                                 \
		"GNU C/C++ Compiler"   ///< Compiler name for GNU C/C++ Compiler.
#	define stick_COMPILER_MSVC                                                \
		"Microsoft Visual C/C++"   ///< Compiler name for Microsoft Visual
		                           ///< C/C++.
#	define stick_COMPILER_SUNPRO                                              \
		"Oracle Solaris Studio"   ///< Compiler name for Oracle Solaris Studio.


/* ____________________ Clang ____________________ */
#	if defined(__clang__)
#		define stick_COMPILER stick_COMPILER_CLANG
#		define stick_COMPILER_VERSION                                         \
			stick_COMPILER_MAKE_VERSION(__clang_major__, __clang_minor__,      \
			                            __clang_patchlevel__)

/* ____________________ GCC ____________________ */
#	elif defined(__GNUC__)
#		define stick_COMPILER stick_COMPILER_GCC

#		if defined(__GNUC_PATCHLEVEL__)
#			define stick_COMPILER_VERSION stick_COMPILER_MAKE_VERSION__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#		else
#			define stick_COMPILER_VERSION                                     \
				stick_COMPILER_MAKE_VERSION(__GNUC__, __GNUC_MINOR__,          \
				                            __GNUC_PATCHLEVEL__, 0)
#		endif

/* ____________________ MSVC ____________________ */
#	elif defined(_MSC_VER)
#		define stick_COMPILER stick_COMPILER_MSVC
#		define stick_COMPILER_VERSION _MSC_FULL_VER

/* ____________________ SUNPRO ____________________ */
#	elif defined(__SUNPRO_CC) || defined(__SUNPRO_C)
#		define stick_COMPILER stick_COMPILER_SUNPRO

#		if defined(__SUNPRO_CC)
#			if (__SUNPRO_CC >= 0x5100)
#				define stick_COMPILER_VERSION                                 \
					stick_ARCH_MAKE_VERSION((__SUNPRO_CC & 0xF00) >> 12,       \
					                        (__SUNPRO_CC & 0xF0) >> 4,         \
					                        (__SUNPRO_CC & 0xF))
#			else
#				define stick_COMPILER_VERSION                                 \
					stick_ARCH_MAKE_VERSION((__SUNPRO_CC & 0xF00) >> 8,        \
					                        (__SUNPRO_CC & 0xF0) >> 4,         \
					                        (__SUNPRO_CC & 0xF))
#			endif
#		elif defined(__SUNPRO_C)
#			if (__SUNPRO_CC >= 0x5100)
#				define stick_COMPILER_VERSION                                 \
					stick_ARCH_MAKE_VERSION((__SUNPRO_C & 0xF00) >> 12,        \
					                        (__SUNPRO_C & 0xF0) >> 4,          \
					                        (__SUNPRO_C & 0xF))
#			else
#				define stick_COMPILER_VERSION                                 \
					stick_ARCH_MAKE_VERSION((__SUNPRO_C & 0xF00) >> 8,         \
					                        (__SUNPRO_C & 0xF0) >> 4,          \
					                        (__SUNPRO_C & 0xF))
#			endif
#		endif

#	endif


#	if not defined(stick_COMPILER_VERSION)
#		define stick_COMPILER_VERSION stick_COMPILER_MAKE_VERSION(0, 0, 0)
#	endif


}   // namespace stick



#endif   //_stick_lib_defines_compiler_