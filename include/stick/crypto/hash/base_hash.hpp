/**
 * Base hash to derive all others from it.
 * @brief Base hash.
 * @file base_hash.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_crypto_hash_base_)
#	define _stick_lib_crypto_hash_base_



#	include "../../defines/types.hpp"
#	include "../../string/string.hpp"


namespace stick {


	/**
	 * Possible sizes of the implemented hash.
	 */
	enum class hash_size : uint8_t {
		_8bit,
		_16bit,
		_32bit,
		_64bit,
		_128bit,
		_256bit,
		_512bit,
		_1024bit
	};


	/**
	 * Base hash to implement all algorithms over it.
	 */
	class base_hash {

		string hash_data;   ///< String which was hashed.
		uint64_t hash_result;   ///< The hashing result
		hash_size hash_length;   ///< The length of the implemented hash.

	protected:
		/**
		 * Basic constructor for hash data.
		 */
		base_hash(const string &data, hash_size length) noexcept;


		/**
		 * How to calculate hash. Should be implemented in all derived classes
		 * since they are the ones to implement the specific hashing algorithm.
		 * Must return the hash result!
		 */
		virtual uint64_t calculate_hash() const noexcept = 0;

	public:
		/**
		 * Destructor.
		 */
		~base_hash() noexcept;


		/**
		 * Get the integer hash result.
		 * @return Calculated hash integer.
		 */
		uint64_t hash() noexcept;

		/**
		 * Get the hash as a hexadecimal string.
		 * @param [in] prefix If the string should have 0x prefix.
		 * @param [in] caps If the hex string should be in capital letters.
		 * @return The hash as a hex string.
		 */
		string hex_hash(bool_t prefix = false, bool_t caps = false) noexcept;


		/**
		 * Get the indicated hash data.
		 * @return string with the data to be hashed.
		 */
		string data() const noexcept;
		/**
		 * Get the indicated hash size.
		 * @return hash_size enum element indicating the size of the hash.
		 */
		hash_size size() const noexcept;
	};


}   // namespace stick



#endif   //_stick_lib_crypto_hash_base_
