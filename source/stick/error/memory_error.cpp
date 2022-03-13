/**
 * Memory error. Implementation.
 * @brief Memory error implementation.
 * @file memory_error.cpp
 * @author Julio C. Galindo (stickM4N)
 */
#include "../../../include/stick/error/memory_error.hpp"

#if defined(_stick_lib_error_memory_)


#	include "../../../include/stick/string/string.hpp"


namespace stick {


	memory_error::memory_error(const_cstring description) noexcept
	    : base_error(description) { }
	memory_error::memory_error(const string &description) noexcept
	    : base_error(description) { }


	string memory_error::description() const noexcept {
		return string("Memory management error. ") + *this->description_cache;
	}


}   // namespace stick


#endif   //_stick_lib_error_memory_
