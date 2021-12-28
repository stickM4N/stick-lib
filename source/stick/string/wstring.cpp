/**
 * Self-managed wide string class implementation.
 * @brief Wide string class implementation.
 * @file wstring.cpp
 * @author Julio C. Galindo (stickM4N)
 */
#include "../../../include/stick/string/wstring.hpp"

#if defined(_stick_lib_string_wstring_)


#	include "../../../include/stick/string/wcstring.hpp"
#	include "../../../include/stick/templates/reference.hpp"


namespace stick {


	wstring::wstring() noexcept {
		this->str = wstr_end;
	}
	wstring::wstring(const_wcstring str, size_t length,
	                 size_t pool_length) noexcept {
		this->str_size = length;
		this->pool_size = pool_length;

		this->str = scoped_pointer<wchar_t>(str, length, pool_length + 1);
		this->str[this->str_size] = str_end;
	}
	wstring::wstring(const_wcstring str) noexcept
	    : wstring(str, wstr_length(str)) { }
	wstring::wstring(const wchar_t c, size_t repetitions,
	                 size_t pool_length) noexcept {
		this->str_size = repetitions;
		this->pool_size = pool_length;

		this->str
		    = scoped_pointer<wchar_t>(this->str_size + this->pool_size + 1);
		set(this->str.operator wchar_t *(), c, this->str_size);
		this->str[this->str_size] = str_end;
	}
	wstring::wstring(size_t length, size_t pool_length) noexcept {
		this->str_size = 0ul;
		this->pool_size = pool_length;

		this->str = scoped_pointer<wchar_t>(length + this->pool_size + 1);
		this->str[0] = str_end;
	}
	wstring::wstring(const wstring &str) noexcept {
		this->str_size = str.str_size;
		this->pool_size = str.pool_size;
		this->str = str.str;
	}
	wstring::wstring(wstring &&str) noexcept {
		this->str_size = str.str_size;
		this->pool_size = str.pool_size;
		this->str = str.str;

		str.str_size = 0ul;
		str.pool_size = 0ul;
		str.str.~scoped_pointer();
	}


	const_wcstring wstring::data() const noexcept {
		return this->str;
	}
	size_t wstring::length() const noexcept {
		return this->str_size;
	}
	size_t wstring::allocated_chars() const noexcept {
		return this->str.allocated_elems();
	}

	void wstring::set_pool(size_t length) noexcept {
		this->pool_size = length;
	}
	void wstring::expand(size_t length) noexcept {
		scoped_pointer<wchar_t> tempy(str.allocated_elems() + length);
		wstr_copy(this->str, this->length(), tempy);

		this->str = move(tempy);
	}


	wstring &wstring::operator=(const_wcstring str) noexcept {
		size_t length = wstr_length(str);

		if (length > this->str_size)
			this->str = scoped_pointer<wchar_t>(length + this->pool_size);


		this->str_size = length;
		wstr_copy(str, this->str_size, this->str);

		return *this;
	}
	wstring &wstring::operator=(const wstring &str) noexcept {
		this->str_size = str.str_size;
		this->pool_size = str.pool_size;
		this->str = str.str;

		return *this;
	}
	wstring &wstring::operator=(wstring &&str) noexcept {
		this->str_size = str.str_size;
		this->pool_size = str.pool_size;
		this->str = str.str;

		str.str_size = 0ul;
		str.pool_size = 0ul;
		str.str.~scoped_pointer();

		return *this;
	}


}   // namespace stick


#endif   //_stick_lib_string_wstring_