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
	 * Memory-managing error class.
	 */
	class out_of_range_error : public base_error {

		/**
		 * Stores the error description given by the programmer.
		 */
		cstring description_cache;

	public:
		explicit out_of_range_error(const_cstring description) noexcept;
		out_of_range_error(const out_of_range_error &error) noexcept;
		out_of_range_error(out_of_range_error &&error) noexcept;

		~out_of_range_error() noexcept override;


		/**
		 * Get the error description.
		 * @return Description cstring.
		 */
		const_cstring description() const noexcept override;
	};


}   // namespace stick



#endif   //_stick_lib_error_out_of_range_
