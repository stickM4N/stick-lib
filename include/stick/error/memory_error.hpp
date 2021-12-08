/**
 * Memory error for access (read/write) exceptions.
 * @brief Memory error.
 * @file memory_error.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_error_memory_)
#	define _stick_lib_error_memory_



#	include "../error/base_error.hpp"


namespace stick {


	/**
	 * Memory-managing error class.
	 */
	class memory_error : public base_error {

		/**
		 * Stores the error description given by the programmer.
		 */
		cstring description_cache;

	public:
		explicit memory_error(const_cstring description) noexcept;
		memory_error(const memory_error &error) noexcept;
		memory_error(memory_error &&error) noexcept;

		~memory_error() noexcept override;


		/**
		 * Get the error description.
		 * @return Description cstring.
		 */
		const_cstring description() const noexcept override;
	};


}   // namespace stick



#endif   //_stick_lib_error_memory_
