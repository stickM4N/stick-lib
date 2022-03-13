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

	public:
		explicit memory_error(const_cstring description) noexcept;
		explicit memory_error(const string &description) noexcept;


		string description() const noexcept override;
	};


}   // namespace stick



#endif   //_stick_lib_error_memory_
