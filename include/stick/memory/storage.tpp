/**
 * Data storage structure to allocate aligned data.
 * @brief Memory data storage with alignment.
 * @file storage.tpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_memory_storage_)
#	define _stick_lib_memory_storage_



#	include "../defines/types.hpp"


namespace stick {


	/**
	 * Memory structure.
	 * @tparam size How much memory will the structure occupy.
	 */
	template<size_t size>
	struct storage {

	public:
		byte_t data[size];
	};

	/**
	 * Aligned memory structure.
	 * @tparam size How much memory will the structure occupy.
	 * @tparam alignment The alignment the structure should have when allocated.
	 */
	template<size_t size, size_t alignment = alignof(byte_t)>
	struct storage_aligned {

	public:
		alignas(alignment) byte_t data[size];
	};


}   // namespace stick



#endif   //_stick_lib_memory_storage_
