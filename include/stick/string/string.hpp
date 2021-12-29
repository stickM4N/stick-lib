/**
 * Self-managed string class.
 * @brief String class.
 * @file string.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_string_string_)
#	define _stick_lib_string_string_



#	include "../defines/types.hpp"
#	include "../memory/scoped_pointer.hpp"


namespace stick {


	class string {

		scoped_pointer<char_t> str;
		size_t str_size = 0ul;
		size_t pool_size = 0ul;

	public:
		/**
		 * Constructor for empty string.
		 */
		string() noexcept;
		/**
		 * Create a string with the given content and length.
		 * @param [in] string Content of the string.
		 * @param [in] length Length of the string.
		 * @param [in] pool_length Amount of reserved chars used on every string
		 * expansion.
		 * @throw memory_error when copying from a nullptr or pooling +2Gbytes.
		 */
		string(const_cstring string, size_t length, size_t pool_length = 0ul);
		/**
		 * Create a string with the given content.
		 * @param [in] string Content of the string.
		 * @throw memory_error when copying from a nullptr.
		 */
		string(const_cstring string);
		/**
		 * Create a string with repetitions of the same character.
		 * @param [in] c Character to fill the string.
		 * @param [in] repetitions Number of times the character will be
		 * repeated.
		 * @param [in] pool_length Amount of reserved chars used on every string
		 * expansion.
		 * @throw memory_error when pooling +2Gbytes.
		 */
		explicit string(char_t c, size_t repetitions = 1ul,
		                size_t pool_length = 0ul);
		/**
		 * Create and empty string with reserved length.
		 * @param [in] length Length to reserve for the string.
		 * @param [in] pool_length Amount of reserved chars used on every string
		 * expansion.
		 */
		explicit string(size_t length, size_t pool_length = 0ul) noexcept;
		/**
		 * Copy constructor.
		 * @param [in] string String to copy from.
		 */
		string(const string &string) noexcept = default;
		/**
		 * Move constructor.
		 * @param [in,out] string String to move from and clear.
		 */
		string(string &&string) noexcept = default;

		/**
		 * Default destructor.
		 */
		~string() = default;


		/**
		 * Get the string content.
		 * @return The c-style string store.
		 */
		const_cstring data() const noexcept;
		/**
		 * Get the length of the stored string.
		 * @return The length of the sored string.
		 */
		size_t length() const noexcept;
		/**
		 * Get the total allocated memory for the string.
		 * @return The number of allocated chars of the string.
		 */
		size_t allocated_chars() const noexcept;

		/**
		 * Set the reserved size of the string on every expansion.
		 * @param [in] length Number of chars to reserve on every string
		 * expansion.
		 */
		void set_pool(size_t length) noexcept;
		/**
		 * Expand the string a specific number of characters.
		 * @param [in] length Number of bytes to expand.
		 */
		void expand(size_t length) noexcept;


		/**
		 * Replace stored string with a new content.
		 * @param [in] string Content of the new string.
		 */
		string &operator=(const_cstring string) noexcept;
		/**
		 * Copy content from other string.
		 * @param [in] string String to copy from.
		 */
		string &operator=(const string &string) noexcept = default;
		/**
		 * Move content from other string.
		 * @param [in,out] string String to move from and clear.
		 */
		string &operator=(string &&string) noexcept;
	};


}   // namespace stick



#endif   //_stick_lib_string_string_
