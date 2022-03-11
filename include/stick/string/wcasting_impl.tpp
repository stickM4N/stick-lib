/**
 * Wide string casting. Wide string casting template implementations.
 * @brief Wide string casting template implementations.
 * @file wcasting_impl.tpp
 * @author Julio C. Galindo (stickM4N)
 */
#if defined(_stick_lib_string_wcasting_impl_)


#	include "../string/wcstring.hpp"


namespace stick {


	template<>
	const_wcstring cast_to_wcstr(nullptr_t value, wcstring string) {
		if (string == nullptr)
			return new_wstr(L"null", 4);
		else
			return wstr_copy(L"null", 4, string);
	}


	template<>
	const_wcstring cast_to_wcstr(bool_t value, wcstring string) {
		if (value) {
			if (string == nullptr)
				return new_wstr(L"true", 4);
			else
				return wstr_copy(L"true", 4, string);
		} else {
			if (string == nullptr)
				return new_wstr(L"false", 5);
			else
				return wstr_copy(L"false", 5, string);
		}
	}


	template<>
	const_wcstring cast_to_wcstr(int8_t value, wcstring string) {
		bool_t is_negative = value < 0;
		if (is_negative)
			value = -value;

		size_t length = 1ul;
		for (uint8_t i = 1u; value / i >= 10u; i *= 10u)
			length++;

		if (string == nullptr)
			string = new_wstr(length + (is_negative ? 2u : 1u));

		if (is_negative) {
			string[0] = L'-';
			length++;
		}
		string[length--] = wstr_end;

		for (; value > 0u; value /= 10u)
			string[length--] = L'0' + static_cast<wchar_t>(value % 10u);

		return string;
	}

	template<>
	const_wcstring cast_to_wcstr(int16_t value, wcstring string) {
		bool_t is_negative = value < 0;
		if (is_negative)
			value = -value;

		size_t length = 1ul;
		for (uint16_t i = 1u; value / i >= 10u; i *= 10u)
			length++;

		if (string == nullptr)
			string = new_wstr(length + (is_negative ? 2u : 1u));

		if (is_negative) {
			string[0] = L'-';
			length++;
		}
		string[length--] = wstr_end;

		for (; value > 0u; value /= 10u)
			string[length--] = L'0' + static_cast<wchar_t>(value % 10u);

		return string;
	}

	template<>
	const_wcstring cast_to_wcstr(int32_t value, wcstring string) {
		bool_t is_negative = value < 0;
		if (is_negative)
			value = -value;

		size_t length = 1ul;
		for (uint32_t i = 1u; value / i >= 10u; i *= 10u)
			length++;

		if (string == nullptr)
			string = new_wstr(length + (is_negative ? 2u : 1u));

		if (is_negative) {
			string[0] = L'-';
			length++;
		}
		string[length--] = wstr_end;

		for (; value > 0u; value /= 10u)
			string[length--] = L'0' + static_cast<wchar_t>(value % 10u);

		return string;
	}

	template<>
	const_wcstring cast_to_wcstr(int64_t value, wcstring string) {
		bool_t is_negative = value < 0;
		if (is_negative)
			value = -value;

		size_t length = 1ul;
		for (uint64_t i = 1u; value / i >= 10u; i *= 10u)
			length++;

		if (string == nullptr)
			string = new_wstr(length + (is_negative ? 2u : 1u));

		if (is_negative) {
			string[0] = L'-';
			length++;
		}
		string[length--] = wstr_end;

		for (; value > 0u; value /= 10u)
			string[length--] = L'0' + static_cast<wchar_t>(value % 10u);

		return string;
	}


	template<>
	const_wcstring cast_to_wcstr(uint8_t value, wcstring string) {
		size_t length = 1ul;
		for (uint8_t i = 1u; value / i >= 10u; i *= 10u)
			length++;

		if (string == nullptr)
			string = new_wstr(length + 1);

		string[length--] = wstr_end;

		for (; value > 0u; value /= 10u)
			string[length--] = L'0' + static_cast<wchar_t>(value % 10u);

		return string;
	}

