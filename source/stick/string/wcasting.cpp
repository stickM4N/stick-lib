/**
 * Convert wide strings to other data types implementation.
 * @brief Wide string casting implementation.
 * @file wcasting.cpp
 * @author Julio C. Galindo (stickM4N)
 */
#include "../../../include/stick/string/wcasting.hpp"

#if defined(_stick_lib_string_wcasting_)


#	include "../../../include/stick/error/cast_error.hpp"
#	include "../../../include/stick/string/wcstring.hpp"

namespace stick {


	nullptr_t wstr_cast_to_null(const_wcstring string, size_t length) {
		if (length == 4u and wstr_equal(string, L"null", 4))
			return nullptr;
		else
			throw cast_error("String cannot be cast to nullptr_t.");
	}
	nullptr_t wstr_cast_to_null(const_wcstring string) {
		return wstr_cast_to_null(string, wstr_length(string));
	}


	bool_t wstr_cast_to_bool(const_wcstring string, size_t length) {
		if (length == 4u and wstr_equal(string, L"true", 4))
			return true;
		else if (length == 5u and wstr_equal(string, L"false", 5))
			return false;
		else
			throw cast_error("String cannot be cast to bool_t.");
	}
	bool_t wstr_cast_to_bool(const_wcstring string) {
		return wstr_cast_to_bool(string, wstr_length(string));
	}


	int8_t wstr_cast_to_int8(const_wcstring string, size_t length) {
		double128_t number = wstr_cast_to_double128(string, length);
		if (stick_int8_MIN > number or number > stick_int8_MAX)
			throw cast_error("Cast number cannot fit in int8 type.");

		return static_cast<int8_t>(number);
	}
	int8_t wstr_cast_to_int8(const_wcstring string) {
		return wstr_cast_to_int8(string, wstr_length(string));
	}

	int16_t wstr_cast_to_int16(const_wcstring string, size_t length) {
		double128_t number = wstr_cast_to_double128(string, length);
		if (stick_int16_MIN > number or number > stick_int16_MAX)
			throw cast_error("Cast number cannot fit in int16 type.");

		return static_cast<int16_t>(number);
	}
	int16_t wstr_cast_to_int16(const_wcstring string) {
		return wstr_cast_to_int16(string, wstr_length(string));
	}

	int32_t wstr_cast_to_int32(const_wcstring string, size_t length) {
		double128_t number = wstr_cast_to_double128(string, length);
		if (stick_int32_MIN > number or number > stick_int32_MAX)
			throw cast_error("Cast number cannot fit in int32 type.");

		return static_cast<int32_t>(number);
	}
	int32_t wstr_cast_to_int32(const_wcstring string) {
		return wstr_cast_to_int32(string, wstr_length(string));
	}

	int64_t wstr_cast_to_int64(const_wcstring string, size_t length) {
		double128_t number = wstr_cast_to_double128(string, length);
		if (stick_int64_MIN > number or number > stick_int64_MAX)
			throw cast_error("Cast number cannot fit in int64 type.");

		return static_cast<int64_t>(number);
	}
	int64_t wstr_cast_to_int64(const_wcstring string) {
		return wstr_cast_to_int64(string, wstr_length(string));
	}


	uint8_t wstr_cast_to_uint8(const_wcstring string, size_t length) {
		double128_t number = wstr_cast_to_double128(string, length);
		if (stick_uint8_MIN > number or number > stick_uint8_MAX)
			throw cast_error("Cast number cannot fit in uint8 type.");

		return static_cast<uint8_t>(number);
	}
	uint8_t wstr_cast_to_uint8(const_wcstring string) {
		return wstr_cast_to_uint8(string, wstr_length(string));
	}

	uint16_t wstr_cast_to_uint16(const_wcstring string, size_t length) {
		double128_t number = wstr_cast_to_double128(string, length);
		if (stick_uint16_MIN > number or number > stick_uint16_MAX)
			throw cast_error("Cast number cannot fit in uint16 type.");

		return static_cast<uint16_t>(number);
	}
	uint16_t wstr_cast_to_uint16(const_wcstring string) {
		return wstr_cast_to_uint16(string, wstr_length(string));
	}

