/**
 * Fowler–Noll–Vo(FNV) 1 hash algorithm.
 * @brief FNV-1 hash algorithm.
 * @file hash_fnv1.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_crypto_hash_fnv1_)
#	define _stick_lib_crypto_hash_fnv1_



#	include "../../crypto/hash/base_hash.hpp"


namespace stick {


	/**
	 * FNV-1 hashing handler.
	 */
	class hash_fnv1 final : public base_hash {

		uint64_t calculate_hash() const noexcept override;

	public:
		explicit hash_fnv1(const string &data,
		                   hash_size length = hash_size::_64bit);
	};


}   // namespace stick



#endif   //_stick_lib_crypto_hash_fnv1_
