/**
 * Numeric related templates.
 * @brief Numeric related templates.
 * @file numeric.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_templates_numeric_)
#	define _stick_lib_templates_numeric_


#	include "../defines/types.hpp"


namespace stick {


	/**
	 * Find max value statically. Static member 'result' holds the max value.
	 * @tparam first_number First number to compare.
	 * @tparam other_numbers Rest of the numbers to compare
	 */
	template<size_t first_number, size_t... other_numbers>
	struct find_max { };


	/**
	 * Find min value statically. Static member 'result' holds the max value.
	 * @tparam first_number First number to compare.
	 * @tparam other_numbers Rest of the numbers to compare
	 */
	template<size_t first_number, size_t... other_numbers>
	struct find_min { };


}   // namespace stick


#	define _stick_lib_templates_numeric_impl_
#	include "../templates/numeric_impl.hpp"
#	undef _stick_lib_templates_numeric_impl_


#endif   //_stick_lib_templates_numeric_
