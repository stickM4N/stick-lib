/**
 * Convert wide strings to other data types.
 * @brief Wide string casting.
 * @file wcasting.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_string_wcasting_)
#	define _stick_lib_string_wcasting_



#	include "../defines/types.hpp"


namespace stick {


	/**
	 * Cast basic types to wide string.
	 * @tparam type Type of the value to be cast.
	 * @param [in] value Value to be cast.
	 * @param [in,out] string String where to copy the cast value.
	 * Default = nullptr, to allocate a new string.
	 * @return Newly allocated string with the cast value.
	 */
	template<typename type>
	const_wcstring cast_to_wcstr(type value, wcstring string = nullptr);


	/**
	 * Cast a string to nullptr.
	 * @param [in] string String to be converted.
	 * @param [in] length Length of the string to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return nullptr value resulting from casting the string.
	 */
	nullptr_t wstr_cast_to_null(const_wcstring string, size_t length);
	/**
	 * Cast a string to int8_t.
	 * @param [in] string String to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return int8_t value resulting from casting the string.
	 */
	nullptr_t wstr_cast_to_null(const_wcstring string);


	/**
	 * Cast a string to bool.
	 * @param [in] string String to be converted.
	 * @param [in] length Length of the string to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return bool value resulting from casting the string.
	 */
	bool_t wstr_cast_to_bool(const_wcstring string, size_t length);
	/**
	 * Cast a string to bool.
	 * @param [in] string String to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return bool value resulting from casting the string.
	 */
	bool_t wstr_cast_to_bool(const_wcstring string);


	/**
	 * Cast a string to int8_t.
	 * @param [in] string String to be converted.
	 * @param [in] length Length of the string to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return int8_t value resulting from casting the string.
	 */
	int8_t wstr_cast_to_int8(const_wcstring string, size_t length);
	/**
	 * Cast a string to int8_t.
	 * @param [in] string String to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return int8_t value resulting from casting the string.
	 */
	int8_t wstr_cast_to_int8(const_wcstring string);

	/**
	 * Cast a string to int16_t.
	 * @param [in] string String to be converted.
	 * @param [in] length Length of the string to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return int16_t value resulting from casting the string.
	 */
	int16_t wstr_cast_to_int16(const_wcstring string, size_t length);
	/**
	 * Cast a string to int16_t.
	 * @param [in] string String to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return int16_t value resulting from casting the string.
	 */
	int16_t wstr_cast_to_int16(const_wcstring string);

	/**
	 * Cast a string to int32_t.
	 * @param [in] string String to be converted.
	 * @param [in] length Length of the string to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return int32_t value resulting from casting the string.
	 */
	int32_t wstr_cast_to_int32(const_wcstring string, size_t length);
	/**
	 * Cast a string to int32_t.
	 * @param [in] string String to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return int32_t value resulting from casting the string.
	 */
	int32_t wstr_cast_to_int32(const_wcstring string);

	/**
	 * Cast a string to int64_t.
	 * @param [in] string String to be converted.
	 * @param [in] length Length of the string to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return int64_t value resulting from casting the string.
	 */
	int64_t wstr_cast_to_int64(const_wcstring string, size_t length);
	/**
	 * Cast a string to int64_t.
	 * @param [in] string String to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return int64_t value resulting from casting the string.
	 */
	int64_t wstr_cast_to_int64(const_wcstring string);


	/**
	 * Cast a string to uint8_t.
	 * @param [in] string String to be converted.
	 * @param [in] length Length of the string to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return uint8_t value resulting from casting the string.
	 */
	uint8_t wstr_cast_to_uint8(const_wcstring string, size_t length);
	/**
	 * Cast a string to uint8_t.
	 * @param [in] string String to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return uint8_t value resulting from casting the string.
	 */
	uint8_t wstr_cast_to_uint8(const_wcstring string);

	/**
	 * Cast a string to uint16_t.
	 * @param [in] string String to be converted.
	 * @param [in] length Length of the string to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return uint16_t value resulting from casting the string.
	 */
	uint16_t wstr_cast_to_uint16(const_wcstring string, size_t length);
	/**
	 * Cast a string to uint16_t.
	 * @param [in] string String to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return uint16_t value resulting from casting the string.
	 */
	uint16_t wstr_cast_to_uint16(const_wcstring string);

	/**
	 * Cast a string to uint32_t.
	 * @param [in] string String to be converted.
	 * @param [in] length Length of the string to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return uint32_t value resulting from casting the string.
	 */
	uint32_t wstr_cast_to_uint32(const_wcstring string, size_t length);
	/**
	 * Cast a string to uint32_t.
	 * @param [in] string String to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return uint32_t value resulting from casting the string.
	 */
	uint32_t wstr_cast_to_uint32(const_wcstring string);

	/**
	 * Cast a string to uint64_t.
	 * @param [in] string String to be converted.
	 * @param [in] length Length of the string to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return uint64_t value resulting from casting the string.
	 */
	uint64_t wstr_cast_to_uint64(const_wcstring string, size_t length);
	/**
	 * Cast a string to uint64_t.
	 * @param [in] string String to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return uint64_t value resulting from casting the string.
	 */
	uint64_t wstr_cast_to_uint64(const_wcstring string);


	/**
	 * Cast a string to float32_t.
	 * @param [in] string String to be converted.
	 * @param [in] length Length of the string to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return float32_t value resulting from casting the string.
	 */
	float32_t wstr_cast_to_float32(const_wcstring string, size_t length);
	/**
	 * Cast a string to float32_t.
	 * @param [in] string String to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return float32_t value resulting from casting the string.
	 */
	float32_t wstr_cast_to_float32(const_wcstring string);


	/**
	 * Cast a string to double64_t.
	 * @param [in] string String to be converted.
	 * @param [in] length Length of the string to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return double64_t value resulting from casting the string.
	 */
	double64_t wstr_cast_to_double64(const_wcstring string, size_t length);
	/**
	 * Cast a string to double64_t.
	 * @param [in] string String to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return double64_t value resulting from casting the string.
	 */
	double64_t wstr_cast_to_double64(const_wcstring string);

	/**
	 * Cast a string to double128_t.
	 * @param [in] string String to be converted.
	 * @param [in] length Length of the string to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return double128_t value resulting from casting the string.
	 */
	double128_t wstr_cast_to_double128(const_wcstring string, size_t length);
	/**
	 * Cast a string to double128_t.
	 * @param [in] string String to be converted.
	 * @throw cast_error when casting cannot be performed to the given string.
	 * @return double128_t value resulting from casting the string.
	 */
	double128_t wstr_cast_to_double128(const_wcstring string);


}   // namespace stick


#	define _stick_lib_string_wcasting_impl_
#	include "../string/wcasting_impl.tpp"
#	undef _stick_lib_string_wcasting_impl_


#endif   //_stick_lib_string_wcasting_
