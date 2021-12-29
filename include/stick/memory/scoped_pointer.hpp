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

		type *ptr;
		size_t allocated_elements;

	public:
		/**
		 * Default constructor pointing to null.
		 */
		scoped_pointer() noexcept;
		/**
		 * Allocate pointer to new address with the given value.
		 * @param [in] value Value to be copied to the new address.
		 */
		scoped_pointer(const type &value) noexcept;
		/**
		 * Convert pointer to single value to scoped_pointer. Pointer will be
		 * deallocated when scoped_pointer is called!
		 * @param [in] pointer Address of the value to be pointed.
		 * @throw memory_error when copying a nullptr.
		 * @return Self instance.
		 */
		scoped_pointer(const type *pointer);
		/**
		 * Allocate a copy of the value(s) referenced by the given pointer.
		 * @param [in] pointer Address of the values to be copied.
		 * @param [in] element_amount Number of consecutive values to be copied.
		 * @param [in] extra_element_amount Number extra elements to be
		 * allocated. Default = 0.
		 * @throw memory_error when copying from a nullptr or allocating 0 byte.
		 */
		explicit scoped_pointer(const type *pointer, size_t element_amount,
		                        size_t extra_element_amount = 0ul);
		/**
		 * Allocate elements without assigning any value.
		 * @param [in] element_amount Number of elements to allocate.
		 * @throw memory_error when allocating 0 byte.
		 */
		explicit scoped_pointer(size_t element_amount);
		/**
		 * Copy constructor. Copy all data pointed by the target scoped_pointer.
		 * @param [in] pointer Target pointer to copy.
		 */
		scoped_pointer(const scoped_pointer &pointer) noexcept;
		/**
		 * Move constructor. Move all data pointed by the target scoped_pointer
		 * and set it to nullptr.
		 * @param [in,out] pointer Target pointer to move.
		 */
		scoped_pointer(scoped_pointer &&pointer) noexcept;

		/**
		 * Deallocate data.
		 */
		~scoped_pointer() noexcept;


		/**
		 * Begin iterator.
		 * @return Pointer to the first element.
		 */
		type *begin() const noexcept;
		/**
		 * End iterator.
		 * @return Pointer to one element after the last.
		 */
		type *end() const noexcept;

		/**
		 * Reverse begin iterator.
		 * @return Pointer to the last element.
		 */
		type *rbegin() const noexcept;
		/**
		 * Revere end iterator.
		 * @return Pointer to one element before the first.
		 */
		type *rend() const noexcept;


		/**
		 * Get the amount of allocated elements.
		 * @return Number of allocated elements.
		 */
		size_t allocated_elems() const noexcept;
		/**
		 * Get the amount of allocated bytes.
		 * @return Number of allocated bytes.
		 */
		size_t allocated_bytes() const noexcept;

		/**
		 * Check if is nullptr.
		 * @return True if is nullptr, false otherwise.
		 */
		bool_t is_null() const noexcept;


		/**
		 * Allows the class to bea treated as a normal pointer.
		 * @return Direct pointer to the allocated data.
		 */
		operator type *() const noexcept;


		/**
		 * Get the value of the given position. Negative integers start from the
		 * last allocated value.
		 * @param [in] position Position of the value to return.
		 * @throw out_of_range_error when accessing a value outside the
		 * allocated memory space.
		 * @return The value stored in the given position.
		 */
		type &operator[](ssize_t position) const;
		/**
		 * Get the value of the given position.
		 * @param [in] position Position of the value to return.
		 * @throw out_of_range_error when accessing a value outside the
		 * allocated memory space.
		 * @return The value stored in the given position.
		 */
		type &operator[](size_t position) const;
		/**
		 * Get the value of the given position. Negative integers start from the
		 * last allocated value. Exists for typical values.
		 * @param [in] position Position of the value to return.
		 * @throw out_of_range_error when accessing a value outside the
		 * allocated memory space.
		 * @return The value stored in the given position.
		 */
		type &operator[](int32_t position) const;
		/**
		 * Get the value of the given position. Exists for typical values.
		 * @param [in] position Position of the value to return.
		 * @throw out_of_range_error when accessing a value outside the
		 * allocated memory space.
		 * @return The value stored in the given position.
		 */
		type &operator[](uint32_t position) const;

		/**
		 * Assign a new value to the pointed data.
		 * @param [in] value Value to be assigned.
		 * @return Self instance.
		 */
		scoped_pointer &operator=(const type &value) noexcept;
		/**
		 * Convert pointer to single value to scoped_pointer. Pointer will be
		 * deallocated when scoped_pointer is called!
		 * @param [in] pointer Address of the data to be pointed.
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