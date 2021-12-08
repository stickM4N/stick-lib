/**
 * Scoped pointer to assert a correct dynamic memory usage.
 * @brief Pointer that is automatically deallocated once it goes ot of the
 * scope.
 * @file scoped_pointer.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_memory_scoped_pointer_)
#	define _stick_lib_memory_scoped_pointer_



#	include "../defines/types.hpp"


namespace stick {


	/**
	 * Class to handle pointers per scope and avoid leaking memory.
	 * @tparam type Type of the data to allocate.
	 */
	template<typename type>
	class scoped_pointer {

		type *ptr = nullptr;
		size_t allocated_elements = 0ul;

	public:
		/**
		 * Default constructor pointing to null;
		 */
		scoped_pointer() noexcept = default;
		/**
		 * Allocate pointer to new address with the given value.
		 * @param value Value to be copied to the new address.
		 */
		explicit scoped_pointer(const type &value) noexcept;
		/**
		 * Convert pointer to single value to scoped_pointer. Pointer will be
		 * deallocated when scoped_pointer is called!
		 * @param pointer Address of the value to be pointed.
		 * @return Self instance.
		 */
		scoped_pointer(const type *pointer) noexcept;
		/**
		 * Allocate a copy of the value(s) referenced by the given pointer.
		 * @param pointer Address of the values to be copied.
		 * @param element_amount Number of consecutive values to be copied.
		 */
		explicit scoped_pointer(const type *pointer,
		                        size_t element_amount = 1ul) noexcept;
		/**
		 * Copy constructor. Copy all data pointed by the target scoped_pointer.
		 * @param pointer Target pointer to copy.
		 */
		scoped_pointer(const scoped_pointer &pointer) noexcept;
		/**
		 * Move constructor. Move all data pointed by the target scoped_pointer
		 * and set it to nullptr.
		 * @param pointer Target pointer to move.
		 */
		scoped_pointer(scoped_pointer &&pointer) noexcept;

		/**
		 * Deallocate data.
		 */
		~scoped_pointer() noexcept;


		/**
		 * Allows the class to bea treated as a normal pointer.
		 * @return Direct pointer to the allocated data.
		 */
		operator type *() const noexcept;


		/**
		 * Assign a new value to the pointed data.
		 * @param [in] value Value to be assigned.
		 * @return Self instance.
		 */
		scoped_pointer &operator=(const type &value) noexcept;
		/**
		 * Convert pointer to single value to scoped_pointer. Pointer will be
		 * deallocated when scoped_pointer is called!
		 * @param pointer Address of the data to be pointed.
		 * @return Self instance.
		 */
		scoped_pointer &operator=(const type *pointer) noexcept;
		/**
		 * Copy data from another pointer.
		 * @param [in] pointer Scoped_pointer to be copied.
		 * @return Self instance.
		 */
		scoped_pointer &operator=(const scoped_pointer &pointer) noexcept;
		/**
		 * Move data from another pointer and clear it.
		 * @param [in,out] pointer Scoped_pointer to be moved and cleared.
		 * @return Self instance.
		 */
		scoped_pointer &operator=(scoped_pointer &&pointer) noexcept;
	};


}   // namespace stick


#	define _stick_lib_memory_scoped_pointer_impl_
#	include "../memory/scoped_pointer_impl.hpp"
#	undef _stick_lib_memory_scoped_pointer_impl_


#endif   //_stick_lib_memory_scoped_pointer_
