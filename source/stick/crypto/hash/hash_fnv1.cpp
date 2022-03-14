/**
 *Fowler–Noll–Vo(FNV) 1 hash algorithm. Implementation
 * @brief FNV-1 hash algorithm implementation.
 * @file hash_fnv1.cpp
 * @author Julio C. Galindo (stickM4N)
 */
#include "../../../../include/stick/crypto/hash/hash_fnv1.hpp"

#if defined(_stick_lib_crypto_hash_fnv1_)


namespace stick {


	uint64_t hash_fnv1::calculate_hash() const noexcept {

		switch (this->size()) {
		case hash_size::_8bit:
		case hash_size::_16bit:
			// These are not supported, they fall back to the smallest supported
			// size.
		case hash_size::_32bit: {
			uint32_t result = 0x811c9dc5;
			for (const auto &c : this->data())
				(result *= 0x01000193) ^= c;

			return result;
		}
		case hash_size::_128bit:
		case hash_size::_256bit:
		case hash_size::_512bit:
		case hash_size::_1024bit:
			// TODO: Implement after being able to handle bigger integers.
			// These are not supported (yet), they fall back to the biggest
			// supported size.
		case hash_size::_64bit: {
			uint64_t result = 0xcbf29ce484222325;
			for (const auto &c : this->data())
				(result *= 0x00000100000001B3) ^= c;

			return result;
		}
		}

		return 0ul;
	}


	hash_fnv1::hash_fnv1(const string &data, hash_size length)
	    : base_hash(data, length <= hash_size::_32bit ? hash_size::_32bit
	                                                  : hash_size::_64bit) { }


}   // namespace stick


#endif   //_stick_lib_crypto_hash_fnv1_
