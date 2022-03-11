/**
 * Type-reference related templates. Template implementations.
 * @brief Type-reference related template implementations.
 * @file reference_impl.tpp
 * @author Julio C. Galindo (stickM4N)
 */
#if defined(_stick_lib_templates_reference_impl_)


#	include "../error/memory_error.hpp"
#	include "../memory/storage.tpp"


namespace stick {


	template<typename type>
	struct dereference {
		using value = type;
	};
	template<typename type>
	struct dereference<const type> {
		using value = const type;
	};
	template<typename type>
	struct dereference<type &> {
		using value = type;
	};
	template<typename type>
	struct dereference<const type &> {
		using value = const type;
	};
	template<typename type>
	struct dereference<type &&> {
		using value = type;
	};
	template<typename type>
	struct dereference<const type &&> {
		using value = const type;
	};


	template<typename type>
	constexpr dereference_t<type> &&move(type &&value) noexcept {
		return static_cast<dereference_t<type> &&>(value);
	}


}   // namespace stick


#else
#	warning This file is included automatically and should not be used on its own!
#endif   //_stick_lib_templates_reference_impl_
