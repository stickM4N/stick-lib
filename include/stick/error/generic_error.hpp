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

		/**
		 * Stores the error description given by the programmer.
		 */
		cstring description_cache;

	public:
		explicit generic_error(const_cstring description) noexcept;
		generic_error(const generic_error &error) noexcept;
		generic_error(generic_error &&error) noexcept;

		~generic_error() noexcept override;


		/**
		 * Get the error description.
		 * @return Description string.
		 */
		const_cstring description() const noexcept override;
	};


}   // namespace stick



#endif   //_stick_lib_error_generic_
