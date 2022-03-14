/**
 * Base hash to derive all others from it. Implementation
 * @brief Base hash implementation.
 * @file base_hash.cpp
 * @author Julio C. Galindo (stickM4N)
 */
#include "../../../../include/stick/crypto/hash/base_hash.hpp"

#if defined(_stick_lib_crypto_hash_base_)


#	include "../../../../include/stick/templates/numeric.tpp"


namespace stick {


	base_hash::base_hash(const string &data, hash_size length) noexcept
	    : hash_data(data), hash_length(length), hash_result(0ul) { }

	base_hash::~base_hash() noexcept {
		this->hash_data.~string();
		this->hash_result = 0ul;
	}



	uint64_t base_hash::hash() noexcept {
		if (this->hash_result == 0ul)
			this->hash_result = this->calculate_hash();

		return this->hash_result;
	}

	string base_hash::hex_hash(bool_t prefix, bool_t caps) noexcept {
		if (this->hash_result == 0ul)
			this->hash_result = this->calculate_hash();

		string hex_hash;
		switch (this->size()) {
		case hash_size::_8bit:
			hex_hash = to_hex<uint8_t>(this->hash_result, prefix, caps);
			break;
		case hash_size::_16bit:
			hex_hash = to_hex<uint16_t>(this->hash_result, prefix, caps);
			break;
		case hash_size::_32bit:
			hex_hash = to_hex<uint32_t>(this->hash_result, prefix, caps);
			break;
		case hash_size::_128bit:
		case hash_size::_256bit:
		case hash_size::_512bit:
		case hash_size::_1024bit:
			// TODO: Pending to do data types able to hold this lengths.
		case hash_size::_64bit:
			hex_hash = to_hex<uint64_t>(this->hash_result, prefix, caps);
			break;
		}

		return hex_hash;
	}


	string base_hash::data() const noexcept {
		return this->hash_data;
	}

	hash_size base_hash::size() const noexcept {
		return this->hash_length;
	}


}   // namespace stick


#endif   //_stick_lib_error_base_
