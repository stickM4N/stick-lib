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
	 * @def stick_OS_ID
	 * 			System current operating system ID.
	 * @def stick_OS_NAME
	 * 			System current operating system name.
	 */


#	define stick_OS_ID_LINUX 1   ///< Operating system ID for Linux.
#	define stick_OS_ID_WINDOWS 2   ///< Operating system ID for Windows.
#	define stick_OS_ID_MACOS 3   ///< Operating system ID for macOS.
#	define stick_OS_ID_UNIX 4   ///< Operating system ID for Unix.
#	define stick_OS_ID_SOLARIS 5   ///< Operating system ID for Solaris.
#	define stick_OS_ID_UNKNOWN 0   ///< Operating system ID for unknown.

#	define stick_OS_NAME_LINUX "Linux"   ///< Operating system name for Linux.
#	define stick_OS_NAME_WINDOWS                                              \
		"Windows"   ///< Operating system name for Windows.
#	define stick_OS_NAME_MACOS "MacOS"   ///< Operating system name for MacOS.
#	define stick_OS_NAME_UNIX "Unix"   ///< Operating system name for Unix.
#	define stick_OS_NAME_SOLARIS                                              \
		"Solaris"   ///< Operating system name for Solaris.
#	define stick_OS_NAME_UNKNOWN                                              \
		"os_unknown"   ///< Operating system name for unknown.


/* ____________________ Linux ____________________ */
#	if defined(linux) || defined(__linux) || defined(__linux__)               \
	    || defined(__gnu_linux__)
#		define stick_OS_ID stick_OS_ID_LINUX
#		define stick_OS_NAME stick_OS_NAME_LINUX

/* ____________________ Windows ____________________ */
#	elif defined(_WIN32) || defined(_WIN64) || defined(__WIN32__)             \
	    || defined(__TOS_WIN__) || defined(__WINDOWS__)
#		define stick_OS_ID stick_OS_ID_WINDOWS
#		define stick_OS_NAME stick_OS_NAME_WINDOWS

/* ____________________ MacOS ____________________ */
#	elif defined(macintosh) || defined(Macintosh)                             \
	    || (defined(__APPLE__) && defined(__MACH__))
#		define stick_OS_ID stick_OS_ID_MACOS
#		define stick_OS_NAME stick_OS_NAME_MACOS

/* ____________________ Unix ____________________ */
#	elif defined(__sysv__) || defined(__SVR4) || defined(__svr4__)            \
	    || defined(_SYSTYPE_SVR4)
#		define stick_OS_ID stick_OS_ID_UNIX
#		define stick_OS_NAME stick_OS_NAME_UNIX

/* ____________________ Solaris ____________________ */
#	elif defined(sun) || defined(__sun)
#		define stick_OS_ID stick_OS_ID_SOLARIS
#		define stick_OS_NAME stick_OS_NAME_SOLARIS

/* ____________________ unknown ____________________ */
#	else
#		define stick_OS_ID stick_OS_ID_UNKNOWN
#		define stick_OS_NAME stick_OS_NAME_UNKNOWN

#	endif


	/**
	 * Checks if current operating system is a specific one.
	 * @def stick_IS_OS_LINUX
	 *	 	Checks if current operating system is Linux.
	 * @def stick_IS_OS_WINDOWS
	 * 		Checks if current operating system is Windows.
	 * @def stick_IS_OS_MACOS
	 * 		Checks if current operating system is MacOS.
	 * @def stick_IS_OS_UNIX
	 * 		Checks if current operating system is Unix.
	 * @def stick_IS_OS_SOLARIS
	 * 		Checks if current operating system is Solaris.
	 * @def stick_IS_OS_UNKNOWN
	 * 		Checks if current operating system is unknown.
	 */
#	define stick_IS_OS_LINUX (stick_OS_ID == stick_OS_ID_LINUX)
#	define stick_IS_OS_WINDOWS (stick_OS_ID == stick_OS_ID_WINDOWS)
#	define stick_IS_OS_MACOS (stick_OS_ID == stick_OS_ID_MACOS)
#	define stick_IS_OS_UNIX (stick_OS_ID == stick_OS_ID_UNIX)
#	define stick_IS_OS_SOLARIS (stick_OS_ID == stick_OS_ID_SOLARIS)
#	define stick_IS_OS_UNKNOWN (stick_OS_ID == stick_OS_ID_UNKNOWN)


}   // namespace stick



#endif   //_stick_lib_defines_os_
