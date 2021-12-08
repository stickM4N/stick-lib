/**
 * Generic error. Implementation.
 * @brief Generic error implementation.
 * @file generic_error.cpp
 * @author Julio C. Galindo (stickM4N)
 */
#include "../../../include/stick/error/generic_error.hpp"

#if defined(_stick_lib_error_generic_)


#	include "../../../include/stick/string/cstring.hpp"


namespace stick {


	generic_error::generic_error(const_cstring description) noexcept {
		this->description_cache = new_str(description, str_length(description));
	}
	generic_error::generic_error(const generic_error &error) noexcept {
		this->description_cache = new_str(error.description_cache);
	}
	generic_error::generic_error(generic_error &&error) noexcept {
		this->description_cache = error.description_cache;
		error.description_cache = nullptr;
	}

	generic_error::~generic_error() noexcept {
		delete_str(this->description_cache);
	}


	const_cstring generic_error::description() const noexcept {
		return this->description_cache;
	}


}   // namespace stick


#endif
