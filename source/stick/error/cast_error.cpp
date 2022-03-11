/**
 * Cast error. Implementation.
 * @brief Cast error implementation.
 * @file cast_error.cpp
 * @author Julio C. Galindo (stickM4N)
 */
#include "../../../include/stick/error/cast_error.hpp"

#if defined(_stick_lib_error_cast_)


#	include "../../../include/stick/string/cstring.hpp"


namespace stick {


	cast_error::cast_error(const_cstring description) noexcept {
		size_t length = str_length(description);
		this->description_cache = new_str(length + 26);
		str_copy("Casting error. ", 15, this->description_cache, false);
		str_copy(description, length, &this->description_cache[15]);
	}
	cast_error::cast_error(const cast_error &error) noexcept {
		this->description_cache = new_str(error.description_cache);
	}
	cast_error::cast_error(cast_error &&error) noexcept {
		this->description_cache = new_str(error.description_cache);
		delete_str(error.description_cache);
	}

	cast_error::~cast_error() noexcept {
		delete_str(this->description_cache);
	}


	const_cstring cast_error::description() const noexcept {
		return this->description_cache;
	}


}   // namespace stick


#endif   //_stick_lib_error_memory_
