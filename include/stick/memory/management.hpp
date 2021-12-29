/**
 * Memory management utilities. Allocation, deallocation, set, copy, move and
 * clear dynamic memory.
 * @brief Memory management.
 * @file management.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_memory_management_)
#	define _stick_lib_memory_management_



#	include "../defines/types.hpp"


namespace stick {


	/**
	 * Dynamic memory allocation. Minimum 1 byte. Maximum < 2 GigaBytes.
	 * @tparam type Data type to allocate. Default = byte_t.
	 * @param [in] element_amount Number of elements to be allocated.
	 * Default = 1.
	 * @return Pointer to the newly allocated memory space.
	 * @throw memory_error when memory cannot be allocated.
	 */
	template<typename type = byte_t>
	inline type *allocate(size_t element_amount = 1ul);

	/**
	 * Dynamic value allocation.
	 * @tparam type Data type to allocate. Default = byte_t.
	 * @param [in] value To be allocated dynamically.
	 * @return Pointer to the newly allocated value.
	 * @throw memory_error when memory cannot be allocated.
	 */
	template<typename type = byte_t>
	inline type *allocate_value(const type &value);

	/**
	 * Dynamic and aligned memory allocation. Minimum 1 byte.
	 * Maximum < 2 GigaBytes.
	 * @tparam type Data type to allocate. Default = byte_t.
	 * @tparam alignment Alignment the allocated memory should have.
	 * @param [in] element_amount Number of elements to be allocated.
	 * Default = 1.
	 * @return Pointer to the newly allocated memory space.
	 * @throw memory_error when memory cannot be allocated.
	 */
	template<typename type = byte_t, size_t alignment = alignof(type)>
	inline type *allocate_aligned(size_t element_amount = 1ul);

	/**
	 * Deallocate memory and make pointer null.
	 * @tparam type Data type of the pointer to deallocate.
	 * @param [in,out] data Pointer to deallocate and make null.
	 * @throw memory_error when memory cannot be deallocated or was previously
	 * deallocated.
	 */
	template<typename type>
	inline void_t deallocate(type *&data);

	/**
	 * Set content of the given address to a specific value.
	 * @tparam type Type of the pointer and value to copy. Default = byte_t.
	 * @param [in] address Pointer to the value to overwrite.
	 * @param [in] value Value to overwrite with the type pointed by address.
	 * @param [in] element_amount Number of consecutive elements to be
	 * overwritten by value. Default = 1.
	 */
	template<typename type = byte_t>
	inline void_t set(type *address, const type &value,
	                  size_t element_amount = 1) noexcept;
	/**
	 * Set the bytes of the content of the given address to a specific value.
	 * @tparam type Type of the pointer and value to copy. Default = byte_t.
	 * @param [in] address Pointer to the value to overwrite.
	 * @param [in] value Value to copy in each byte of the type data pointed by
	 * address.
	 * @param [in] element_amount Number of consecutive elements to be
	 * overwritten by value. Default = 1.
	 */
	template<typename type = byte_t>
	inline void_t set(type *address, const byte_t &value,
	                  size_t element_amount = 1) noexcept;


	/**
	 * Sets all the bytes to null.
	 * @tparam type Type of the data pointed to. Default = byte_t.
	 * @param [in] address Pointer to the data to be nullified.
	 * @param [in] element_amount Number of consecutive elements of type to be
	 * nullified. Default = 1.
	 */
	template<typename type = byte_t>
	inline void_t clear(type *address, size_t element_amount = 1ul) noexcept;

	/**
	 * Copy memory data from one address to another.
	 * @tparam type Type of the data to be copied. Default = byte_t.
	 * @param [in] source_address Pointer to the data to be copied from.
	 * @param [in] destination_address Pointer to the data to be copied to.
	 * @param [in] element_amount Number of consecutive data elements to be
	 * copied from the source. Default = 1.
	 * @throw memory_error when destination data will overwrite source data.
	 */
	template<typename type = byte_t>
	inline void_t copy(const type *source_address, type *destination_address,
	                   size_t element_amount = 1ul);

	/**
	 * Move memory data from one address to another and nullify source data.
	 * @tparam type Type of the data to be moved. Default = byte_t.
	 * @param [in] source_address Pointer to the data to be moved from.
	 * @param [in] destination_address Pointer to the data to be moved to.
	 * @param [in] element_amount Number of consecutive data elements to be
	 * moved from the source. Default = 1.
	 * @param [in] set_null Set memory to null when moved. Default = true.
	 */
	template<typename type = byte_t>
	inline void_t move(type *source_address, type *destination_address,
	                   size_t element_amount = 1ul,
	                   bool_t set_null = true) noexcept;


}   // namespace stick


#	define _stick_lib_memory_management_impl_
#	include "../memory/management_impl.hpp"
#	undef _stick_lib_memory_management_impl_


#endif   //_stick_lib_memory_management_
