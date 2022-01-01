/**
 * Self-managed wide string class implementation.
 * @brief Wide string class implementation.
 * @file wstring.cpp
 * @author Julio C. Galindo (stickM4N)
 */
#include "../../../include/stick/string/wstring.hpp"

#if defined(_stick_lib_string_wstring_)


#	include "../../../include/stick/string/wcstring.hpp"


namespace stick {


	wstring::wstring() noexcept : data(wstr_end) { }
	wstring::wstring(const_wcstring str, size_t length, size_t pool_length)
	    : data_size(length), pool(pool_length),
	      data(str, length, pool_length + 1) {
		this->data[this->length()] = wstr_end;
	}
	wstring::wstring(const_wcstring str) : wstring(str, wstr_length(str)) { }
	wstring::wstring(const wchar_t c, size_t repetitions, size_t pool_length)
	    : data_size(repetitions), pool(pool_length),
	      data(repetitions + pool_length + 1) {
		set(this->data.operator wchar_t *(), c, this->length());
		this->data[this->length()] = wstr_end;
	}
	wstring::wstring(size_t length, size_t pool_length) noexcept
	    : data_size(0ul), pool(pool_length), data(length + pool_length + 1) {
		this->data[0ul] = wstr_end;
	}

	wstring::~wstring() noexcept {
		this->data = allocate_value(wstr_end);
		this->data_size = 0ul;
		this->pool = 0ul;
	}


	wchar_t *wstring::begin() const noexcept {
		return &this->data[0ul];
	}
	wchar_t *wstring::end() const noexcept {
		return &this->data[this->length()];
	}

	wchar_t *wstring::rbegin() const noexcept {
		return &this->data[this->length() - 1ul];
	}
	wchar_t *wstring::rend() const noexcept {
		return &this->data[0ul] - 1ul;
	}


	size_t wstring::length() const noexcept {
		return this->data_size;
	}
	size_t wstring::allocated_chars() const noexcept {
		return this->data.allocated_elems();
	}

	size_t wstring::available_pool() const noexcept {
		return this->allocated_chars() - this->length() - 1ul;
	}

	bool_t wstring::empty() const noexcept {
		return this->length() == 0ul;
	}


	wstring &wstring::set_pool(size_t length) noexcept {
		this->pool = length;

		return *this;
	}


	wstring &wstring::expand(size_t length) noexcept {
		scoped_pointer<wchar_t> tempy(data.allocated_elems() + length);
		wstr_copy(this->data, this->length(), tempy);

		this->data = move(tempy);

		return *this;
	}


	wstring &wstring::compact(size_t size) noexcept {
		if (this->length() == this->allocated_chars() + 1ul)
			return *this;

		if (this->available_pool() <= size)
			size = 0ul;
		else
			size = this->available_pool() - size;

		if (this->length() + size == 0ul)
			*this = move(wstring());
		else {
			scoped_pointer<wchar_t> tempy(this->data, this->length(),
			                              size + 1ul);
			this->data = move(tempy);
		}

		return *this;
	}


	wstring &wstring::append(const_wcstring str, size_t length) {
		if (this->available_pool() < length)
			this->expand(this->available_pool() - length + this->pool);

		wstr_copy(str, length, &this->data[length]);
		this->data_size += length;

		return *this;
	}
	wstring &wstring::append(const_wcstring str) {
		return this->append(str, wstr_length(str));
	}
	wstring &wstring::append(const wstring &str) noexcept {
		return this->append(str.data, str.length());
	}

	wstring &wstring::preppend(const_wcstring str, size_t length) {
		if (this->available_pool() < length) {
			scoped_pointer<wchar_t> tempy(
			    str, length, this->length() + this->available_pool() + pool);
			wstr_copy(this->data, this->length(), &tempy[length], false);
			this->data = move(tempy);
		} else {
			wstr_move(this->data, this->length(), &this->data[length], true,
			          false);
			wstr_copy(str, length, this->data, true);
		}
		this->data_size += length;

		return *this;
	}
	wstring &wstring::preppend(const_wcstring str) {
		return this->preppend(str, wstr_length(str));
	}
	wstring &wstring::preppend(const wstring &str) noexcept {
		return this->preppend(str.data, str.length());
	}


	wstring &wstring::clear() noexcept {
		this->data[0ul] = wstr_end;
		this->data_size = 0ul;

		return *this;
	}


