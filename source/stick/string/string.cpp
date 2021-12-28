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
	string::string(const_cstring str, size_t length,
	               size_t pool_length) noexcept
	    : str_size(length), pool_size(pool_length),
	      str(str, length, pool_length + 1) {
		this->str[this->str_size] = str_end;
	}
	string::string(const_cstring str) noexcept
	    : string(str, str_length(str)) { }
	string::string(const char_t c, size_t repetitions,
	               size_t pool_length) noexcept
	    : str_size(repetitions), pool_size(pool_length),
	      str(repetitions + pool_length + 1) {
		set(this->str.operator char_t *(), c, this->str_size);
		this->str[this->str_size] = str_end;
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


	string &string::operator=(const_cstring str) noexcept {
		size_t length = str_length(str);

		if (length > this->str_size)
			this->str = scoped_pointer<char_t>(length + this->pool_size);


		this->str_size = length;
		str_copy(str, this->str_size, this->str);

		return *this;
	}
	string &string::operator=(const string &str) noexcept {
		this->str_size = str.str_size;
		this->pool_size = str.pool_size;
		this->str = str.str;

		return *this;
	}
	string &string::operator=(string &&str) noexcept {
		this->str_size = str.str_size;
		this->pool_size = str.pool_size;
		this->str = move(str.str);

		str.str_size = 0ul;
		str.pool_size = 0ul;

		return *this;
	}



}   // namespace stick


#endif   //_stick_lib_string_string_
