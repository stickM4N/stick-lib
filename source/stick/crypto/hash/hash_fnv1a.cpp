/**
 * Fowler–Noll–Vo(FNV) 1a hash algorithm. Implementation
 * @brief FNV-1a hash algorithm implementation.
 * @file hash_fnv1a.cpp
 * @author Julio C. Galindo (stickM4N)
 */
#include "../../../../include/stick/crypto/hash/hash_fnv1a.hpp"

#if defined(_stick_lib_crypto_hash_fnv1a_)


namespace stick {


	uint64_t hash_fnv1a::calculate_hash() const noexcept {

		switch (this->size()) {
		case hash_size::_8bit:
		case hash_size::_16bit:
			// These are not supported, they fall back to the smallest supported
			// size.
		case hash_size::_32bit: {
			uint32_t result = 0x811c9dc5;
			for (const auto &c : this->data())
				(result ^= c) *= 0x01000193;

			return result;
		}
		case hash_size::_128bit:
		case hash_size::_256bit:
		case hash_size::_512bit:
		case hash_size::_1024bit:
			// TODO implement after being able to handle bigger integers.
			// These are not supported (yet), they fall back to the biggest
			// supported size.
		case hash_size::_64bit: {
			uint64_t result = 0xcbf29ce484222325;
			for (const auto &c : this->data())
				(result ^= c) *= 0x00000100000001B3;

			return result;
		}
		}

		return 0ul;
	}


	hash_fnv1a::hash_fnv1a(const string &data, hash_size length)
	    : base_hash(data, length <= hash_size::_32bit ? hash_size::_32bit
	                                                  : hash_size::_64bit) { }


}   // namespace stick


#endif   //_stick_lib_crypto_hash_fnv1a_
