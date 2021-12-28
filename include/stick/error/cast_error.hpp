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

		/**
		 * Stores the error description given by the programmer.
		 */
		cstring description_cache;

	public:
		explicit cast_error(const_cstring description) noexcept;
		cast_error(const cast_error &error) noexcept;
		cast_error(cast_error &&error) noexcept;

		~cast_error() noexcept override;


		/**
		 * Get the error description.
		 * @return Description string.
		 */
		const_cstring description() const noexcept override;
	};


}   // namespace stick



#endif   //_stick_lib_error_cast_
