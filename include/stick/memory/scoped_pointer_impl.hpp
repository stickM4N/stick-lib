/**
 * Scoped pointer. Template implementations.
 * @brief Scoped pointer template implementations.
 * @file scoped_pointer_impl.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if defined(_stick_lib_memory_scoped_pointer_impl_)


#	include "../error/out_of_range_error.hpp"
#	include "../memory/management.hpp"


namespace stick {


	template<typename type>
	scoped_pointer<type>::scoped_pointer(const type &value) noexcept {
		this->ptr = allocate_value(value);
		this->allocated_elements = 1ul;
	}
	template<typename type>
	scoped_pointer<type>::scoped_pointer(const type *pointer) noexcept {
		this->ptr = const_cast<type *>(pointer);
		this->allocated_elements = 1;
	}
	template<typename type>
	scoped_pointer<type>::scoped_pointer(const type *pointer,
	                                     size_t element_amount,
	                                     size_t extra_element_amount) noexcept {
		this->allocated_elements = element_amount + extra_element_amount;
		this->ptr = allocate<type>(this->allocated_elements);
		copy(pointer, this->ptr, element_amount);
	}
	template<typename type>
	scoped_pointer<type>::scoped_pointer(size_t element_amount) noexcept {
		this->allocated_elements = element_amount;
		this->ptr = allocate<type>(this->allocated_elements);
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
		this->~scoped_pointer();

		this->ptr = pointer.ptr;
		this->allocated_elements = pointer.allocated_elements;

		pointer.ptr = nullptr;
		pointer.allocated_elements = 0ul;
	}

	template<typename type>
	scoped_pointer<type>::~scoped_pointer() noexcept {
		if (this->ptr != nullptr)
			deallocate(this->ptr);

		this->allocated_elements = 0ul;
	}


	template<typename type>
	type *scoped_pointer<type>::begin() const noexcept {
		return &this->ptr[0];
	}
	template<typename type>
	type *scoped_pointer<type>::end() const noexcept {
		return &this->ptr[this->allocated_elements];
	}

	template<typename type>
	type *scoped_pointer<type>::rbegin() const noexcept {
		return &this->ptr[this->allocated_elements - 1];
	}
	template<typename type>
	type *scoped_pointer<type>::rend() const noexcept {
		return &this->ptr[0] - 1;
	}


	template<typename type>
	size_t scoped_pointer<type>::allocated_elems() const noexcept {
		return this->allocated_elements;
	}
	template<typename type>
	size_t scoped_pointer<type>::allocated_bytes() const noexcept {
		return this->allocated_elements * sizeof(type);
	}


	template<typename type>
	scoped_pointer<type>::operator type *() const noexcept {
		return this->ptr;
	}


	template<typename type>
	type &scoped_pointer<type>::operator[](ssize_t position) const {
		if (position >= 0) {
			if (this->allocated_elements <= position)
				throw out_of_range_error(
				    "Accessing a value outside the allocated memory section.");

			return this->ptr[position];
		} else {
			if (this->allocated_elements <= -position)
				throw out_of_range_error(
				    "Accessing a value outside the allocated memory section.");

			return this->ptr[this->allocated_elements + position];
		}
	}
	template<typename type>
	type &scoped_pointer<type>::operator[](size_t position) const {
		if (this->allocated_elements <= position)
			throw out_of_range_error(
			    "Accessing a value outside the allocated memory section.");

		return this->ptr[position];
	}
	template<typename type>
	type &scoped_pointer<type>::operator[](int32_t position) const {
		return this->operator[](static_cast<ssize_t>(position));
	}
	template<typename type>
	type &scoped_pointer<type>::operator[](uint32_t position) const {
		return this->operator[](static_cast<size_t>(position));
	}

	template<typename type>
	scoped_pointer<type> &
	scoped_pointer<type>::operator=(const type &value) noexcept {
		if (this->ptr == nullptr)
			this->ptr = allocate_value(value);
		else
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
		this->~scoped_pointer();

		this->ptr = pointer.ptr;
		this->allocated_elements = pointer.allocated_elements;

		pointer.ptr = nullptr;
		pointer.allocated_elements = 0ul;

		return *this;
	}


}   // namespace stick


#else
#	warning This file is included automatically and should not be used on its own!
#endif   //_stick_lib_memory_scoped_pointer_impl_