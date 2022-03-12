/**
 * Type identifier template. Template implementations.
 * @brief Type identifier template implementations.
 * @file types_impl.tpp
 * @author Julio C. Galindo (stickM4N)
 */
#if defined(_stick_lib_templates_types_impl_)


#	include <typeinfo>


namespace stick {


	template<typename type>
	constexpr const_cstring type_id<type>::name() noexcept {
		// TODO: Remove int from the beginning and add names for base types.
		return typeid(type).name();
	}

	template<typename type>
	constexpr size_t type_id<type>::id() noexcept {
		return typeid(type).hash_code();
	}


	template<typename type>
	template<typename cmp_type>
	constexpr bool_t
	type_id<type>::operator==(const type_id<cmp_type> &) const noexcept {
		return type_id<type>::id() == type_id<cmp_type>::id();
	}

	template<typename type>
	template<typename cmp_type>
	constexpr bool_t
	type_id<type>::operator!=(const type_id<cmp_type> &) const noexcept {
		return type_id<type>::id() != type_id<cmp_type>::id();
	}


}   // namespace stick


#else
#	warning This file is included automatically and should not be used on its own!
#endif   //_stick_lib_templates_types_impl_
