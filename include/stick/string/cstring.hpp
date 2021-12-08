/**
 * C-styled (null terminated) string utilities.
 * @brief Cstring utilities.
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
	 * @param [in] length Length of the str.
	 * @return A pointer to the newly allocated string.
	 */
	cstring new_str(const_cstring str, size_t length);
	/**
	 * Allocates and initiates a new string.
	 * @param [in] str Pointer to the string to be initiated with.
	 * @return A pointer to the newly allocated string.
	 */
	cstring new_str(const_cstring str);
	/**
	 * Allocates an empty string.
	 * @param [in] length Length of the buffer the string should have.
	 * @return A pointer to the newly allocated string.
	 */
	cstring new_str(size_t length);

	/**
	 * Deletes and deallocates a string.
	 * @param [in,out] str Pointer to the string to be deleted.
	 */
	void delete_str(cstring &str);


	/**
	 * Return the length of a string.
	 * @param [in] str The string to determine the length of.
	 * @return The size of the string.
	 */
	size_t str_length(const_cstring str) noexcept;


	/**
	 * Compares two string contents.
	 * @param [in] str_1 First string to campare.
	 * @param [in] str_2 Second string to compare.
	 * @param [in] length Length to compare in the strings.
	 * @return True if the strings are identical, false otherwise.
	 */
	bool_t str_compare(const_cstring str_1, const_cstring str_2,
	                   size_t length) noexcept;
	/**
	 * Compares two string contents.
	 * @param [in] str_1 First string to campare.
	 * @param [in] str_2 Second string to compare.
	 * @return True if the strings are identical, false otherwise.
	 */
	bool_t str_compare(const_cstring str_1, const_cstring str_2) noexcept;


	/**
	 * Copies a string with the given length to the target string.
	 * @param [in] source_str Pointer to the beginning of the string to copy.
	 * @param [in] length Length of the string to copy.
	 * @param [in] destination_str Pointer to the beginning of the string to
	 * copy to.
	 * @return Pointer to the updated destination string.
	 */
	cstring str_copy(const_cstring source_str, size_t length,
	                 cstring destination_str) noexcept;
	/**
	 * Copies a string with the given length to the target string.
	 * @param [in] source_str Pointer to the beginning of the string to copy.
	 * @param [in] destination_str Pointer to the beginning of the string to
	 * copy to.
	 * @return Pointer to the updated destination string.
	 */
	cstring str_copy(const_cstring source_str,
	                 cstring destination_str) noexcept;


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
	 * @return Return a pointer to an array of the positions where the pattern
	 * was found. The array ends with -1 value.
	 */
	const size_t *str_find(const_cstring text, size_t text_length,
	                       const_cstring pattern, size_t pattern_length,
	                       size_t max_matches = -1ul, bool_t wide_dict = true,
	                       size_t alphabet_size = 26ul) noexcept;
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
	 * @return Return a pointer to an array of the positions where the pattern
	 * was found. The array ends with -1 value.
	 */
	const size_t *str_find(const_cstring text, const_cstring pattern,
	                       size_t max_matches = -1ul, bool_t wide_dict = true,
	                       size_t alphabet_size = 26ul) noexcept;


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
	 * @return Pointer to the updated string.
	 */
	const_cstring
	str_replace(cstring text, size_t text_length, const_cstring pattern,
	            size_t pattern_length, const_cstring replacement,
	            size_t replacement_length, size_t max_matches = -1ul,
	            bool_t wide_dict = true, size_t alphabet_size = 256ul) noexcept;
	/**
	 * Find and replace a specific string inside another.
	 * @param [in] text Text where the pattern is searched within.
	 * @param [in] pattern String to be replaced.
	 * @param [in] replacement String to replace with.
	 * @param [in] max_matches Max matches to be replaces.
	 * @param [in] wide_dict If characters pool is varied. Default = true.
	 * @param [in] alphabet_size Max ASCII code of possible characters.
	 * Default = 256 for full ASCII.
	 * @return Pointer to the updated string.
	 */
	const_cstring str_replace(cstring text, const_cstring pattern,
	                          const_cstring replacement,
	                          size_t max_matches = -1ul,
	                          bool_t wide_dict = true,
	                          size_t alphabet_size = 256ul) noexcept;


}   // namespace stick



#endif   //_stick_lib_string_cstring_
