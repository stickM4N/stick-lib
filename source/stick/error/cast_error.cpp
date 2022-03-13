/**
 * Cast error. Implementation.
 * @brief Cast error implementation.
 * @file cast_error.cpp
 * @author Julio C. Galindo (stickM4N)
 */
#include "../../../include/stick/error/cast_error.hpp"

#if defined(_stick_lib_error_cast_)


#	include "../../../include/stick/string/string.hpp"


namespace stick {


	cast_error::cast_error(const_cstring description) noexcept
	    : base_error(description) { }
	cast_error::cast_error(const string &description) noexcept
	    : base_error(description) { }


	string cast_error::description() const noexcept {
		return string("Casting error. ") + *this->description_cache;
	}


}   // namespace stick


#endif   //_stick_lib_error_memory_
