/**
 * Base error. Implementation.
 * @brief Base error implementation.
 * @file base_error.cpp
 * @author Julio C. Galindo (stickM4N)
 */
#include "../../../include/stick/error/base_error.hpp"

#if defined(_stick_lib_error_base_)


namespace stick {


	const_cstring base_error::what() const noexcept {
		return this->description();
	}


}   // namespace stick


#endif   //_stick_lib_error_base_
