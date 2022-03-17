/**
 * Compiler predefined macro aliases for easier usage.
 * @brief Compiler predefined macros aliases.
 * @file predef.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_defines_predef_)
#	define _stick_lib_defines_predef_



namespace stick {


#	define stick_CXX_VERSION __cplusplus   ///< Current C++ standard version.

#	define stick_CURRENT_DATE __DATE__   ///< Current date.
#	define stick_CURRENT_TIME __TIME__   ///< Current time.
#	define stick_CURRENT_DATETIME __DATE__ __TIME__   ///< Current datetime.

#	define stick_CONTEXT_FILE __FILE__   ///< Context file.
#	define stick_CONTEXT_LINE __LINE   ///< Context line.
#	define stick_CONTEXT_FUNCTION __FUNCTION__   ///< Context function name.
#	define stick_CONTEXT_PRETTY_FUNCTION                                      \
		__PRETTY_FUNCTION__   ///< Context function declaration.


	/// Constexpr definitions for each standard.
#	define stick_constexpr constexpr

#	if __cpp_constexpr == 201907L
#		define stick_HAS_CONSTEXPR20 true
#		define stick_HAS_CONSTEXPR17 true
#		define stick_HAS_CONSTEXPR14 true

#		define stick_constexpr20 constexpr
#		define stick_constexpr17 constexpr
#		define stick_constexpr14 constexpr

#	elif __cpp_constexpr == 201603L
#		define stick_HAS_CONSTEXPR20 false
#		define stick_HAS_CONSTEXPR17 true
#		define stick_HAS_CONSTEXPR14 true

#		define stick_constexpr20
#		define stick_constexpr17 constexpr
#		define stick_constexpr14 constexpr

#	elif __cpp_constexpr == 201304L
#		define stick_HAS_CONSTEXPR20 false
#		define stick_HAS_CONSTEXPR17 false
#		define stick_HAS_CONSTEXPR14 true

#		define stick_constexpr20
#		define stick_constexpr17
#		define stick_constexpr14 constexpr

#	else
#		define stick_HAS_CONSTEXPR20 false
#		define stick_HAS_CONSTEXPR17 false
#		define stick_HAS_CONSTEXPR14 false

#		define stick_constexpr20
#		define stick_constexpr17
#		define stick_constexpr14

#	endif


}   // namespace stick



#endif   //_stick_lib_defines_predef_
