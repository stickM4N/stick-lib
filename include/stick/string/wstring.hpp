/**
 * Self-managed wide string class.
 * @brief Wide string class.
 * @file wstring.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_string_wstring_)
#	define _stick_lib_string_wstring_



#	include "../data_structures/array.tpp"
#	include "../defines/types.hpp"
#	include "../memory/scoped_pointer.tpp"


namespace stick {


	/**
	 * String class to easily manage char arrays.
	 */
	class wstring {

		scoped_pointer<wchar_t> data;
		size_t data_size = 0ul;
		size_t pool = 0ul;

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
		 * @throw memory_error when copying from a nullptr or pooling +2Gbytes.
		 */
		wstring(const_wcstring str, size_t length, size_t pool_length = 0ul);
		/**
		 * Create a string with the given content.
		 * @param [in] str Content of the string.
		 * @throw memory_error when copying from a nullptr.
		 */
		wstring(const_wcstring str);
		/**
		 * Append the given char to this string.
		 * @param [in] c Char to append.
		 * @return Self instance.
		 */
		wstring &append(wchar_t c);
		/**
		 * Create a string with repetitions of the same character.
		 * @param [in] c Character to fill the string.
		 * @param [in] repetitions Number of times the character will be
		 * repeated.
		 * @param [in] pool_length Amount of reserved chars used on every string
		 * expansion.
		 * @throw memory_error when pooling +2Gbytes.
		 */
		explicit wstring(wchar_t c, size_t repetitions = 1ul,
		                 size_t pool_length = 0ul);
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
		 * Reset the string to its bare state.
		 */
		~wstring() noexcept;


		/**
		 * Begin iterator.
		 * @return Pointer to the first element.
		 */
		wchar_t *begin() const noexcept;
		/**
		 * End iterator.
		 * @return Pointer to one element after the last.
		 */
		wchar_t *end() const noexcept;

		/**
		 * Reverse begin iterator.
		 * @return Pointer to the last element.
		 */
		wchar_t *rbegin() const noexcept;
		/**
		 * Reverse end iterator.
		 * @return Pointer to one element before the first.
		 */
		wchar_t *rend() const noexcept;


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
		 * Get the amount of characters allocated but not in use.
		 * @return Number of unused allocated characters.
		 */
		size_t available_pool() const noexcept;

		/**
		 * Check if the string is empty.
		 * @return True if the string is empty, false otherwise.
		 */
		bool_t empty() const noexcept;


		/**
		 * Set the reserved size of the string on every expansion.
		 * @param [in] length Number of chars to reserve on every string
		 * expansion.
		 * @return Self instance.
		 */
		wstring &set_pool(size_t length) noexcept;


		/**
		 * Expand the string a specific number of characters.
		 * @param [in] length Number of bytes to expand.
		 * @return Self instance.
		 */
		wstring &expand(size_t length) noexcept;

		/**
		 * Reduce the allocated size of the string without changing its content.
		 * @param [in] size Max number of characters to deallocate.
		 * @return Self instance.
		 */
		wstring &compact(size_t size = -1ul) noexcept;


		/**
		 * Append the given string to this one.
		 * @param [in] str String to append.
		 * @param [in] length Length of the string to append.
		 * @throw memory_error when appending a nullptr.
		 * @return Self instance.
		 */
		wstring &append(const_wcstring str, size_t length);
		/**
		 * Append the given string to this one.
		 * @param [in] str String to append.
		 * @throw memory_error when appending a nullptr.
		 * @return Self instance.
		 */
		wstring &append(const_wcstring str);
		/**
		 * Append the given string to this one.
		 * @param [in] str String to append.
		 * @return Self instance.
		 */
		wstring &append(const wstring &str) noexcept;

		/**
		 * Preppend the given string to this one.
		 * @param [in] str String to preppend.
		 * @param [in] length Length of the string to preppend.
		 * @throw memory_error when prepending a nullptr.
		 * @return Self instance.
		 */
		wstring &preppend(const_wcstring str, size_t length);
		/**
		 * Preppend the given string to this one.
		 * @param [in] str String to preppend.
		 * @throw memory_error when prepending a nullptr.
		 * @return Self instance.
		 */
		wstring &preppend(const_wcstring str);
		/**
		 * Preppend the given string to this one.
		 * @param [in] str String to preppend.
		 * @return Self instance.
		 */
		wstring &preppend(const wstring &str) noexcept;


		/**
		 * Set the string to empty state.
		 * @return Self instance.
		 */
		wstring &clear() noexcept;


		/**
		 * Create a new string from a portion of this one.
		 * @param [in] start_position Position where the new string starts.
		 * Negative values start from behind.
		 * @param [in] max_length Length of the string to create. Default =
		 * remaining length of this string.
		 * @throw out_of_range_error when start_position is outside the string.
		 * @return New string.
		 */
		wstring substr(ssize_t start_position, size_t max_length = -1ul) const;
		/**
		 * Create a new string from a portion of this one.
		 * @param [in] start_position Position where the new string starts.
		 * @param [in] max_length Length of the string to create. Default =
		 * remaining length of this string.
		 * @throw out_of_range_error when start_position is outside the string.
		 * @return New string.
		 */
		wstring substr(size_t start_position, size_t max_length = -1ul) const;
		/**
		 * Create a new string from a portion of this one. Exists for
		 * compatibility.
		 * @param [in] start_position Position where the new string starts.
		 * Negative values start from behind.
		 * @param [in] max_length Length of the string to create. Default =
		 * remaining length of this string.
		 * @throw out_of_range_error when start_position is outside the string.
		 * @return New string.
		 */
		wstring substr(int32_t start_position, size_t max_length = -1ul) const;
		/**
		 * Create a new string from a portion of this one. Exists for
		 * compatibility.
		 * @param [in] start_position Position where the new string starts.
		 * @param [in] max_length Length of the string to create. Default =
		 * remaining length of this string.
		 * @throw out_of_range_error when start_position is outside the string.
		 * @return New string.
		 */
		wstring substr(uint32_t start_position, size_t max_length = -1ul) const;

		/**
		 * Reduce this string to a portion.
		 * @param [in] start_position Position where the new string starts.
		 * Negative values start from behind.
		 * @param [in] max_length Length of the string to create. Default =
		 * remaining length of this string.
		 * @throw out_of_range_error when start_position is outside the string.
		 * @return Self instance.
		 */
		wstring &shrink(ssize_t start_position, size_t max_length = -1ul);
		/**
		 * Reduce this string to a portion.
		 * @param [in] start_position Position where the new
		 * string starts.
		 * @param [in] max_length Length of the string to create.
		 * Default = remaining length of this string.
		 * @throw out_of_range_error when start_position is outside the string.
		 * @return Self instance.
		 */
		wstring &shrink(size_t start_position, size_t max_length = -1ul);
		/**
		 * Reduce this string to a portion. Exists for
		 * compatibility.
		 * @param [in] start_position Position where the new string starts.
		 * Negative values start from behind.
		 * @param [in] max_length Length of the string to create. Default =
		 * remaining length of this string.
		 * @throw out_of_range_error when start_position is outside the string.
		 * @return Self instance.
		 */
		wstring &shrink(int32_t start_position, size_t max_length = -1ul);
		/**
		 * Reduce this string to a portion. Exists for
		 * compatibility.
		 * @param [in] start_position Position where the new
		 * string starts.
		 * @param [in] max_length Length of the string to create.
		 * Default = remaining length of this string.
		 * @throw out_of_range_error when start_position is outside the string.
		 * @return Self instance.
		 */
		wstring &shrink(uint32_t start_position, size_t max_length = -1ul);

		/**
		 * Get a copy of the string reversed.
		 * @return New string with its content reversed.
		 */
		wstring mirror() const noexcept;

		/**
		 * Reverses the content of this string.
		 * @return Self instance.
		 */
		wstring &reverse() noexcept;


		/**
		 * Find where the pattern appears in the string. Boyer-Moore Algorithm
		 * will be used for wide dictionary size, otherwise Knuth-Morris-Pratt
		 * Algorithm will be used.
		 * @param [in] pattern Pattern to look for.
		 * @param [in] pattern_length Length of string to look for.
		 * @param [in] max_matches Max number of matches to look for.
		 * Default = no limit.
		 * @param [in] wide_dict If characters pool is varied. Default = true.
		 * @param [in] alphabet_size Max ASCII code of possible characters.
		 * Default = 256 for full ASCII.
		 * @throw memory_error when text or pattern is nullptr.
		 * @return Array of the positions where the match was found.
		 */
		array<size_t> find(const_wcstring pattern, size_t pattern_length,
		                   size_t max_matches = -1ul, bool_t wide_dict = true,
		                   size_t alphabet_size = 256ul) const;
		/**
		 * Find where the pattern appears in the string. Boyer-Moore Algorithm
		 * will be used for wide dictionary size, otherwise Knuth-Morris-Pratt
		 * Algorithm will be used.
		 * @param [in] pattern Pattern to look for.
		 * @param [in] max_matches Max number of matches to look for.
		 * Default = no limit.
		 * @param [in] wide_dict If characters pool is varied. Default = true.
		 * @param [in] alphabet_size Max ASCII code of possible characters.
		 * Default = 256 for full ASCII.
		 * @throw memory_error when text or pattern is nullptr.
		 * @return Array of the positions where the match was found.
		 */
		array<size_t> find(const_wcstring pattern, size_t max_matches = -1ul,
		                   bool_t wide_dict = true,
		                   size_t alphabet_size = 256ul) const;
		/**
		 * Find where the pattern appears in the string. Boyer-Moore Algorithm
		 * will be used for wide dictionary size, otherwise Knuth-Morris-Pratt
		 * Algorithm will be used.
		 * @param [in] pattern Pattern to look for.
		 * @param [in] max_matches Max number of matches to look for.
		 * Default = no limit.
		 * @param [in] wide_dict If characters pool is varied. Default = true.
		 * @param [in] alphabet_size Max ASCII code of possible characters.
		 * Default = 256 for full ASCII.
		 * @return Array of the positions where the match was found.
		 */
		array<size_t> find(const wstring &pattern, size_t max_matches = -1ul,
		                   bool_t wide_dict = true,
		                   size_t alphabet_size = 256ul) const noexcept;


		/**
		 * Find and replace a specific string inside this string.
		 * @param [in] pattern String to be replaced.
		 * @param [in] pattern_length Length of the string to be replaced.
		 * @param [in] replacement String to replace with.
		 * @param [in] replacement_length Length of the string to replace with.
		 * @param [in] max_matches Max matches to be replaces.
		 * @param [in] wide_dict If characters pool is varied. Default = true.
		 * @param [in] alphabet_size Max ASCII code of possible characters.
		 * Default = 256 for full ASCII.
		 * @throw memory_error when text, pattern or replacement is nullptr.
		 * @return Self instance.
		 */
		wstring &replace(const_wcstring pattern, size_t pattern_length,
		                 const_wcstring replacement, size_t replacement_length,
		                 size_t max_matches = -1ul, bool_t wide_dict = true,
		                 size_t alphabet_size = 256ul);
		/**
		 * Find and replace a specific string inside this string.
		 * @param [in] pattern String to be replaced.
		 * @param [in] replacement String to replace with.
		 * @param [in] max_matches Max matches to be replaces.
		 * @param [in] wide_dict If characters pool is varied. Default = true.
		 * @param [in] alphabet_size Max ASCII code of possible characters.
		 * Default = 256 for full ASCII.
		 * @throw memory_error when pattern or replacement is nullptr.
		 * @return Self instance.
		 */
		wstring &replace(const_wcstring pattern, const_wcstring replacement,
		                 size_t max_matches = -1ul, bool_t wide_dict = true,
		                 size_t alphabet_size = 256ul);
		/**
		 * Find and replace a specific string inside this string.
		 * @param [in] pattern String to be replaced.
		 * @param [in] replacement String to replace with.
		 * @param [in] max_matches Max matches to be replaces.
		 * @param [in] wide_dict If characters pool is varied. Default = true.
		 * @param [in] alphabet_size Max ASCII code of possible characters.
		 * Default = 256 for full ASCII.
		 * @return Self instance.
		 */
		wstring &replace(const wstring &pattern, const wstring &replacement,
		                 size_t max_matches = -1ul, bool_t wide_dict = true,
		                 size_t alphabet_size = 256ul) noexcept;


		/**
		 * Create a new copy of this string and append other string to it.
		 * @param [in] str String to append.
		 * @throw memory_error when string is a nullptr.
		 * @return A new string.
		 */
		wstring operator+(const_wcstring str) const;
		/**
		 * Create a new copy of this string and append other string to it.
		 * @param [in] str String to append.
		 * @return A new string.
		 */
		wstring operator+(const wstring &str) const noexcept;

		/**
		 * Append the given string to this one.
		 * @param [in] str String to append.
		 * @throw memory_error when string is a nullptr.
		 * @return Self instance.
		 */
		wstring &operator+=(const_wcstring str);
		/**
		 * Append the given string to this one.
		 * @param [in] str String to append.
		 * @return Self instance.
		 */
		wstring &operator+=(const wstring &str);

		/**
		 * Replace stored string with a new content.
		 * @param [in] str Content of the new string.
		 * @return Self instance.
		 */
		wstring &operator=(const_wcstring str) noexcept;
		/**
		 * Copy content from other string.
		 * @param [in] str String to copy from.
		 * @return Self instance.
		 */
		wstring &operator=(const wstring &str) noexcept = default;
		/**
		 * Move content from other string.
		 * @param [in,out] str String to move from and clear.
		 * @return Self instance.
		 */
		wstring &operator=(wstring &&str) noexcept;

		/**
		 * Check if this string is equal to another.
		 * @param [in] str String to compare with.
		 * @return True if the strings are equal, false otherwise.
		 */
		bool_t operator==(const wstring &str) const noexcept;

		/**
		 * Check if this string is different to another.
		 * @param [in] str String to compare with.
		 * @return True if the strings are different, false otherwise.
		 */
		bool_t operator!=(const wstring &str) const noexcept;

		/**
		 * Convert to a null-terminated string.
		 * @return Simple c-style string.
		 */
		operator wcstring() const noexcept;
	};


}   // namespace stick



#endif   //_stick_lib_string_wstring_
