/**
 * Hybrid FIFO-LIFO array. Template implementations.
 * @brief Hybrid array template implementations.
 * @file array_impl.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if defined(_stick_lib_data_structures_array_impl_)


#	include "../error/out_of_range_error.hpp"
#	include "../memory/management.hpp"
#	include "../templates/reference.hpp"


namespace stick {


	template<typename type>
	typename array<type>::move_decision_result
	array<type>::make_move_decision(size_t position) const noexcept {

		bool_t prefer_moving_back = this->size() - position <= position;

		if (prefer_moving_back) {
			if (this->available_back_pool() != 0ul)
				return move_decision_result::move_back;
			else if (this->available_front_pool() != 0ul)
				return move_decision_result::move_front;
		} else {
			if (this->available_front_pool() != 0ul)
				return move_decision_result::move_front;
			else if (this->available_back_pool() != 0ul)
				return move_decision_result::move_back;
		}

		if (prefer_moving_back) {
			return move_decision_result::expand_and_move_back;
		} else {
			return move_decision_result::expand_and_move_front;
		}
	}


	template<typename type>
	size_t array<type>::first_position() const noexcept {
		return this->data_start;
	}
	template<typename type>
	size_t array<type>::last_position() const noexcept {
		return this->data_start + this->data_size - 1;
	}


	template<typename type>
	type *array<type>::allocated_begin() const noexcept {
		return this->data.begin();
	}
	template<typename type>
	type *array<type>::allocated_end() const noexcept {
		return this->data.end();
	}

	template<typename type>
	type *array<type>::allocated_rbegin() const noexcept {
		return this->data.rbegin();
	}
	template<typename type>
	type *array<type>::allocated_rend() const noexcept {
		return this->data.rend();
	}


	template<typename type>
	array<type>::array(const type *array, size_t length)
	    : data(array, length), data_size(length) { }
	template<typename type>
	array<type>::array(size_t size, size_t front_pool_length,
	                   size_t back_pool_length)
	    : data(front_pool_length + size + back_pool_length),
	      front_pool(front_pool_length), back_pool(back_pool_length),
	      data_start(front_pool_length) { }
	template<typename type>
	array<type>::array(array &&array) noexcept {
		this->data = move(array.data);
		this->data_start = array.data_start;
		this->data_size = array.data_size;
		this->front_pool = array.front_pool;
		this->back_pool = array.back_pool;

		array.data_start = 0ul;
		array.data_size = 0ul;
		array.front_pool = 0ul;
		array.back_pool = 0ul;
	}

	template<typename type>
	array<type>::~array() noexcept {
		this->data.~scoped_pointer();
		this->data_start = 0ul;
		this->data_size = 0ul;
		this->front_pool = 0ul;
		this->back_pool = 0ul;
	}


	template<typename type>
	type *array<type>::begin() const noexcept {
		return &this->data[this->first_position()];
	}
	template<typename type>
	type *array<type>::end() const noexcept {
		if (this->empty())
			return this->begin();
		else
			return &this->data[this->last_position()];
	}

	template<typename type>
	type *array<type>::rbegin() const noexcept {
		if (this->empty())
			return this->rend();
		else
			return &this->data[this->last_position()];
	}
	template<typename type>
	type *array<type>::rend() const noexcept {
		return &this->data[this->first_position()] - 1ul;
	}


	template<typename type>
	size_t array<type>::size() const noexcept {
		return this->data_size;
	}
	template<typename type>
	size_t array<type>::allocated_size() const noexcept {
		return this->data.allocated_elems();
	}
	template<typename type>

	size_t array<type>::available_front_pool() const noexcept {
		return this->first_position();
	}
	template<typename type>
	size_t array<type>::available_back_pool() const noexcept {
		return this->allocated_size() - this->last_position();
	}

	template<typename type>
	bool_t array<type>::empty() const noexcept {
		return this->size() == 0ul;
	}


	template<typename type>
	array<type> &array<type>::set_front_pool(size_t size) noexcept {
		this->front_pool = size;

		return *this;
	}
	template<typename type>
	array<type> &array<type>::set_back_pool(size_t size) noexcept {
		this->back_pool = size;

		return *this;
	}


	template<typename type>
	array<type> &array<type>::expand(size_t front_size,
	                                 size_t back_size) noexcept {
		array<type> tempy(this->allocated_size(), front_size, back_size);

		if (not this->empty())
			for (const type &e : *this)
				tempy.push_back(e);

		*this = move(tempy);

		return *this;
	}
	template<typename type>
	array<type> &array<type>::expand_front(size_t size) noexcept {
		return this->expand(size, 0ul);
	}
	template<typename type>
	array<type> &array<type>::expand_back(size_t size) noexcept {
		return this->expand(0ul, size);
	}


	template<typename type>
	array<type> &array<type>::compact(size_t front_size,
	                                  size_t back_size) noexcept {
		if (this->size() == this->allocated_size())
			return *this;

		if (this->available_front_pool() <= front_size)
			front_size = 0ul;
		else
			front_size = this->available_front_pool() - front_size;

		if (this->available_back_pool() <= back_size)
			back_size = 0ul;
		else
			back_size = this->available_back_pool() - back_size;

		if (front_size + this->size() + back_size != 0ul) {
			array<type> tempy(this->size(), front_size, back_size);
			for (const auto &e : *this)
				tempy.push_back(e);

			*this = move(tempy);
		} else {
			this->data.~scoped_pointer();
			this->data_start = 0ul;
			this->data_size = 0ul;
		}

		return *this;
	}
	template<typename type>
	array<type> &array<type>::compact_front(size_t size) noexcept {
		return this->compact(size, 0ul);
	}
	template<typename type>
	array<type> &array<type>::compact_back(size_t size) noexcept {
		return this->compact(0ul, size);
	}


	template<typename type>
	array<type> &array<type>::push(const type &value, ssize_t position) {
		if (position < 0l)
			position = this->last_position() + position + 1l;

		return this->push(value, static_cast<size_t>(position));
	}
	template<typename type>
	array<type> &array<type>::push(const type &value, size_t position) {
		if (this->size() < position)
			throw out_of_range_error("Push-ing a value outside the array.");


		switch (this->make_move_decision(position)) {

		case move_decision_result::expand_and_move_back:
			this->expand_back(this->back_pool + 1ul);
		case move_decision_result::move_back:
			move(this->begin() + position, this->begin() + position + 1ul,
			     this->size() - position, false);
			this->data_size++;
			this->operator[](position) = value;

			break;
		case move_decision_result::expand_and_move_front:
			this->expand_front(this->back_pool + 1ul);
		case move_decision_result::move_front:
			move(this->begin(), this->begin() - position - 1ul, position + 1ul,
			     false);
			this->data_start--;
			this->data_size++;
			this->operator[](position) = value;

			break;
		}

		return *this;
	}
	template<typename type>
	array<type> &array<type>::push(const type &value, int32_t position) {
		return this->push(value, static_cast<ssize_t>(position));
	}
	template<typename type>
	array<type> &array<type>::push(const type &value, uint32_t position) {
		return this->push(value, static_cast<size_t>(position));
	}
	template<typename type>
	array<type> &array<type>::push_front(const type &value) noexcept {
		return this->push(value, 0ul);
	}
	template<typename type>
	array<type> &array<type>::push_back(const type &value) noexcept {
		return this->push(value, this->size());
	}


	template<typename type>
	array<type> &array<type>::pop(ssize_t position) {
		if (position < 0l)
			position = this->last_position() + position + 1l;

		return this->pop(static_cast<size_t>(position));
	}
	template<typename type>
	array<type> &array<type>::pop(size_t position) {
		if (this->size() <= position)
			throw out_of_range_error("Pop-ing a value outside the array.");

		switch (this->make_move_decision(position)) {

		case move_decision_result::expand_and_move_back:
		case move_decision_result::move_back:
			move(this->begin() + position + 1ul, this->begin() + position,
			     this->size() - position - 1ul, false);
			break;
		case move_decision_result::expand_and_move_front:
		case move_decision_result::move_front:
			move(this->begin(), this->begin() + 1ul, position, false);
			this->data_start++;
			break;
		}
		this->data_size--;

		return *this;
	}
	template<typename type>
	array<type> &array<type>::pop(int32_t position) {
		return this->pop(static_cast<ssize_t>(position));
	}
	template<typename type>
	array<type> &array<type>::pop(uint32_t position) {
		return this->pop(static_cast<size_t>(position));
	}
	template<typename type>
	array<type> &array<type>::pop_front() {
		return this->pop(0ul);
	}
	template<typename type>
	array<type> &array<type>::pop_back() {
		return this->pop(-1ul);
	}


	template<typename type>
	array<type> &array<type>::clear() noexcept {
		this->data_size = 0ul;

		return *this;
	}


	template<typename type>
	type &array<type>::operator[](ssize_t position) const {
		if (position < 0l)
			position = this->last_position() + position + 1l;

		return this->operator[](static_cast<size_t>(position));
	}
	template<typename type>
	type &array<type>::operator[](size_t position) const {
		if (this->size() <= position)
			throw out_of_range_error("Accessing a value outside the array.");

		return this->data[this->first_position() + position];
	}
	template<typename type>
	type &array<type>::operator[](int32_t position) const {
		return this->operator[](static_cast<ssize_t>(position));
	}
	template<typename type>
	type &array<type>::operator[](uint32_t position) const {
		return this->operator[](static_cast<size_t>(position));
	}

	template<typename type>
	array<type> &array<type>::operator=(array &&array) noexcept {
		this->data = move(array.data);
		this->data_start = array.data_start;
		this->data_size = array.data_size;
		this->front_pool = array.front_pool;
		this->back_pool = array.back_pool;

		array.data_start = 0ul;
		array.data_size = 0ul;
		array.front_pool = 0ul;
		array.back_pool = 0ul;

		return *this;
	}


	template<typename type>
	array<type>::operator type *() const noexcept {
		return this->data;
	}


}   // namespace stick


#else
#	warning This file is included automatically and should not be used on its own!
#endif   //_stick_lib_data_structures_array_impl_
