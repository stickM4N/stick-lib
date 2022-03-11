/**
 * String casting. String casting template implementations.
 * @brief String casting template implementations.
 * @file casting_impl.tpp
 * @author Julio C. Galindo (stickM4N)
 */
#if defined(_stick_lib_string_casting_impl_)


#	include "../string/cstring.hpp"


namespace stick {


	template<>
	const_cstring cast_to_cstr(nullptr_t value, cstring string) {
		if (string == nullptr)
			return new_str("null", 4);
		else
			return str_copy("null", 4, string);
	}


	template<>
	const_cstring cast_to_cstr(bool_t value, cstring string) {
		if (value) {
			if (string == nullptr)
				return new_str("true", 4);
			else
				return str_copy("true", 4, string);
		} else {
			if (string == nullptr)
				return new_str("false", 5);
			else
				return str_copy("false", 5, string);
		}
	}


	template<>
	const_cstring cast_to_cstr(int8_t value, cstring string) {
		bool_t is_negative = value < 0;
		if (is_negative)
			value = -value;

		size_t length = 1ul;
		for (uint8_t i = 1u; value / i >= 10u; i *= 10u)
			length++;

		if (string == nullptr)
			string = new_str(length + (is_negative ? 2u : 1u));

		if (is_negative) {
			string[0] = '-';
			length++;
		}
		string[length--] = str_end;

		for (; value > 0u; value /= 10u)
			string[length--] = '0' + static_cast<char_t>(value % 10u);

		return string;
	}

	template<>
	const_cstring cast_to_cstr(int16_t value, cstring string) {
		bool_t is_negative = value < 0;
		if (is_negative)
			value = -value;

		size_t length = 1ul;
		for (uint16_t i = 1u; value / i >= 10u; i *= 10u)
			length++;

		if (string == nullptr)
			string = new_str(length + (is_negative ? 2u : 1u));

		if (is_negative) {
			string[0] = '-';
			length++;
		}
		string[length--] = str_end;

		for (; value > 0u; value /= 10u)
			string[length--] = '0' + static_cast<char_t>(value % 10u);

		return string;
	}

	template<>
	const_cstring cast_to_cstr(int32_t value, cstring string) {
		bool_t is_negative = value < 0;
		if (is_negative)
			value = -value;

		size_t length = 1ul;
		for (uint32_t i = 1u; value / i >= 10u; i *= 10u)
			length++;

		if (string == nullptr)
			string = new_str(length + (is_negative ? 2u : 1u));

		if (is_negative) {
			string[0] = '-';
			length++;
		}
		string[length--] = str_end;

		for (; value > 0u; value /= 10u)
			string[length--] = '0' + static_cast<char_t>(value % 10u);

		return string;
	}

	template<>
	const_cstring cast_to_cstr(int64_t value, cstring string) {
		bool_t is_negative = value < 0;
		if (is_negative)
			value = -value;

		size_t length = 1ul;
		for (uint64_t i = 1u; value / i >= 10u; i *= 10u)
			length++;

		if (string == nullptr)
			string = new_str(length + (is_negative ? 2u : 1u));

		if (is_negative) {
			string[0] = '-';
			length++;
		}
		string[length--] = str_end;

		for (; value > 0u; value /= 10u)
			string[length--] = '0' + static_cast<char_t>(value % 10u);

		return string;
	}


	template<>
	const_cstring cast_to_cstr(uint8_t value, cstring string) {
		size_t length = 1ul;
		for (uint8_t i = 1u; value / i >= 10u; i *= 10u)
			length++;

		if (string == nullptr)
			string = new_str(length + 1);

		string[length--] = str_end;

		for (; value > 0u; value /= 10u)
			string[length--] = '0' + static_cast<char_t>(value % 10u);

		return string;
	}

