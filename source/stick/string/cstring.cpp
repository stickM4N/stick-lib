/**
 * C-styled (null terminated) string utilities implementation.
 * @brief Cstring utilities implementation.
 * @file cstring.cpp
 * @author Julio C. Galindo (stickM4N)
 */
#include "../../../include/stick/string/cstring.hpp"

#if defined(_stick_lib_string_cstring_)


#	include "../../../include/stick/memory/management.hpp"


namespace stick {


	cstring new_str(const_cstring str, size_t length) {
		auto string = allocate<char_t>(length + 1);
		copy(str, string, length);
		string[length] = str_end;

		return string;
	}
	cstring new_str(const_cstring str) { return new_str(str, str_length(str)); }
	cstring new_str(size_t length) {
		auto string = allocate<char_t>(length + 1);
		string[0] = str_end;

		return string;
	}

	void delete_str(cstring &str) { deallocate(str); }


	size_t str_length(const_cstring str) noexcept {
		size_t length = 0ul;
		for (; *str != str_end; length++, str++)
			;

		return length;
	}


	bool_t str_equal(const_cstring str_1, const_cstring str_2,
	                 size_t length) noexcept {
		for (size_t i = 0ul; i < length; i++)
			if (str_1[i] != str_2[i])
				return false;

		return true;
	}
	bool_t str_equal(const_cstring str_1, const_cstring str_2) noexcept {
		return str_equal(str_1, str_2, str_length(str_1));
	}


	bool_t str_sorted(const_cstring str_1, const_cstring str_2,
	                  size_t length) noexcept {
		for (size_t i = 0ul; i < length; i++)
			if (str_1[i] < str_2[i])
				return true;
			else if (str_1[i] > str_2[i])
				return false;

		return true;
	}
	bool_t str_sorted(const_cstring str_1, const_cstring str_2) noexcept {
		return str_sorted(str_1, str_2, str_length(str_1));
	}


	bool_t char_is_numeric(const char_t character) noexcept {
		if ('0' <= character and character <= '9')
			return true;
		else
			return false;
	}

	bool_t str_is_numeric(const_cstring string, size_t length) noexcept {
		for (size_t i = 0ul; i < length; i++)
			if (not char_is_numeric(string[i]))
				return false;

		return true;
	}
	bool_t str_is_numeric(const_cstring string) noexcept {
		return str_is_numeric(string, str_length(string));
	}


	cstring str_copy(const_cstring source_str, size_t length,
	                 cstring destination_str, bool_t set_end) noexcept {
		copy(source_str, destination_str, length);

		if (set_end)
			destination_str[length] = str_end;

		return destination_str;
	}
	cstring str_copy(const_cstring source_str, cstring destination_str,
	                 bool_t set_end) noexcept {
		return str_copy(source_str, str_length(source_str), destination_str,
		                set_end);
	}


