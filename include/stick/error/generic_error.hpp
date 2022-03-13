/**
 * Generic error for non-specific exceptions.
 * @brief Generic error.
 * @file generic_error.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_error_generic_)
#	define _stick_lib_error_generic_



#	include "../error/base_error.hpp"


namespace stick {


	/**
	 * Generic error class.
	 */
	class generic_error : public base_error {

	public:
		explicit generic_error(const_cstring description) noexcept;
		explicit generic_error(const string &description) noexcept;


		string description() const noexcept override;
	};


}   // namespace stick



#endif   //_stick_lib_error_generic_
