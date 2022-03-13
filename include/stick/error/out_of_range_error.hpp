/**
 * Out-of-range exception.
 * @brief Out-of-range error.
 * @file out_of_range_error.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_error_out_of_range_)
#	define _stick_lib_error_out_of_range_



#	include "../error/base_error.hpp"


namespace stick {


	/**
	 * Out-of-range error class.
	 */
	class out_of_range_error : public base_error {

	public:
		explicit out_of_range_error(const_cstring description) noexcept;
		explicit out_of_range_error(const string &description) noexcept;


		string description() const noexcept override;
	};


}   // namespace stick



#endif   //_stick_lib_error_out_of_range_
