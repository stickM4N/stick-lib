/**
 * Operating system name defines.
 * @brief Operating system defines.
 * @file os.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_defines_os_)
#	define _stick_lib_defines_os_



namespace stick {


	/**
	 * @def stick_OS
	 * 			Current operating system name.
	 */


#	define stick_OS_LINUX "Linux"   ///< Operating system name for Linux.
#	define stick_OS_WINDOWS "Windows"   ///< Operating system name for Windows.
#	define stick_OS_MACOS "macOS"   ///< Operating system name for macOS.
#	define stick_OS_UNIX "Unix"   ///< Operating system name for Unix.
#	define stick_OS_SOLARIS "Solaris"   ///< Operating system name for Solaris.
#	define stick_OS_UNKNOWN                                                   \
		"os_unknown"   ///< Operating system name for unknown.


/* ____________________ Linux ____________________ */
#	if defined(linux) || defined(__linux) || defined(__linux__)               \
	    || defined(__gnu_linux__)
#		define stick_OS stick_OS_LINUX

/* ____________________ Windows ____________________ */
#	elif defined(_WIN32) || defined(_WIN64) || defined(__WIN32__)             \
	    || defined(__TOS_WIN__) || defined(__WINDOWS__)
#		define stick_OS stick_OS_WINDOWS

/* ____________________ MacOS ____________________ */
#	elif defined(macintosh) || defined(Macintosh)                             \
	    || (defined(__APPLE__) && defined(__MACH__))
#		define stick_OS stick_OS_MACOS

/* ____________________ Unix ____________________ */
#	elif defined(__sysv__) || defined(__SVR4) || defined(__svr4__)            \
	    || defined(_SYSTYPE_SVR4)
#		define stick_OS stick_OS_UNIX

/* ____________________ Solaris ____________________ */
#	elif defined(sun) || defined(__sun)
#		define stick_OS stick_OS_SOLARIS

/* ____________________ unknown ____________________ */
#	else
#		define stick_OS stick_OS_UNKNOWN

#	endif


}   // namespace stick



#endif   //_stick_lib_defines_os_
