/**
 * C-styled (null terminated) string utilities implementation.
 * @brief Wide c-styled string utilities implementation.
 * @file wcstring.cpp
 * @author Julio C. Galindo (stickM4N)
 */
#include "../../../include/stick/string/wcstring.hpp"

#if defined(_stick_lib_string_wcstring_)


#	include "../../../include/stick/error/memory_error.hpp"
#	include "../../../include/stick/memory/management.tpp"


namespace stick {


	wcstring new_wstr(const_wcstring str, size_t length) {
		if (str == nullptr)
			throw memory_error("Creating string from a nullptr.");

		auto str_new = allocate<wchar_t>(length + 1);
		wstr_copy(str, length, str_new);

		return str_new;
	}
	wcstring new_wstr(const_wcstring str) {
		return new_wstr(str, wstr_length(str));
	}
	wcstring new_wstr(size_t length) noexcept {
		auto str_new = allocate<wchar_t>(length + 1ul);
		str_new[0ul] = wstr_end;

		return str_new;
	}

	void delete_wstr(wcstring &str) {
		if (str == nullptr)
			throw memory_error("Deallocating a nullptr string.");

		deallocate(str);
	}


	size_t wstr_length(const_wcstring str) {
		if (str == nullptr)
			throw memory_error("Checking length of a nullptr.");

		size_t length = 0ul;
		for (; *str != wstr_end; length++, str++)
			;

		return length;
	}


	bool_t wstr_equal(const_wcstring str_1, const_wcstring str_2,
	                  size_t length) {
		if (str_1 == nullptr or str_2 == nullptr)
			throw memory_error("Comparing length of a nullptr string.");

		for (size_t i = 0ul; i < length; i++)
			if (str_1[i] != str_2[i])
				return false;

		return true;
	}
	bool_t wstr_equal(const_wcstring str_1, const_wcstring str_2) {
		return wstr_equal(str_1, str_2, wstr_length(str_1));
	}


	bool_t wstr_sorted(const_wcstring str_1, const_wcstring str_2,
	                   size_t length) {
		if (str_1 == nullptr or str_2 == nullptr)
			throw memory_error("Checking sort of a nullptr string.");

		for (size_t i = 0ul; i < length; i++)
			if (str_1[i] < str_2[i])
				return true;
			else if (str_1[i] > str_2[i])
				return false;

		return true;
	}
	bool_t wstr_sorted(const_wcstring str_1, const_wcstring str_2) {
		return wstr_sorted(str_1, str_2, wstr_length(str_1));
	}


	bool_t wchar_is_numeric(const wchar_t character) noexcept {
		if (L'0' <= character and character <= L'9')
			return true;
		else
			return false;
	}

	bool_t wstr_is_numeric(const_wcstring str, size_t length) {
		if (str == nullptr)
			throw memory_error("Checking numeric-ness of a nullptr string.");

		for (size_t i = 0ul; i < length; i++)
			if (not wchar_is_numeric(str[i]))
				return false;

		return true;
	}
	bool_t wstr_is_numeric(const_wcstring str) {
		return wstr_is_numeric(str, wstr_length(str));
	}


	wcstring wstr_copy(const_wcstring source_str, size_t length,
	                   wcstring destination_str, bool_t set_end) {
		if (source_str == nullptr or destination_str == nullptr)
			throw memory_error("Copying to/from a nullptr.");

		copy(source_str, destination_str, length);

		if (set_end)
			destination_str[length] = wstr_end;

		return destination_str;
	}
	wcstring wstr_copy(const_wcstring source_str, wcstring destination_str,
	                   bool_t set_end) {
		return wstr_copy(source_str, wstr_length(source_str), destination_str,
		                 set_end);
	}

	wcstring wstr_move(wcstring source_str, size_t length,
	                   wcstring destination_str, bool_t set_end,
	                   bool_t clear_str) {
		if (source_str == nullptr or destination_str == nullptr)
			throw memory_error("Moving to/from a nullptr.");

		move(source_str, destination_str, length, false);

		if (set_end)
			destination_str[length] = wstr_end;

		if (clear_str)
			source_str[0ul] = wstr_end;

		return destination_str;
	}
	wcstring wstr_move(wcstring source_str, wcstring destination_str,
	                   bool_t set_end, bool_t clear_str) {
		return wstr_move(source_str, wstr_length(source_str), destination_str,
		                 set_end, clear_str);
	}


	const size_t *wstr_find(const_wcstring text, size_t text_length,
	                        const_wcstring pattern, size_t pattern_length,
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
				pattern_index[pattern[i]] = static_cast<ssize_t>(i);

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
					                   pattern_index[text[j + pattern_length]])
					         : 1ul;
				} else {
					i -= pattern_index[text[j + static_cast<size_t>(i)]];
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
	const size_t *wstr_find(const_wcstring text, const_wcstring pattern,
	                        size_t max_matches, bool_t wide_dict,
	                        size_t alphabet_size) {
		return wstr_find(text, wstr_length(text), pattern, wstr_length(pattern),
		                 max_matches, wide_dict, alphabet_size);
	}


	const_wcstring wstr_replace(wcstring text, size_t text_length,
	                            const_wcstring pattern, size_t pattern_length,
	                            const_wcstring replacement,
	                            size_t replacement_length, size_t max_matches,
	                            bool_t wide_dict, size_t alphabet_size) {

		size_t matches_found = 0ul;
		auto matches = const_cast<size_t *>(
		    wstr_find(text, text_length, pattern, pattern_length, max_matches,
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
			copy(replacement, &text[matches[i]], replacement_length);

		text[text_length
		     + matches_found * (replacement_length - pattern_length)]
		    = wstr_end;

		deallocate(matches);

		return text;
	}
	const_wcstring wstr_replace(wcstring text, const_wcstring pattern,
	                            const_wcstring replacement, size_t max_matches,
	                            bool_t wide_dict, size_t alphabet_size) {
		return wstr_replace(
		    text, wstr_length(text), pattern, wstr_length(pattern), replacement,
		    wstr_length(replacement), max_matches, wide_dict, alphabet_size);
	}


}   // namespace stick


#endif
