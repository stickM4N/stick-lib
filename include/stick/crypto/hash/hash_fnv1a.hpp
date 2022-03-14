/**
 * Fowler–Noll–Vo(FNV) 1a hash algorithm.
 * @brief FNV-1a hash algorithm.
 * @file hash_fnv1a.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_crypto_hash_fnv1a_)
#	define _stick_lib_crypto_hash_fnv1a_



#	include "../../crypto/hash/base_hash.hpp"


namespace stick {


	/**
	 * FNV-1a hashing handler.
	 */
	class hash_fnv1a final : public base_hash {

		uint64_t calculate_hash() const noexcept override;

	public:
		explicit hash_fnv1a(const string &data,
		                    hash_size length = hash_size::_64bit);
	};


}   // namespace stick



#endif   //_stick_lib_crypto_hash_fnv1a_
