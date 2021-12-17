/**
 * Memory error. Implementation.
 * @brief Memory error implementation.
 * @file memory_error.cpp
 * @author Julio C. Galindo (stickM4N)
 */
#include "../../../include/stick/error/memory_error.hpp"

#if defined(_stick_lib_error_memory_)


#	include "../../../include/stick/string/cstring.hpp"


namespace stick {


	memory_error::memory_error(const_cstring description) noexcept {
		size_t length = str_length(description);
		this->description_cache = new_str(length + 26);
		str_copy("Memory management error. ", 25, this->description_cache);
		str_copy(description, length, &this->description_cache[25]);
	}
	memory_error::memory_error(const memory_error &error) noexcept {
		this->description_cache = new_str(error.description_cache);
	}
	memory_error::memory_error(memory_error &&error) noexcept {
		this->description_cache = new_str(error.description_cache);
		delete_str(error.description_cache);
	}

	memory_error::~memory_error() noexcept {
		delete_str(this->description_cache);
	}


	const_cstring memory_error::description() const noexcept {
		return this->description_cache;
	}


}   // namespace stick


#endif   //_stick_lib_error_memory_
