/**
 * Type-reference related templates.
 * @brief Type-reference related templates.
 * @file reference.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_templates_reference_)
#	define _stick_lib_templates_reference_



#	include "../defines/types.hpp"


namespace stick {


	template<typename type>
	struct dereference;

	template<typename type>
	using dereference_t = typename dereference<type>::value;


	template<typename type>
	constexpr dereference_t<type> &&move(type &&value) noexcept;


}   // namespace stick


#	define _stick_lib_templates_reference_impl_
#	include "../templates/reference_impl.hpp"
#	undef _stick_lib_templates_reference_impl_


#endif   //_stick_lib_templates_reference_
