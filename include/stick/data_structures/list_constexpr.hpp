/**
 * List initializer. Helps creating structures using a list.
 * @brief List initializer template.
 * @file list_constexpr.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_data_structures_initializer_list_)
#	define _stick_lib_data_structures_initializer_list_


#	include <initializer_list>


namespace stick {


	/**
	 * This cannot be reimplemented, its a language feature that is forcibly
	 * looked within the standard library. This is just an alias to use within
	 * the library.
	 */
	template<typename type>
	using list_constexpr = std::initializer_list<type>;


}   // namespace stick



#endif   //_stick_lib_data_structures_initializer_list_