	const size_t *str_find(const_cstring text, size_t string_length,
	                       const_cstring pattern, size_t pattern_length,
	                       size_t max_matches, bool_t wide_dict,
	                       size_t alphabet_size) noexcept {

		if (string_length == 0 or pattern_length == 0) {
			auto result = allocate<size_t>(1);
			result[0] = -1ul;

			return result;
		}

		size_t total_matches_found = 0ul;
		size_t max_possible_matches = string_length - pattern_length + 1;
		if (max_matches > max_possible_matches)
			max_matches = max_possible_matches;

		auto matches_found = allocate<size_t>(max_matches + 1);

		if (wide_dict) {
			// Implemented using Boyer-Moore Algorithm for String Pattern
			auto pattern_index = allocate<ssize_t>(alphabet_size);
			for (size_t i = 0ul; i < alphabet_size; i++)
				pattern_index[i] = -1l;
			for (size_t i = 0ul; i < pattern_length; i++)
				pattern_index[static_cast<uchar_t>(pattern[i])]
				    = static_cast<ssize_t>(i);

			for (size_t j = 0ul; j <= string_length - pattern_length
			                     and total_matches_found < max_matches;) {
				ssize_t i = static_cast<ssize_t>(pattern_length) - 1;
				while (i >= 0l
				       and pattern[i] == text[j + static_cast<size_t>(i)])
					i--;
				if (i < 0l) {
					matches_found[total_matches_found++] = j;
					j += j + pattern_length < string_length
					         ? pattern_length
					               - static_cast<size_t>(
					                   pattern_index[static_cast<uchar_t>(
					                       text[j + pattern_length])])
					         : 1ul;
				} else {
					i -= pattern_index[static_cast<uchar_t>(
					    text[j + static_cast<size_t>(i)])];
					j += 1l < i ? static_cast<size_t>(i) : 1ul;
				}
			}

			deallocate(pattern_index);

		} else {
			// Implemented using Knuth-Morris-Pratt Algorithm
			auto pattern_index = allocate<size_t>(pattern_length);
			for (size_t i = 1ul, l = 0ul; i <= pattern_length;) {
				if (pattern[i] == pattern[l])
					pattern_index[i++] = ++l;
				else {
					if (l != 0)
						l = pattern_index[l - 1];
					else
						pattern_index[i++] = 0ul;
				}
			}
			pattern_index[0] = 0ul;

			for (size_t i = 0ul, j = 0ul;
			     i < string_length and total_matches_found < max_matches;) {
				if (pattern[j] == text[i]) {
					j++;
					i++;
				}

				if (j == pattern_length) {
					matches_found[total_matches_found++] = i - j;
					j = pattern_index[j - 1];
				} else if (i < string_length and pattern[j] != text[i]) {
					if (j != 0)
						j = pattern_index[j - 1];
					else
						i++;
				}
			}

			deallocate(pattern_index);
		}

		matches_found[total_matches_found] = -1ul;

		return matches_found;
	}
	const size_t *str_find(const_cstring text, const_cstring pattern,
	                       size_t max_matches, bool_t wide_dict,
	                       size_t alphabet_size) noexcept {
		return str_find(text, str_length(text), pattern, str_length(pattern),
		                max_matches, wide_dict, alphabet_size);
	}


	const_cstring str_replace(cstring text, size_t text_length,
	                          const_cstring pattern, size_t pattern_length,
	                          const_cstring replacement,
	                          size_t replacement_length, size_t max_matches,
	                          bool_t wide_dict, size_t alphabet_size) noexcept {

		size_t matches_found = 0ul;
		auto matches = const_cast<size_t *>(
		    str_find(text, text_length, pattern, pattern_length, max_matches,
		             wide_dict, alphabet_size));
		for (; matches[matches_found] != -1ul; matches_found++)
			;
		matches[matches_found] = text_length;

		if (matches_found == 0)
			return text;

		if (replacement_length < pattern_length) {
			for (size_t i = 0ul, displacement; i < matches_found; i++) {
				displacement = i * (pattern_length - replacement_length);
				move(&text[matches[i]] + pattern_length,
				     &text[matches[i]] + replacement_length - displacement,
				     matches[i + 1] - matches[i] - pattern_length);
				matches[i] -= displacement;
			}
		} else if (pattern_length < replacement_length) {
			for (size_t i = matches_found - 1, displacement; i < -1ul; i--) {
				displacement = i * (replacement_length - pattern_length);
				move(&text[matches[i]] + pattern_length,
				     &text[matches[i]] + replacement_length + displacement,
				     matches[i + 1] - matches[i] - pattern_length);
				matches[i] += displacement;
			}
		}

		for (size_t i = 0ul; i < matches_found; i++)
			copy(replacement, &text[matches[i]], replacement_length);

		text[text_length
		     + matches_found * (replacement_length - pattern_length)]
		    = str_end;

		deallocate(matches);

		return text;
	}
	const_cstring str_replace(cstring text, const_cstring pattern,
	                          const_cstring replacement, size_t max_matches,
	                          bool_t wide_dict, size_t alphabet_size) noexcept {
		return str_replace(text, str_length(text), pattern, str_length(pattern),
		                   replacement, str_length(replacement), max_matches,
		                   wide_dict, alphabet_size);
	}


}   // namespace stick


#endif
