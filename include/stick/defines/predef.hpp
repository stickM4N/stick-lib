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
#	define stick_CXX_CONSTEXPR_VERSION                                        \
		__cpp_constexpr   ///< Current C++ constexpr version.

#	define stick_CURRENT_DATE __DATE__   ///< Current date.
#	define stick_CURRENT_TIME __TIME__   ///< Current time.
#	define stick_CURRENT_DATETIME __DATE__ __TIME__   ///< Current datetime.

#	define stick_CONTEXT_FILE __FILE__   ///< Context file.
#	define stick_CONTEXT_LINE __LINE   ///< Context line.
#	define stick_CONTEXT_FUNCTION __FUNCTION__   ///< Context function name.
#	define stick_CONTEXT_PRETTY_FUNCTION                                      \
		__PRETTY_FUNCTION__   ///< Context function declaration.



	/**
	 * Constexpr definitions for each standard.
	 * @def stick_constexpr20
	 * 			Declare as constexpr if stick_HAS_CONSTEXPR20.
	 * @def stick_constexpr17
	 * 			Declare as constexpr if stick_HAS_CONSTEXPR17.
	 * @def stick_constexpr14
	 * 			Declare as constexpr if stick_HAS_CONSTEXPR14.
	 * @def stick_constexpr
	 * 			Declare as constexpr.
	 */

#	define stick_constexpr constexpr


#	define stick_HAS_CONSTEXPR20                                              \
		(stick_CXX_CONSTEXPR_VERSION                                           \
		 > 201900ul)   ///< Checks if cxx20 constexpr is supported.
#	define stick_HAS_CONSTEXPR17                                              \
		(stick_CXX_CONSTEXPR_VERSION                                           \
		 > 201700ul)   ///< Checks if cxx17 constexpr is supported.
#	define stick_HAS_CONSTEXPR14                                              \
		(stick_CXX_CONSTEXPR_VERSION                                           \
		 > 201300ul)   ///< Checks if cxx14 constexpr is supported.


#	if stick_HAS_CONSTEXPR20
#		define stick_constexpr20 constexpr
#		define stick_constexpr17 constexpr
#		define stick_constexpr14 constexpr

#	elif stick_HAS_CONSTEXPR17
#		define stick_constexpr20
#		define stick_constexpr17 constexpr
#		define stick_constexpr14 constexpr

#	elif stick_HAS_CONSTEXPR14
#		define stick_constexpr20
#		define stick_constexpr17
#		define stick_constexpr14 constexpr

#	else
#		define stick_constexpr20
#		define stick_constexpr17
#		define stick_constexpr14

#	endif


}   // namespace stick



#endif   //_stick_lib_defines_predef_