	wstring wstring::substr(ssize_t start_position, size_t max_length) const {
		if (start_position < 0l)
			start_position = this->length() + start_position;

		return this->substr(static_cast<size_t>(start_position), max_length);
	}
	wstring wstring::substr(size_t start_position, size_t max_length) const {
		if (this->length() <= start_position)
			throw;

		if (max_length < this->length() - start_position)
			max_length = this->length() - start_position;

		return { &this->data[start_position], max_length };
	}
	wstring wstring::substr(int32_t start_position, size_t max_length) const {
		return this->substr(static_cast<ssize_t>(start_position), max_length);
	}
	wstring wstring::substr(uint32_t start_position, size_t max_length) const {
		return this->substr(static_cast<size_t>(start_position), max_length);
	}

	wstring &wstring::shrink(ssize_t start_position, size_t max_length) {
		if (start_position < 0l)
			start_position = this->length() + start_position;

		return this->shrink(static_cast<size_t>(start_position), max_length);
	}
	wstring &wstring::shrink(size_t start_position, size_t max_length) {
		if (this->length() <= start_position)
			throw;

		if (max_length < this->length() - start_position)
			max_length = this->length() - start_position;

		wstr_copy(&this->data[start_position], max_length, this->data);

		return *this;
	}
	wstring &wstring::shrink(int32_t start_position, size_t max_length) {
		return this->shrink(static_cast<ssize_t>(start_position), max_length);
	}
	wstring &wstring::shrink(uint32_t start_position, size_t max_length) {
		return this->shrink(static_cast<size_t>(start_position), max_length);
	}


