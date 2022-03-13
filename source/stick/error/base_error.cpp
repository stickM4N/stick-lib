/**
 * Base error. Implementation.
 * @brief Base error implementation.
 * @file base_error.cpp
 * @author Julio C. Galindo (stickM4N)
 */
#include "../../../include/stick/error/base_error.hpp"

#if defined(_stick_lib_error_base_)


#	include "../../../include/stick/string/string.hpp"


namespace stick {


	base_error::base_error(const_cstring description) noexcept
	    : description_cache(new string(description)) { }
	base_error::base_error(const string &description) noexcept
	    : description_cache(new string(description)) { }

	base_error::~base_error() noexcept {
		delete this->description_cache;
		this->description_cache = nullptr;
	}


	string base_error::description() const noexcept {
		return *this->description_cache;
	}
	const_cstring base_error::what() const noexcept {
		return this->description();
	}


}   // namespace stick


#endif   //_stick_lib_error_base_
