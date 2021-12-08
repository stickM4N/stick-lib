/**
 * C-styled (wstr_end terminated) string utilities implementation.
 * @brief Wcstring utilities implementation.
 * @file wcstring.cpp
 * @author Julio C. Galindo (stickM4N)
 */
#include "../../../include/stick/string/wcstring.hpp"

#if defined(_stick_lib_string_wcstring_)


#	include "../../../include/stick/memory/management.hpp"


namespace stick {


	wcstring new_wstr(const_wcstring str, size_t length) {
		auto string = allocate<wchar_t>(length + 1);
		copy(str, string, length);
		string[length] = wstr_end;

		return string;
	}
	wcstring new_wstr(const_wcstring str) {
		return new_wstr(str, wstr_length(str));
	}
	wcstring new_wstr(size_t length) {
		auto string = allocate<wchar_t>(length + 1);
		string[0] = wstr_end;

		return string;
	}

	void delete_wstr(wcstring &str) { deallocate(str); }


	size_t wstr_length(const_wcstring str) noexcept {
		size_t length = 0ul;
		for (; *str != static_cast<wchar_t>(wstr_end); length++, str++)
			;

		return length;
	}


	bool_t wstr_compare(const_wcstring str_1, const_wcstring str_2,
	                    size_t length) noexcept {
		for (size_t i = 0ul; i < length; i++)
			if (str_1[i] != str_2[i])
				return false;

		return true;
	}
	bool_t wstr_compare(const_wcstring str_1, const_wcstring str_2) noexcept {
		return wstr_compare(str_1, str_2, wstr_length(str_1));
	}


	wcstring wstr_copy(const_wcstring source_str, size_t length,
	                   wcstring destination_str) noexcept {
		copy(source_str, destination_str, length);
		destination_str[length] = wstr_end;

		return destination_str;
	}
	wcstring wstr_copy(const_wcstring source_str,
	                   wcstring destination_str) noexcept {
		return wstr_copy(source_str, wstr_length(source_str), destination_str);
	}


	const size_t *wstr_find(const_wcstring text, size_t string_length,
	                        const_wcstring pattern, size_t pattern_length,
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
			// Searching
			auto pattern_index = allocate<ssize_t>(alphabet_size);
			for (size_t i = 0l; i < alphabet_size; i++)
				pattern_index[i] = -1l;
			for (size_t i = 0ul; i < pattern_length; i++)
				pattern_index[pattern[i]] = static_cast<ssize_t>(i);

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
					                   pattern_index[text[j + pattern_length]])
					         : 1l;
				} else {
					i -= pattern_index[text[j + static_cast<size_t>(i)]];
					j += 1l < i ? static_cast<size_t>(i) : 1l;
				}
			}

			deallocate(pattern_index);

		} else {
			// Implemented using Knuth-Morris-Pratt Algorithm for String Pattern
			// Searching
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
	const size_t *wstr_find(const_wcstring text, const_wcstring pattern,
	                        size_t max_matches, bool_t wide_dict,
	                        size_t alphabet_size) noexcept {
		return wstr_find(text, wstr_length(text), pattern, wstr_length(pattern),
		                 max_matches, wide_dict, alphabet_size);
	}


	const_wcstring wstr_replace(wcstring text, size_t text_length,
	                            const_wcstring pattern, size_t pattern_length,
	                            const_wcstring replacement,
	                            size_t replacement_length, size_t max_matches,
	                            bool_t wide_dict,
	                            size_t alphabet_size) noexcept {

		size_t matches_found = 0ul;
		auto matches = const_cast<size_t *>(
		    wstr_find(text, text_length, pattern, pattern_length, max_matches,
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
		    = wstr_end;

		deallocate(matches);

		return text;
	}
	const_wcstring wstr_replace(wcstring text, const_wcstring pattern,
	                            const_wcstring replacement, size_t max_matches,
	                            bool_t wide_dict,
	                            size_t alphabet_size) noexcept {
		return wstr_replace(
		    text, wstr_length(text), pattern, wstr_length(pattern), replacement,
		    wstr_length(replacement), max_matches, wide_dict, alphabet_size);
	}


}   // namespace stick


#endif