	template<>
	const_wcstring cast_to_wcstr(uint16_t value, wcstring string) {
		size_t length = 1ul;
		for (uint16_t i = 1u; value / i >= 10u; i *= 10u)
			length++;

		if (string == nullptr)
			string = new_wstr(length + 1);

		string[length--] = wstr_end;

		for (; value > 0u; value /= 10u)
			string[length--] = L'0' + static_cast<wchar_t>(value % 10u);

		return string;
	}

	template<>
	const_wcstring cast_to_wcstr(uint32_t value, wcstring string) {
		size_t length = 1ul;
		for (uint32_t i = 1u; value / i >= 10u; i *= 10u)
			length++;

		if (string == nullptr)
			string = new_wstr(length + 1);

		string[length--] = wstr_end;

		for (; value > 0u; value /= 10u)
			string[length--] = L'0' + static_cast<wchar_t>(value % 10u);

		return string;
	}

	template<>
	const_wcstring cast_to_wcstr(uint64_t value, wcstring string) {
		size_t length = 1ul;
		for (uint64_t i = 1u; value / i >= 10u; i *= 10u)
			length++;

		if (string == nullptr)
			string = new_wstr(length + 1);

		string[length--] = wstr_end;

		for (; value > 0u; value /= 10u)
			string[length--] = L'0' + static_cast<wchar_t>(value % 10u);

		return string;
	}


	// TODO: Enhance implementation to be more precise and permit more values
	//       for floating point numbers. Currently it lacks precision due to
	//       bit-level algebra is not implemented.

	template<>
	const_wcstring cast_to_wcstr(float32_t value, wcstring string) {
		auto integer_part = static_cast<int64_t>(value);
		auto decimal_part = (value - integer_part) * 10;

		const_wcstring integer_str = cast_to_wcstr(integer_part, string);
		size_t length = wstr_length(integer_str);

		if (string == nullptr)
			string = new_wstr(length + 10);

		wstr_copy(integer_str, length, string, false);
		delete_wstr(const_cast<wcstring &>(integer_str));

		if (decimal_part != 0.0) {
			string[length++] = L'.';

			for (uint8_t i = 0u; i < 8 and decimal_part != 0.0l; i++) {
				string[length++] = L'0' + static_cast<wchar_t>(decimal_part);
				(decimal_part -= static_cast<wchar_t>(decimal_part)) *= 10u;
			}
		}

		string[length] = wstr_end;

		return string;
	}

	template<>
	const_wcstring cast_to_wcstr(double64_t value, wcstring string) {
		auto integer_part = static_cast<int64_t>(value);
		auto decimal_part = (value - integer_part) * 10;

		const_wcstring integer_str = cast_to_wcstr(integer_part, string);
		size_t length = wstr_length(integer_str);

		if (string == nullptr)
			string = new_wstr(length + 10);

		wstr_copy(integer_str, length, string, false);
		delete_wstr(const_cast<wcstring &>(integer_str));

		if (decimal_part != 0.0) {
			string[length++] = L'.';

			for (uint8_t i = 0u; i < 8 and decimal_part != 0.0l; i++) {
				string[length++] = L'0' + static_cast<wchar_t>(decimal_part);
				(decimal_part -= static_cast<wchar_t>(decimal_part)) *= 10u;
			}
		}

		string[length] = wstr_end;

		return string;
	}
	template<>
	const_wcstring cast_to_wcstr(double128_t value, wcstring string) {
		auto integer_part = static_cast<int64_t>(value);
		auto decimal_part = (value - integer_part) * 10;

		const_wcstring integer_str = cast_to_wcstr(integer_part, string);
		size_t length = wstr_length(integer_str);

		if (string == nullptr)
			string = new_wstr(length + 10);

		wstr_copy(integer_str, length, string, false);
		delete_wstr(const_cast<wcstring &>(integer_str));

		if (decimal_part != 0.0) {
			string[length++] = L'.';

			for (uint8_t i = 0u; i < 8 and decimal_part != 0.0l; i++) {
				string[length++] = L'0' + static_cast<wchar_t>(decimal_part);
				(decimal_part -= static_cast<wchar_t>(decimal_part)) *= 10u;
			}
		}

		string[length] = wstr_end;

		return string;
	}


}   // namespace stick


#else
#	warning This file is included automatically and should not be used on its own!
#endif   //_stick_lib_string_wcasting_impl_
