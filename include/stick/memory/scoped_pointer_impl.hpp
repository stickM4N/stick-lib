/**
 * Scoped pointer. Template implementations.
 * @brief Scoped pointer template implementations.
 * @file scoped_pointer_impl.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if defined(_stick_lib_memory_scoped_pointer_impl_)


#	include "../memory/management.hpp"


namespace stick {


	template<typename type>
	scoped_pointer<type>::scoped_pointer(const type &value) noexcept {
		this->ptr = allocate<type>();
		this->allocated_elements = 1ul;
		copy(&value, this->ptr);
	}
	template<typename type>
	scoped_pointer<type>::scoped_pointer(const type *pointer) noexcept {
		this->ptr = const_cast<type *>(pointer);
		this->allocated_elements = 1;
	}
	template<typename type>
	scoped_pointer<type>::scoped_pointer(const type *pointer,
	                                     size_t element_amount) noexcept {
		this->ptr = allocate<type>(element_amount);
		this->allocated_elements = element_amount;
		copy(pointer, this->ptr, element_amount);
	}
	template<typename type>
	scoped_pointer<type>::scoped_pointer(
	    const scoped_pointer &pointer) noexcept {
		this->ptr = allocate<type>(pointer.allocated_elements);
		this->allocated_elements = pointer.allocated_elements;
		copy(pointer.ptr, this->ptr, pointer.allocated_elements);
	}
	template<typename type>
	scoped_pointer<type>::scoped_pointer(scoped_pointer &&pointer) noexcept {
		this->ptr = pointer.ptr;

		pointer.ptr = nullptr;
		pointer.allocated_elements = 0ul;
	}

	template<typename type>
	scoped_pointer<type>::~scoped_pointer() noexcept {
		if (this->ptr != nullptr)
			deallocate(this->ptr);
	}


	template<typename type>
	scoped_pointer<type>::operator type *() const noexcept {
		return this->ptr;
	}


	template<typename type>
	scoped_pointer<type> &
	scoped_pointer<type>::operator=(const type &value) noexcept {
		*this->ptr = value;

		return *this;
	}
	template<typename type>
	scoped_pointer<type> &
	scoped_pointer<type>::operator=(const type *pointer) noexcept {
		if (this->ptr != nullptr)
			deallocate(this->ptr);

		this->ptr = const_cast<type *>(pointer);

		return *this;
	}
	template<typename type>
	scoped_pointer<type> &
	scoped_pointer<type>::operator=(const scoped_pointer &pointer) noexcept {
		if (&pointer == this)
			return *this;

		if (this->ptr != nullptr)
			deallocate(this->ptr);

		this->ptr = allocate<type>(pointer.allocated_elements);
		this->allocated_elements = pointer.allocated_elements;
		copy(pointer.ptr, this->ptr, pointer.allocated_elements);

		return *this;
	}
	template<typename type>
	scoped_pointer<type> &
	scoped_pointer<type>::operator=(scoped_pointer &&pointer) noexcept {
		this->ptr = pointer.ptr;

		pointer.ptr = nullptr;
		pointer.allocated_elements = 0ul;

		return *this;
	}


}   // namespace stick


#else
#	warning This file is included automatically and should not be used on its own!
#endif   //_stick_lib_memory_scoped_pointer_impl_