	array<size_t> wstring::find(const_wcstring pattern, size_t pattern_length,
	                            size_t max_matches, bool_t wide_dict,
	                            size_t alphabet_size) const {
		if (this->data == nullptr or pattern == nullptr)
			throw memory_error("Finding a/in a nullptr.");

		if (this->length() == 0 or pattern_length == 0)
			return {};


		size_t max_possible_matches = this->length() - pattern_length + 1;
		if (max_matches > max_possible_matches)
			max_matches = max_possible_matches;

		array<size_t> matches_found(max_matches);

		if (wide_dict) {
			// Implemented using Boyer-Moore Algorithm for String Pattern
			auto pattern_index = allocate<ssize_t>(alphabet_size);
			set(pattern_index, -1l, alphabet_size);
			for (size_t i = 0ul; i < pattern_length; i++)
				pattern_index[static_cast<uchar_t>(pattern[i])]
				    = static_cast<ssize_t>(i);

			for (size_t j = 0ul; j <= this->length() - pattern_length
			                     and matches_found.size() < max_matches;) {
				ssize_t i = static_cast<ssize_t>(pattern_length) - 1;
				while (i >= 0l
				       and pattern[i] == this->data[j + static_cast<size_t>(i)])
					i--;
				if (i < 0l) {
					matches_found.push_back(j);
					j += j + pattern_length < this->length()
					         ? pattern_length
					               - static_cast<size_t>(
					                   pattern_index[static_cast<uchar_t>(
					                       this->data[j + pattern_length])])
					         : 1ul;
				} else {
					i -= pattern_index[static_cast<uchar_t>(
					    this->data[j + static_cast<size_t>(i)])];
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
			     i < this->length() and matches_found.size() < max_matches;) {
				if (pattern[j] == this->data[i]) {
					j++;
					i++;
				}

				if (j == pattern_length) {
					matches_found.push_back(i - j);
					j = pattern_index[j - 1];
				} else if (i < this->length() and pattern[j] != this->data[i]) {
					if (j != 0)
						j = pattern_index[j - 1];
					else
						i++;
				}
			}

			deallocate(pattern_index);
		}

		return matches_found;
	}
	array<size_t> wstring::find(const_wcstring pattern, size_t max_matches,
	                            bool_t wide_dict, size_t alphabet_size) const {
		return this->find(pattern, wstr_length(pattern), max_matches, wide_dict,
		                  alphabet_size);
	}
	array<size_t> wstring::find(const wstring &pattern, size_t max_matches,
	                            bool_t wide_dict,
	                            size_t alphabet_size) const noexcept {
		return this->find(pattern, pattern.length(), max_matches, wide_dict,
		                  alphabet_size);
	}


	wstring &wstring::replace(const_wcstring pattern, size_t pattern_length,
	                          const_wcstring replacement,
	                          size_t replacement_length, size_t max_matches,
	                          bool_t wide_dict, size_t alphabet_size) {
		if (replacement == nullptr)
			throw memory_error("Replacing with a nullptr.");


		array<size_t> matches = this->find(pattern, pattern_length, max_matches,
		                                   wide_dict, alphabet_size);

		if (matches.empty())
			return *this;

		if (pattern_length < replacement_length
		    and this->available_pool()
		            < matches.size() * (replacement_length - pattern_length)) {

			wstring tempy(this->length()
			              + matches.size()
			                    * (replacement_length - pattern_length)
			              + this->pool + 1ul);
			tempy.append(this->data, matches[0ul]);
			for (size_t i = 0ul; i < matches.size() - 1ul; i++) {
				tempy.append(replacement, replacement_length);
				tempy.append(&this->data[matches[i] + pattern_length],
				             matches[i + 1ul] - matches[i]);
			}
			tempy.append(&this->data[matches[-1l]],
			             this->length() - matches[-1l]);

			*this = move(tempy);

		} else {

			matches.push_back(this->length());
			if (replacement_length < pattern_length) {
				for (size_t i = 0ul, offset; i < matches.size() - 1ul; i++) {
					offset = i * (pattern_length - replacement_length);
					wstr_move(&this->data[matches[i]] + pattern_length,
					          matches[i + 1ul] - matches[i] - pattern_length,
					          &this->data[matches[i]] + replacement_length
					              - offset,
					          false, false);
					matches[i] -= offset;
				}
			} else if (pattern_length < replacement_length) {
				for (size_t i = matches.size() - 1ul, offset; i < -1ul; i--) {
					offset = i * (replacement_length - pattern_length);
					wstr_move(&this->data[matches[i]] + pattern_length,
					          matches[i + 1ul] - matches[i] - pattern_length,
					          &this->data[matches[i]] + replacement_length
					              + offset,
					          false, false);
					matches[i] += offset;
				}
			}

			for (const auto e : matches.pop_back())
				wstr_copy(replacement, replacement_length, &this->data[e],
				          false);

			this->data_size
			    += matches.size() * (replacement_length - pattern_length);
			this->data[this->length()] = str_end;
		}

		return *this;
	}
	wstring &wstring::replace(const_wcstring pattern,
	                          const_wcstring replacement, size_t max_matches,
	                          bool_t wide_dict, size_t alphabet_size) {
		return this->replace(pattern, wstr_length(pattern), replacement,
		                     wstr_length(replacement), max_matches, wide_dict,
		                     alphabet_size);
	}
	wstring &wstring::replace(const wstring &pattern,
	                          const wstring &replacement, size_t max_matches,
	                          bool_t wide_dict, size_t alphabet_size) noexcept {
		return this->replace(pattern, pattern.length(), replacement,
		                     replacement.length(), max_matches, wide_dict,
		                     alphabet_size);
	}


	wstring wstring::operator+(const_wcstring str) const {
		return wstring(*this).append(str);
	}
	wstring wstring::operator+(const wstring &str) const noexcept {
		return wstring(*this).append(str);
	}

	wstring &wstring::operator+=(const_wcstring str) {
		return this->append(str);
	}
	wstring &wstring::operator+=(const wstring &str) {
		return this->append(str);
	}

	wstring &wstring::operator=(const_wcstring str) noexcept {
		size_t length = wstr_length(str);

		if (length > this->length())
			this->data = scoped_pointer<wchar_t>(length + this->pool);


		this->data_size = length;
		wstr_copy(str, this->length(), this->data);

		return *this;
	}
	wstring &wstring::operator=(wstring &&str) noexcept {
		this->data_size = str.data_size;
		this->pool = str.pool;
		this->data = move(str.data);

		str.data_size = 0ul;
		str.pool = 0ul;

		return *this;
	}

	bool_t wstring::operator==(const wstring &str) const noexcept {
		for (size_t i = 0ul; i < this->length(); i++)
			if (this->data[i] != str[i])
				return false;

		return true;
	}

	bool_t wstring::operator!=(const wstring &str) const noexcept {
		return not this->operator==(str);
	}

	wstring::operator wcstring() const noexcept {
		return this->data;
	}


}   // namespace stick


#endif   //_stick_lib_string_wstring_
