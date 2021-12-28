/**
 * Out-of-range exception. Implementation.
 * @brief Out-of-range error implementation.
 * @file out_of_range_error.cpp
 * @author Julio C. Galindo (stickM4N)
 */
#include "../../../include/stick/error/out_of_range_error.hpp"

#if defined(_stick_lib_error_out_of_range_)


#	include "../../../include/stick/string/cstring.hpp"


namespace stick {


	out_of_range_error::out_of_range_error(const_cstring description) noexcept {
		size_t length = str_length(description);
		this->description_cache = new_str(length + 26);
		str_copy("Out-of-range error. ", 20, this->description_cache, false);
		str_copy(description, length, &this->description_cache[20]);
	}
	out_of_range_error::out_of_range_error(
	    const out_of_range_error &error) noexcept {
		this->description_cache = new_str(error.description_cache);
	}
	out_of_range_error::out_of_range_error(
	    out_of_range_error &&error) noexcept {
		this->description_cache = new_str(error.description_cache);
		delete_str(error.description_cache);
	}

	out_of_range_error::~out_of_range_error() noexcept {
		delete_str(this->description_cache);
	}


	const_cstring out_of_range_error::description() const noexcept {
		return this->description_cache;
	}


}   // namespace stick


#endif   //_stick_lib_error_memory_
