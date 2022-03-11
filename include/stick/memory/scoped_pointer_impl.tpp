/**
 * Scoped pointer. Template implementations.
 * @brief Scoped pointer template implementations.
 * @file scoped_pointer_impl.tpp
 * @author Julio C. Galindo (stickM4N)
 */
#if defined(_stick_lib_memory_scoped_pointer_impl_)


#	include "../error/out_of_range_error.hpp"
#	include "../memory/management.tpp"


namespace stick {


	template<typename type>
	scoped_pointer<type>::scoped_pointer(const type &value) noexcept
	    : ptr(allocate_value(value)), allocated_elements(1ul) { }
	template<typename type>
	scoped_pointer<type>::scoped_pointer(const type *pointer)
	    : ptr(const_cast<type *>(pointer)), allocated_elements(1ul) {
		if (this->is_null())
			throw memory_error(
			    "Creating a nullptr scoped_pointer from pointer, if this is "
			    "what was meant use default constructor instead.");
	}
	template<typename type>
	scoped_pointer<type>::scoped_pointer(const type *pointer,
	                                     size_t element_amount,
	                                     size_t extra_element_amount)
	    : allocated_elements(element_amount + extra_element_amount),
	      ptr(allocate<type>(element_amount + extra_element_amount)) {
		if (pointer == nullptr)
			throw memory_error("Creating a scoped_pointer and trying to copy "
			                   "values from a nullptr to it.");

		copy(pointer, this->ptr, element_amount);
	}
	template<typename type>
	scoped_pointer<type>::scoped_pointer(
	    const list_constexpr<type> &list) noexcept
	    : ptr(allocate<type>(list.size())) {
		for (const auto &e : list)
			this->ptr[this->allocated_elements++] = e;
	}
	template<typename type>
	scoped_pointer<type>::scoped_pointer(size_t element_amount, nullptr_t)
	    : allocated_elements(element_amount),
	      ptr(allocate<type>(element_amount)) { }
	template<typename type>
	scoped_pointer<type>::scoped_pointer(const scoped_pointer &pointer) noexcept
	    : allocated_elements(pointer.allocated_elements),
	      ptr(allocate<type>(pointer.allocated_elements)) {
		copy(pointer.ptr, this->ptr, pointer.allocated_elements);
	}
	template<typename type>
	scoped_pointer<type>::scoped_pointer(scoped_pointer &&pointer) noexcept
	    : ptr(pointer.ptr), allocated_elements(pointer.allocated_elements) {
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
		return this->ptr;
	}
	template<typename type>
	type *scoped_pointer<type>::end() const noexcept {
		return this->ptr + this->allocated_elements;
	}

	template<typename type>
	type *scoped_pointer<type>::rbegin() const noexcept {
		return this->end() - 1ul;
	}
	template<typename type>
	type *scoped_pointer<type>::rend() const noexcept {
		return this->begin() - 1ul;
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
	bool_t scoped_pointer<type>::is_null() const noexcept {
		return this->ptr == nullptr;
	}


	template<typename type>
	scoped_pointer<type>::operator type *() const noexcept {
		return this->ptr;
	}


	template<typename type>
	type &scoped_pointer<type>::operator[](ssize_t position) const {
		if (position < 0l)
			position = this->allocated_elements + position + 1;

		return this->operator[](static_cast<size_t>(position));
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
		if (this->is_null())
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
		this->allocated_elements = 1ul;

		return *this;
	}
	template<typename type>
	scoped_pointer<type> &
	scoped_pointer<type>::operator=(const list_constexpr<type> &list) noexcept {
		this->~scoped_pointer();

		this->ptr = allocate(list.size());
		for (const auto &e : list)
			this->ptr[this->allocated_elements++] = e;
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