/**
 * Base error to derive all others from it.
 * @brief Base error.
 * @file base_error.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_error_base_)
#	define _stick_lib_error_base_



#	include "../defines/types.hpp"


#	if defined(stick_USE_STD_EXCEPTION_BASE)
#		include <exception>
#		define stick_STD_EXCEPTION_BASED_INHERIT_ : public std::exception
#		define stick_STD_EXCEPTION_BASED_OVERRIDE_ override
#		define stick_STD_EXCEPTION_BASED_VIRTUAL_

#	else
#		define stick_STD_EXCEPTION_BASED_INHERIT_
#		define stick_STD_EXCEPTION_BASED_OVERRIDE_
#		define stick_STD_EXCEPTION_BASED_VIRTUAL_ virtual

#	endif


namespace stick {


	/**
	 * Base class for error description.
	 */
	class base_error stick_STD_EXCEPTION_BASED_INHERIT_ {

	public:
		stick_STD_EXCEPTION_BASED_VIRTUAL_ ~base_error() noexcept
		    stick_STD_EXCEPTION_BASED_OVERRIDE_ = default;


		/**
		 * Get the error description.
		 * @return Description cstring.
		 */
		virtual const_cstring description() const noexcept = 0;
		/**
		 * Get the error description. Mimic description for std::exception
		 * compatibility.
		 * @return Description cstring.
		 */
		const_cstring what() const noexcept stick_STD_EXCEPTION_BASED_OVERRIDE_;
	};


#	undef stick_STD_EXCEPTION_BASED_INHERIT_
#	undef stick_STD_EXCEPTION_BASED_OVERRIDE_
#	undef stick_STD_EXCEPTION_BASED_VIRTUAL_


}   // namespace stick



#endif   //_stick_lib_error_base_
