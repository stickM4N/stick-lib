/**
 * Self-managed wide string class.
 * @brief Wide string class.
 * @file wstring.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_string_wstring_)
#	define _stick_lib_string_wstring_



#	include "../defines/types.hpp"
#	include "../memory/scoped_pointer.hpp"


namespace stick {


	class wstring {

		scoped_pointer<wchar_t> str;
		size_t str_size = 0ul;
		size_t pool_size = 0ul;

	public:
		/**
		 * Constructor for empty string.
		 */
		wstring() noexcept;
		/**
		 * Create a string with the given content and length.
		 * @param [in] str Content of the string.
		 * @param [in] length Length of the string.
		 * @param [in] pool_length Amount of reserved chars used on every string
		 * expansion.
		 */
		wstring(const_wcstring str, size_t length,
		        size_t pool_length = 0ul) noexcept;
		/**
		 * Create a string with the given content.
		 * @param [in] str Content of the string.
		 */
		wstring(const_wcstring str) noexcept;
		/**
		 * Create a string with repetitions of the same character.
		 * @param [in] c Character to fill the string.
		 * @param [in] repetitions Number of times the character will be
		 * repeated.
		 * @param [in] pool_length Amount of reserved chars used on every string
		 * expansion.
		 */
		explicit wstring(wchar_t c, size_t repetitions = 1ul,
		                 size_t pool_length = 0ul) noexcept;
		/**
		 * Create and empty string with reserved length.
		 * @param [in] length Length to reserve for the string.
		 * @param [in] pool_length Amount of reserved chars used on every string
		 * expansion.
		 */
		explicit wstring(size_t length, size_t pool_length = 0ul) noexcept;
		/**
		 * Copy constructor.
		 * @param [in] str String to copy from.
		 */
		wstring(const wstring &str) noexcept = default;
		/**
		 * Move constructor.
		 * @param [in,out] str String to move from and clear.
		 */
		wstring(wstring &&str) noexcept = default;

		/**
		 * Default destructor.
		 */
		~wstring() = default;


		/**
		 * Get the string content.
		 * @return The c-style string store.
		 */
		const_wcstring data() const noexcept;
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
		 * @param [in] str Content of the new string.
		 */
		wstring &operator=(const_wcstring str) noexcept;
		/**
		 * Copy content from other string.
		 * @param [in] str String to copy from.
		 */
		wstring &operator=(const wstring &str) noexcept;
		/**
		 * Move content from other string.
		 * @param [in,out] str String to move from and clear.
		 */
		wstring &operator=(wstring &&str) noexcept;
	};


}   // namespace stick



#endif   //_stick_lib_string_wstring_
