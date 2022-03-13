/**
 * Generic error. Implementation.
 * @brief Generic error implementation.
 * @file generic_error.cpp
 * @author Julio C. Galindo (stickM4N)
 */
#include "../../../include/stick/error/generic_error.hpp"

#if defined(_stick_lib_error_generic_)


#	include "../../../include/stick/string/string.hpp"


namespace stick {


	generic_error::generic_error(const_cstring description) noexcept
	    : base_error(description) { }
	generic_error::generic_error(const string &description) noexcept
	    : base_error(description) { }


	string generic_error::description() const noexcept {
		return *this->description_cache;
	}


}   // namespace stick


#endif   //_stick_lib_error_generic_