	template<>
	const_cstring cast_to_cstr(uint16_t value, cstring string) {
		size_t length = 1ul;
		for (uint16_t i = 1u; value / i >= 10u; i *= 10u)
			length++;

		if (string == nullptr)
			string = new_str(length + 1);

		string[length--] = str_end;

		for (; value > 0u; value /= 10u)
			string[length--] = '0' + static_cast<char_t>(value % 10u);

		return string;
	}

	template<>
	const_cstring cast_to_cstr(uint32_t value, cstring string) {
		size_t length = 1ul;
		for (uint32_t i = 1u; value / i >= 10u; i *= 10u)
			length++;

		if (string == nullptr)
			string = new_str(length + 1);

		string[length--] = str_end;

		for (; value > 0u; value /= 10u)
			string[length--] = '0' + static_cast<char_t>(value % 10u);

		return string;
	}

	template<>
	const_cstring cast_to_cstr(uint64_t value, cstring string) {
		size_t length = 1ul;
		for (uint64_t i = 1u; value / i >= 10u; i *= 10u)
			length++;

		if (string == nullptr)
			string = new_str(length + 1);

		string[length--] = str_end;

		for (; value > 0u; value /= 10u)
			string[length--] = '0' + static_cast<char_t>(value % 10u);

		return string;
	}


	// TODO: Enhance implementation to be more precise and permit more values
	//       for floating point numbers. Currently it lacks precision due to
	//       bit-level algebra is not implemented.

	template<>
	const_cstring cast_to_cstr(float32_t value, cstring string) {
		auto integer_part = static_cast<int64_t>(value);
		auto decimal_part = (value - integer_part) * 10;

		const_cstring integer_str = cast_to_cstr(integer_part, string);
		size_t length = str_length(integer_str);

		if (string == nullptr)
			string = new_str(length + 10);

		str_copy(integer_str, length, string, false);
		delete_str(const_cast<cstring &>(integer_str));

		if (decimal_part != 0.0) {
			string[length++] = '.';

			for (uint8_t i = 0u; i < 8 and decimal_part != 0.0l; i++) {
				string[length++] = '0' + static_cast<char_t>(decimal_part);
				(decimal_part -= static_cast<char_t>(decimal_part)) *= 10u;
			}
		}

		string[length] = str_end;

		return string;
	}

	template<>
	const_cstring cast_to_cstr(double64_t value, cstring string) {
		auto integer_part = static_cast<int64_t>(value);
		auto decimal_part = (value - integer_part) * 10;

		const_cstring integer_str = cast_to_cstr(integer_part, string);
		size_t length = str_length(integer_str);

		if (string == nullptr)
			string = new_str(length + 10);

		str_copy(integer_str, length, string, false);
		delete_str(const_cast<cstring &>(integer_str));

		if (decimal_part != 0.0) {
			string[length++] = '.';

			for (uint8_t i = 0u; i < 8 and decimal_part != 0.0l; i++) {
				string[length++] = '0' + static_cast<char_t>(decimal_part);
				(decimal_part -= static_cast<char_t>(decimal_part)) *= 10u;
			}
		}

		string[length] = str_end;

		return string;
	}
	template<>
	const_cstring cast_to_cstr(double128_t value, cstring string) {
		auto integer_part = static_cast<int64_t>(value);
		auto decimal_part = (value - integer_part) * 10;

		const_cstring integer_str = cast_to_cstr(integer_part, string);
		size_t length = str_length(integer_str);

		if (string == nullptr)
			string = new_str(length + 10);

		str_copy(integer_str, length, string, false);
		delete_str(const_cast<cstring &>(integer_str));

		if (decimal_part != 0.0) {
			string[length++] = '.';

			for (uint8_t i = 0u; i < 8 and decimal_part != 0.0l; i++) {
				string[length++] = '0' + static_cast<char_t>(decimal_part);
				(decimal_part -= static_cast<char_t>(decimal_part)) *= 10u;
			}
		}

		string[length] = str_end;

		return string;
	}


}   // namespace stick


#else
#	warning This file is included automatically and should not be used on its own!
#endif   //_stick_lib_string_casting_impl_
