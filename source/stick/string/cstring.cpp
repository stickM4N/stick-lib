/**
 * C-styled (null terminated) string utilities implementation.
 * @brief C-styled string utilities implementation.
 * @file cstring.cpp
 * @author Julio C. Galindo (stickM4N)
 */
#include "../../../include/stick/string/cstring.hpp"

#if defined(_stick_lib_string_cstring_)


#	include "../../../include/stick/error/memory_error.hpp"
#	include "../../../include/stick/memory/management.hpp"


namespace stick {


	cstring new_str(const_cstring str, size_t length) {
		if (str == nullptr)
			throw memory_error("Creating string from a nullptr.");

		auto str_new = allocate<char_t>(length + 1);
		str_copy(str, length, str_new);

		return str_new;
	}
	cstring new_str(const_cstring str) {
		return new_str(str, str_length(str));
	}
	cstring new_str(size_t length) noexcept {
		auto str_new = allocate<char_t>(length + 1ul);
		str_new[0ul] = str_end;

		return str_new;
	}

	void delete_str(cstring &str) {
		if (str == nullptr)
			throw memory_error("Deallocating a nullptr string.");

		deallocate(str);
	}


	size_t str_length(const_cstring str) {
		if (str == nullptr)
			throw memory_error("Checking length of a nullptr.");

		size_t length = 0ul;
		for (; *str != str_end; length++, str++)
			;

		return length;
	}


	bool_t str_equal(const_cstring str_1, const_cstring str_2, size_t length) {
		if (str_1 == nullptr or str_2 == nullptr)
			throw memory_error("Comparing length of a nullptr string.");

		for (size_t i = 0ul; i < length; i++)
			if (str_1[i] != str_2[i])
				return false;

		return true;
	}
	bool_t str_equal(const_cstring str_1, const_cstring str_2) {
		return str_equal(str_1, str_2, str_length(str_1));
	}


	bool_t str_sorted(const_cstring str_1, const_cstring str_2, size_t length) {
		if (str_1 == nullptr or str_2 == nullptr)
			throw memory_error("Checking sort of a nullptr string.");

		for (size_t i = 0ul; i < length; i++)
			if (str_1[i] < str_2[i])
				return true;
			else if (str_1[i] > str_2[i])
				return false;

		return true;
	}
	bool_t str_sorted(const_cstring str_1, const_cstring str_2) {
		return str_sorted(str_1, str_2, str_length(str_1));
	}


	bool_t char_is_numeric(const char_t character) noexcept {
		if ('0' <= character and character <= '9')
			return true;
		else
			return false;
	}

	bool_t str_is_numeric(const_cstring str, size_t length) {
		if (str == nullptr)
			throw memory_error("Checking numeric-ness of a nullptr string.");

		for (size_t i = 0ul; i < length; i++)
			if (not char_is_numeric(str[i]))
				return false;

		return true;
	}
	bool_t str_is_numeric(const_cstring str) {
		return str_is_numeric(str, str_length(str));
	}


	cstring str_copy(const_cstring source_str, size_t length,
	                 cstring destination_str, bool_t set_end) {
		if (source_str == nullptr or destination_str == nullptr)
			throw memory_error("Copying to/from a nullptr.");

		copy(source_str, destination_str, length);

		if (set_end)
			destination_str[length] = str_end;

		return destination_str;
	}
	cstring str_copy(const_cstring source_str, cstring destination_str,
	                 bool_t set_end) {
		return str_copy(source_str, str_length(source_str), destination_str,
		                set_end);
	}

	cstring str_move(cstring source_str, size_t length, cstring destination_str,
	                 bool_t set_end, bool_t clear_str) {
		if (source_str == nullptr or destination_str == nullptr)
			throw memory_error("Moving to/from a nullptr.");

		move(source_str, destination_str, length, false);

		if (set_end)
			destination_str[length] = str_end;

		if (clear_str)
			source_str[0ul] = str_end;

		return destination_str;
	}
	cstring str_move(cstring source_str, cstring destination_str,
	                 bool_t set_end, bool_t clear_str) {
		return str_move(source_str, str_length(source_str), destination_str,
		                set_end, clear_str);
	}