	uint32_t wstr_cast_to_uint32(const_wcstring string, size_t length) {
		double128_t number = wstr_cast_to_double128(string, length);
		if (stick_uint32_MIN > number or number > stick_uint32_MAX)
			throw cast_error("Cast number cannot fit in uint32 type.");

		return static_cast<uint32_t>(number);
	}
	uint32_t wstr_cast_to_uint32(const_wcstring string) {
		return wstr_cast_to_uint32(string, wstr_length(string));
	}

	uint64_t wstr_cast_to_uint64(const_wcstring string, size_t length) {
		double128_t number = wstr_cast_to_double128(string, length);
		if (stick_uint64_MIN > number or number > stick_uint64_MAX)
			throw cast_error("Cast number cannot fit in uint64 type.");

		return static_cast<uint64_t>(number);
	}
	uint64_t wstr_cast_to_uint64(const_wcstring string) {
		return wstr_cast_to_uint64(string, wstr_length(string));
	}


	float32_t wstr_cast_to_float32(const_wcstring string, size_t length) {
		return static_cast<float32_t>(wstr_cast_to_double128(string, length));
	}
	float32_t wstr_cast_to_float32(const_wcstring string) {
		return wstr_cast_to_float32(string, wstr_length(string));
	}


	double64_t wstr_cast_to_double64(const_wcstring string, size_t length) {
		return static_cast<double64_t>(wstr_cast_to_double128(string, length));
	}
	double64_t wstr_cast_to_double64(const_wcstring string) {
		return wstr_cast_to_double64(string, wstr_length(string));
	}

	double128_t wstr_cast_to_double128(const_wcstring string, size_t length) {

		size_t char_position = 0ul;
		bool_t is_negative = string[char_position] == '-';
		if (is_negative)
			char_position++;

		double128_t integer_part = 0.0l;
		if (string[char_position] == L'0')
			char_position++;
		else if (wchar_is_numeric(string[char_position]))
			do
				(integer_part *= 10) += string[char_position++] - L'0';
			while (wchar_is_numeric(string[char_position]));
		else
			throw cast_error("Given string is not a number. No integer part.");

		double128_t decimal_part = 0.0l;
		if (string[char_position] == L'.') {
			char_position++;

			if (not wchar_is_numeric(string[char_position]))
				throw cast_error(
				    "Given string is not a number. Expected decimal values.");

			double128_t factor = 0.1l;
			do {
				decimal_part += (string[char_position++] - L'0') * factor;
				factor *= 0.1l;
			} while (wchar_is_numeric(string[char_position]));
		}

		uint8_t exponent = 0;
		bool_t negative_exponent = false;
		if (string[char_position] == L'E' or string[char_position] == L'e') {
			char_position++;

			if (string[char_position] == L'+')
				char_position++;
			else if (string[char_position] == L'-') {
				negative_exponent = true;
				char_position++;
			}

			if (string[char_position] == L'0')
				char_position++;
			else if (wchar_is_numeric(string[char_position]))
				do
					exponent = exponent * 10 + (string[char_position++] - L'0');
				while (wchar_is_numeric(string[char_position]));
			else
				throw cast_error(
				    "Given string is not a number. Invalid exponent.");
		}

		if (char_position != length)
			throw cast_error("Given string is not a number. "
			                 "Could not be parsed completely.");

		double128_t number = integer_part + decimal_part;
		if (negative_exponent)
			for (uint8_t i = 0; i < exponent; i++)
				number /= 10;
		else   // positive exponent
			for (uint8_t i = 0; i < exponent; i++)
				number *= 10;
		if (is_negative)
			number = -number;

		return number;
	}
	double128_t wstr_cast_to_double128(const_wcstring string) {
		return wstr_cast_to_double128(string, wstr_length(string));
	}


}   // namespace stick


#endif   //_stick_lib_string_wcasting_
