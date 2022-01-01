/**
 * C-styled (null terminated) string utilities.
 * @brief C-styled string utilities.
 * @file cstring.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_string_cstring_)
#	define _stick_lib_string_cstring_



#	include "../defines/types.hpp"


namespace stick {


#	define str_end '\0'   ///< C-string (null-terminated) end character.


	/**
	 * Allocates and initiates a new string.
	 * @param [in] str Pointer to the string to be initiated with.
	 * @param [in] length Length of the string.
	 * @thow memory_error when data is nullptr.
	 * @return Pointer to the newly allocated string.
	 */
	cstring new_str(const_cstring str, size_t length);
	/**
	 * Allocates and initiates a new string.
	 * @param [in] str Pointer to the string to be initiated with.
	 * @thow memory_error when data is nullptr.
	 * @return Pointer to the newly allocated string.
	 */
	cstring new_str(const_cstring str);
	/**
	 * Allocates an empty string.
	 * @param [in] length Length of the buffer the string should have.
	 * @return Pointer to the newly allocated string.
	 */
	cstring new_str(size_t length) noexcept;

	/**
	 * Deletes and deallocates a string.
	 * @param [in,out] str Pointer to the string to be deleted.
	 * @thow memory_error when data is nullptr.
	 */
	void delete_str(cstring &str);


	/**
	 * Return the length of a string.
	 * @param [in] str The string to determine the length of.
	 * @thow memory_error when data is nullptr.
	 * @return The size of the string.
	 */
	size_t str_length(const_cstring str);


	/**
	 * Compares two string contents.
	 * @param [in] str_1 First string to compare.
	 * @param [in] str_2 Second string to compare.
	 * @param [in] length Length to compare in the strings.
	 * @thow memory_error when any data is nullptr.
	 * @return True if the strings are identical, false otherwise.
	 */
	bool_t str_equal(const_cstring str_1, const_cstring str_2, size_t length);
	/**
	 * Compares two string contents.
	 * @param [in] str_1 First string to compare.
	 * @param [in] str_2 Second string to compare.
	 * @thow memory_error when any data is nullptr.
	 * @return True if the strings are identical, false otherwise.
	 */
	bool_t str_equal(const_cstring str_1, const_cstring str_2);


	/**
	 * Checks if the first string is sorted in relation to the second string
	 * according to the ASCII code.
	 * @param [in] str_1 First string to compare.
	 * @param [in] str_2 Second string to compare.
	 * @param [in] length Length to compare in the strings.
	 * @thow memory_error when any data is nullptr.
	 * @return True if the first string is sorted ahead of the second, false
	 * otherwise.
	 */
	bool_t str_sorted(const_cstring str_1, const_cstring str_2, size_t length);
	/**
	 * Checks if the first string is sorted in relation to the second string
	 * according to the ASCII code.
	 * @param [in] str_1 First string to compare.
	 * @param [in] str_2 Second string to compare.
	 * @thow memory_error when any data is nullptr.
	 * @return True if the first string is sorted ahead of the second, false
	 * otherwise.
	 */
	bool_t str_sorted(const_cstring str_1, const_cstring str_2);


	/**
	 * Checks if the character is a number.
	 * @param character Character to be checked.
	 * @return True if the character is a number, false otherwise.
	 */
	bool_t char_is_numeric(char_t character) noexcept;

	/**
	 * Checks if the string is made by numeric characters.
	 * @param str The string to be checked.
	 * @param length The length of the string to be checked.
	 * @thow memory_error when data is nullptr.
	 * @return True if all chars in the string are numbers, false otherwise.
	 */
	bool_t str_is_numeric(const_cstring str, size_t length);
	/**
	 * Checks if the string is made by numeric characters.
	 * @param str The string to be checked.
	 * @thow memory_error when data is nullptr.
	 * @return True if all chars in the string are numbers, false otherwise.
	 */
	bool_t str_is_numeric(const_cstring str);


	/**
	 * Copies a string with the given length to the target string.
	 * @param [in] source_str Pointer to the beginning of the string to copy.
	 * @param [in] length Length of the string to copy.
	 * @param [in] destination_str Pointer to the beginning of the string to
	 * copy to.
	 * @param [in] set_end Set null character at the end of the copied string.
	 * Default = true.
	 * @thow memory_error when copying to/from a nullptr.
	 * @return Pointer to the updated destination string.
	 */
	cstring str_copy(const_cstring source_str, size_t length,
	                 cstring destination_str, bool_t set_end = true);
	/**
	 * Copies a string with the given length to the target string.
	 * @param [in] source_str Pointer to the beginning of the string to copy.
	 * @param [in] destination_str Pointer to the beginning of the string to
	 * copy to.
	 * @param [in] set_end Set null character at the end of the copied string.
	 * Default = true.
	 * @thow memory_error when copying to/from a nullptr.
	 * @return Pointer to the updated destination string.
	 */
	cstring str_copy(const_cstring source_str, cstring destination_str,
	                 bool_t set_end = true);

	/**
	 * Moves a string with the given length to the target string.
	 * @param [in] source_str Pointer to the beginning of the string to move.
	 * @param [in] length Length of the string to move.
	 * @param [in] destination_str Pointer to the beginning of the string to
	 * move to.
	 * @param [in] set_end Set null character at the end of the moved string.
	 * Default = true.
	 * @param [in] clear_str Set source data to empty. Default = true.
	 * @thow memory_error when moving to/from a nullptr.
	 * @return Pointer to the updated destination string.
	 */
	cstring str_move(cstring source_str, size_t length, cstring destination_str,
	                 bool_t set_end = true, bool_t clear_str = true);
	/**
	 * Moves a string with the given length to the target string.
	 * @param [in] source_str Pointer to the beginning of the string to move.
	 * @param [in] destination_str Pointer to the beginning of the string to
	 * move to.
	 * @param [in] set_end Set null character at the end of the moved string.
	 * Default = true.
	 * @param [in] clear_str Set source data to empty. Default = true.
	 * @thow memory_error when moving to/from a nullptr.
	 * @return Pointer to the updated destination string.
	 */
	cstring str_move(cstring source_str, cstring destination_str,
	                 bool_t set_end = true, bool_t clear_str = true);

	/**
	 * Find where the pattern appears in the string. Boyer-Moore Algorithm will
	 * be used for wide dictionary size, otherwise Knuth-Morris-Pratt Algorithm
	 * will be used.
	 * @param [in] text String to look within.
	 * @param [in] text_length Length of the string to look in.
	 * @param [in] pattern Pattern to look for.
	 * @param [in] pattern_length Length of string to look for.
	 * @param [in] max_matches Max number of matches to look for.
	 * Default = no limit.
	 * @param [in] wide_dict If characters pool is varied. Default = true.
	 * @param [in] alphabet_size Max ASCII code of possible characters.
	 * Default = 256 for full ASCII.
	 * @throw memory_error when text or pattern is nullptr.
	 * @return Pointer to an array of the positions where the pattern
	 * was found. The array ends with -1 value.
	 */
	const size_t *str_find(const_cstring text, size_t text_length,
	                       const_cstring pattern, size_t pattern_length,
	                       size_t max_matches = -1ul, bool_t wide_dict = true,
	                       size_t alphabet_size = 256ul);
	/**
	 * Find where the pattern appears in the string. Boyer-Moore Algorithm will
	 * be used for wide dictionary size, otherwise Knuth-Morris-Pratt Algorithm
	 * will be used.
	 * @param [in] text String to look within.
	 * @param [in] pattern Pattern to look for.
	 * @param [in] max_matches Max number of matches to look for.
	 * Default = no limit.
	 * @param [in] wide_dict If characters pool is varied. Default = true.
	 * @param [in] alphabet_size Max ASCII code of possible characters.
	 * Default = 256 for full ASCII.
	 * @throw memory_error when text or pattern is nullptr.
	 * @return Pointer to an array of the positions where the pattern
	 * was found. The array ends with -1 value.
	 */
	const size_t *str_find(const_cstring text, const_cstring pattern,
	                       size_t max_matches = -1ul, bool_t wide_dict = true,
	                       size_t alphabet_size = 256ul);


	/**
	 * Find and replace a specific string inside another.
	 * @param [in] text String where the pattern is searched within.
	 * @param [in] text_length Length of the string
	 * @param [in] pattern String to be replaced.
	 * @param [in] pattern_length Length of the string to be replaced.
	 * @param [in] replacement String to replace with.
	 * @param [in] replacement_length Length of the string to replace with.
	 * @param [in] max_matches Max matches to be replaces.
	 * @param [in] wide_dict If characters pool is varied. Default = true.
	 * @param [in] alphabet_size Max ASCII code of possible characters.
	 * Default = 256 for full ASCII.
	 * @throw memory_error when text, pattern or replacement is nullptr.
	 * @return Pointer to the updated string.
	 */
	const_cstring
	str_replace(cstring text, size_t text_length, const_cstring pattern,
	            size_t pattern_length, const_cstring replacement,
	            size_t replacement_length, size_t max_matches = -1ul,
	            bool_t wide_dict = true, size_t alphabet_size = 256ul);
	/**
	 * Find and replace a specific string inside another.
	 * @param [in] text Text where the pattern is searched within.
	 * @param [in] pattern String to be replaced.
	 * @param [in] replacement String to replace with.
	 * @param [in] max_matches Max matches to be replaces.
	 * @param [in] wide_dict If characters pool is varied. Default = true.
	 * @param [in] alphabet_size Max ASCII code of possible characters.
	 * Default = 256 for full ASCII.
	 * @throw memory_error when text, pattern or replacement is nullptr.
	 * @return Pointer to the updated string.
	 */
	const_cstring str_replace(cstring text, const_cstring pattern,
	                          const_cstring replacement,
	                          size_t max_matches = -1ul,
	                          bool_t wide_dict = true,
	                          size_t alphabet_size = 256ul);


}   // namespace stick



#endif   //_stick_lib_string_cstring_