	const size_t *str_find(const_cstring text, size_t text_length,
	                       const_cstring pattern, size_t pattern_length,
	                       size_t max_matches, bool_t wide_dict,
	                       size_t alphabet_size) {
		if (text == nullptr or pattern == nullptr)
			throw memory_error("Finding a/in a nullptr.");

		if (text_length == 0 or pattern_length == 0) {
			auto result = allocate<size_t>(1);
			result[0] = -1ul;

			return result;
		}

		size_t total_matches_found = 0ul;
		size_t max_possible_matches = text_length - pattern_length + 1;
		if (max_matches > max_possible_matches)
			max_matches = max_possible_matches;

		auto matches_found = allocate<size_t>(max_matches + 1);

		if (wide_dict) {
			// Implemented using Boyer-Moore Algorithm for String Pattern
			// Searching
			auto pattern_index = allocate<ssize_t>(alphabet_size);
			set(pattern_index, -1l, alphabet_size);
			for (size_t i = 0ul; i < pattern_length; i++)
				pattern_index[static_cast<uchar_t>(pattern[i])]
				    = static_cast<ssize_t>(i);

			for (size_t j = 0ul; j <= text_length - pattern_length
			                     and total_matches_found < max_matches;) {
				ssize_t i = static_cast<ssize_t>(pattern_length) - 1;
				while (i >= 0l
				       and pattern[i] == text[j + static_cast<size_t>(i)])
					i--;
				if (i < 0l) {
					matches_found[total_matches_found++] = j;
					j += j + pattern_length < text_length
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
					if (l != 0ul)
						l = pattern_index[l - 1ul];
					else
						pattern_index[i++] = 0ul;
				}
			}
			pattern_index[0ul] = 0ul;

			for (size_t i = 0ul, j = 0ul;
			     i < text_length and total_matches_found < max_matches;) {
				if (pattern[j] == text[i]) {
					j++;
					i++;
				}

				if (j == pattern_length) {
					matches_found[total_matches_found++] = i - j;
					j = pattern_index[j - 1ul];
				} else if (i < text_length and pattern[j] != text[i]) {
					if (j != 0)
						j = pattern_index[j - 1ul];
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
	                       size_t alphabet_size) {
		return str_find(text, str_length(text), pattern, str_length(pattern),
		                max_matches, wide_dict, alphabet_size);
	}


	const_cstring str_replace(cstring text, size_t text_length,
	                          const_cstring pattern, size_t pattern_length,
	                          const_cstring replacement,
	                          size_t replacement_length, size_t max_matches,
	                          bool_t wide_dict, size_t alphabet_size) {
		if (replacement == nullptr)
			throw memory_error("Replacing with a nullptr.");

		size_t matches_found = 0ul;
		auto matches = const_cast<size_t *>(
		    str_find(text, text_length, pattern, pattern_length, max_matches,
		             wide_dict, alphabet_size));
		for (; matches[matches_found] != -1ul; matches_found++)
			;
		matches[matches_found] = text_length;

		if (matches_found == 0ul)
			return text;

		if (replacement_length < pattern_length) {
			for (size_t i = 0ul, displacement; i < matches_found; i++) {
				displacement = i * (pattern_length - replacement_length);
				move(&text[matches[i]] + pattern_length,
				     &text[matches[i]] + replacement_length - displacement,
				     matches[i + 1ul] - matches[i] - pattern_length);
				matches[i] -= displacement;
			}
		} else if (pattern_length < replacement_length) {
			for (size_t i = matches_found - 1ul, displacement; i < -1ul; i--) {
				displacement = i * (replacement_length - pattern_length);
				move(&text[matches[i]] + pattern_length,
				     &text[matches[i]] + replacement_length + displacement,
				     matches[i + 1ul] - matches[i] - pattern_length);
				matches[i] += displacement;
			}
		}

		for (size_t i = 0ul; i < matches_found; i++)
			str_copy(replacement, replacement_length, &text[matches[i]], false);

		text[text_length
		     + matches_found * (replacement_length - pattern_length)]
		    = str_end;

		deallocate(matches);

		return text;
	}
	const_cstring str_replace(cstring text, const_cstring pattern,
	                          const_cstring replacement, size_t max_matches,
	                          bool_t wide_dict, size_t alphabet_size) {
		return str_replace(text, str_length(text), pattern, str_length(pattern),
		                   replacement, str_length(replacement), max_matches,
		                   wide_dict, alphabet_size);
	}


}   // namespace stick


#endif
