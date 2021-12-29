/**
 * Self-managed string class implementation.
 * @brief String class implementation.
 * @file string.cpp
 * @author Julio C. Galindo (stickM4N)
 */
#include "../../../include/stick/string/string.hpp"

#if defined(_stick_lib_string_string_)


#	include "../../../include/stick/string/cstring.hpp"
#	include "../../../include/stick/templates/reference.hpp"


namespace stick {


	string::string() noexcept : str(str_end) { }
	string::string(const_cstring string, size_t length, size_t pool_length)
	    : str_size(length), pool_size(pool_length),
	      str(string, length, pool_length + 1) {
		this->str[this->length()] = str_end;
	}
	string::string(const_cstring string) : str(string, str_length(string)) { }
	string::string(const char_t c, size_t repetitions, size_t pool_length)
	    : str_size(repetitions), pool_size(pool_length),
	      str(repetitions + pool_length + 1) {
		set(this->str.operator char_t *(), c, this->length());
		this->str[this->length()] = str_end;
	}
	string::string(size_t length, size_t pool_length) noexcept
	    : str_size(0ul), pool_size(pool_length), str(length + pool_length + 1) {
		this->str[0] = str_end;
	}


	const_cstring string::data() const noexcept {
		return this->str;
	}
	size_t string::length() const noexcept {
		return this->str_size;
	}
	size_t string::allocated_chars() const noexcept {
		return this->str.allocated_elems();
	}

	void string::set_pool(size_t length) noexcept {
		this->pool_size = length;
	}
	void string::expand(size_t length) noexcept {
		scoped_pointer<char_t> tempy(str.allocated_elems() + length);
		str_copy(this->str, this->length(), tempy);

		this->str = move(tempy);
	}


	string &string::operator=(const_cstring string) noexcept {
		size_t length = str_length(string);

		if (length > this->length())
			this->str = scoped_pointer<char_t>(length + this->pool_size);


		this->str_size = length;
		str_copy(string, this->length(), this->str);

		return *this;
	}
	string &string::operator=(string &&string) noexcept {
		this->str_size = string.str_size;
		this->pool_size = string.pool_size;
		this->str = move(string.str);

		string.str_size = 0ul;
		string.pool_size = 0ul;

		return *this;
	}



}   // namespace stick


#endif   //_stick_lib_string_string_
