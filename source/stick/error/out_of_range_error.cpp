/**
 * Out-of-range exception. Implementation.
 * @brief Out-of-range error implementation.
 * @file out_of_range_error.cpp
 * @author Julio C. Galindo (stickM4N)
 */
#include "../../../include/stick/error/out_of_range_error.hpp"

#if defined(_stick_lib_error_out_of_range_)


#	include "../../../include/stick/string/string.hpp"


namespace stick {


	out_of_range_error::out_of_range_error(const_cstring description) noexcept
	    : base_error(description) { }
	out_of_range_error::out_of_range_error(const string &description) noexcept
	    : base_error(description) { }


	string out_of_range_error::description() const noexcept {
		return string("Out-of-range error. ") + *this->description_cache;
	}


}   // namespace stick


#endif   //_stick_lib_error_memory_
