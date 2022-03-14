/**
 * Numeric related templates.
 * @brief Numeric related templates.
 * @file numeric.tpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_templates_numeric_)
#	define _stick_lib_templates_numeric_


#	include "../defines/types.hpp"
#	include "../string/string.hpp"


namespace stick {


	/**
	 * Find max value statically. Static member 'result' holds the max value.
	 * @tparam first_number First number to compare.
	 * @tparam other_numbers Rest of the numbers to compare
	 */
	template<size_t first_number, size_t... other_numbers>
	struct find_max;


	/**
	 * Find min value statically. Static member 'result' holds the max value.
	 * @tparam first_number First number to compare.
	 * @tparam other_numbers Rest of the numbers to compare
	 */
	template<size_t first_number, size_t... other_numbers>
	struct find_min;


	/**
	 * Convert a number to its hex string equivalent.
	 * @tparam type Type of the number to convert.
	 * @param number [in] Number to convert.
	 * @param prefix [in] If the string should have 0x prefix.
	 * @param caps [in] If the string should be in capital letters.
	 * @return String holding the hex conversion.
	 */
	template<typename type>
	string to_hex(type number, bool_t prefix = true, bool_t caps = false) {

		string hex_data(sizeof(type) + sizeof(type) + (prefix ? 2ul : 0ul));

		for (size_t i = 0ul; i < sizeof(type); i++) {
			uint8_t octet = (number & 0xfful << i * 8) >> i * 8;
			uint8_t base = octet / 16ul;
			uint8_t remainder = octet % 16ul;

			hex_data
			    .append(static_cast<char_t>(remainder < 10ul ? '0' + remainder
			                                : caps ? 'A' + remainder - 10ul
			                                       : 'a' + remainder - 10ul))
			    .append(static_cast<char_t>(base < 10ul ? '0' + base
			                                : caps      ? 'A' + base - 10ul
			                                            : 'a' + base - 10ul));
		}

		if (prefix)
			hex_data.append("x0");

		return hex_data.mirror();
	}


}   // namespace stick


#	define _stick_lib_templates_numeric_impl_
#	include "../templates/numeric_impl.tpp"
#	undef _stick_lib_templates_numeric_impl_


#endif   //_stick_lib_templates_numeric_
