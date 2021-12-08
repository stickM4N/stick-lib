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


}   // namespace stick



#endif   //_stick_lib_defines_predef_
