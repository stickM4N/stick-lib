/**
 * Pair structure. Template implementations.
 * @brief Pair structure template implementations.
 * @file pair_impl.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if defined(_stick_lib_data_structures_pair_impl_)


#	include "../memory/management.hpp"


namespace stick {


	template<typename first_type, typename second_type>
	pair<first_type, second_type>::pair(first_type first,
	                                    second_type second) noexcept
	    : first_value(first), second_value(second) { }
	template<typename first_type, typename second_type>
	pair<first_type, second_type>::pair(const pair &pair) noexcept
	    : first_value(pair.first_value), second_value(pair.second_value) { }
	template<typename first_type, typename second_type>
	pair<first_type, second_type>::pair(pair &&pair) noexcept
	    : first_value(pair.first_value), second_value(pair.second_value) {
		pair.~pair();
	}

	template<typename first_type, typename second_type>
	pair<first_type, second_type>::~pair() noexcept {
		this->first_value.~first_type();
		this->second_value.~second_type();
	}


	template<typename first_type, typename second_type>
	first_type &pair<first_type, second_type>::first() const noexcept {
		return this->first_value;
	}
	template<typename first_type, typename second_type>
	second_type &pair<first_type, second_type>::second() const noexcept {
		return this->second_value;
	}


	template<typename first_type, typename second_type>
	pair<first_type, second_type> &
	pair<first_type, second_type>::operator=(const pair &pair) noexcept {
		this->first_value = pair.first_value;
		this->second_value = pair.second_value;

		return *this;
	}
	template<typename first_type, typename second_type>
	pair<first_type, second_type> &
	pair<first_type, second_type>::operator=(pair &&pair) noexcept {
		this->first_value = pair.first_value;
		this->second_value = pair.second_value;

		pair.~pair();

		return *this;
	}


}   // namespace stick


#else
#	warning This file is included automatically and should not be used on its own!
#endif   //_stick_lib_data_structures_pair_impl_
