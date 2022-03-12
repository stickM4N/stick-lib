/**
 * Type identifier template.
 * @brief Type identifier template.
 * @file types.tpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_templates_types_)
#	define _stick_lib_templates_types_



#	include "../defines/types.hpp"


namespace stick {


	/**
	 * Get identification fot types easily. It uses typeid() language feature.
	 * @tparam type Type to identify.
	 */
	template<typename type>
	struct type_id {
		/**
		 * Gets the name of the given type.
		 * @return constexpr cstring holding the type name.
		 */
		static constexpr const_cstring name() noexcept;

		/**
		 * Gets a unique type identifier associated to the given type.
		 * @return constexpr size_t id of the type.
		 */
		static constexpr size_t id() noexcept;


		/**
		 * Check if two types are the same.
		 * @tparam cmp_type Type to compare.
		 * @return Return true on same types, false otherwise.
		 */
		template<typename cmp_type>
		constexpr bool_t operator==(const type_id<cmp_type> &) const noexcept;

		/**
		 * Check if two types are different.
		 * @tparam cmp_type Type to compare.
		 * @return Return true on different types, false otherwise.
		 */
		template<typename cmp_type>
		constexpr bool_t operator!=(const type_id<cmp_type> &) const noexcept;
	};


	/**
	 * Compare if two types are equal.
	 * @param [in] first_type First type to compare.
	 * @param [in] second_type Second type to compare.
	 * @return True if types are equal, false otherwise.
	 */
#	define same_types(first_type, second_type)                                \
		type_id<first_type>::id() == type_id<second_type>::id()

	/**
	 * Compare if two types are different.
	 * @param [in] first_type First type to compare.
	 * @param [in] second_type Second type to compare.
	 * @return True if types are different, false otherwise.
	 */
#	define diff_types(first_type, second_type)                                \
		type_id<first_type>::id() != type_id<second_type>::id()


}   // namespace stick


#	define _stick_lib_templates_types_impl_
#	include "../templates/types_impl.tpp"
#	undef _stick_lib_templates_types_impl_


#endif   //_stick_lib_templates_types_
