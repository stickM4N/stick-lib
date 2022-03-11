/**
 * Type-reference related templates.
 * @brief Type-reference related templates.
 * @file reference.tpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_templates_reference_)
#	define _stick_lib_templates_reference_



#	include "../defines/types.hpp"


namespace stick {


	/**
	 * Struct utility to dereference any data type on compile time.
	 * @tparam type Type to dereference.
	 */
	template<typename type>
	struct dereference;

	/**
	 * Dereference data type.
	 */
	template<typename type>
	using dereference_t = typename dereference<type>::value;


	/**
	 * Move any value by calling the move constructor.
	 * @tparam type Type of the value to move.
	 * @param [in,out] value Value to move.
	 * @return xvalue (reference of rvalue).
	 */
	template<typename type>
	constexpr dereference_t<type> &&move(type &&value) noexcept;


}   // namespace stick


#	define _stick_lib_templates_reference_impl_
#	include "../templates/reference_impl.tpp"
#	undef _stick_lib_templates_reference_impl_


#endif   //_stick_lib_templates_reference_
