/**
 * Casting exceptions.
 * @brief Cast error.
 * @file cast_error.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_error_cast_)
#	define _stick_lib_error_cast_



#	include "../error/base_error.hpp"


namespace stick {


	/**
	 * Memory-managing error class.
	 */
	class cast_error : public base_error {

	public:
		explicit cast_error(const_cstring description) noexcept;
		explicit cast_error(const string &description) noexcept;


		string description() const noexcept override;
	};


}   // namespace stick



#endif   //_stick_lib_error_cast_
