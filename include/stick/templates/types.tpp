/**
 * Type identifier template.
 * @brief Type identifier template.
 * @file types.tpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_templates_types_)
#	define _stick_lib_templates_types_



#	include "../defines/types.hpp"
#	include "../defines/predef.hpp"


namespace stick {


	/**
	 * Class to handle the static string in data segment as a constexpr.
	 */
	class type_str {

		const_cstring str;   ///< Pointer to the start of the string.
		size_t str_length;   ///< Length of the string.

	protected:
		/**
		 * Get the length of the string as a constexpr.
		 * @param string [in] String to measure.
		 * @param length Variable to store the length across recursion.
		 * @return size_t length of the string.
		 */
		static stick_constexpr size_t get_length(const_cstring string,
		                                         size_t length = 0ul) noexcept;
		/**
		 * Compare two strings for equality.
		 * @param str1 [in] First string to compare.
		 * @param str2 [in] Second string to compare.
		 * @param length [in] Max length to compare
		 * @return True if the strings are equal, false otherwise.
		 */
		static stick_constexpr bool_t compare(const_cstring str1,
		                                      const_cstring str2,
		                                      size_t length) noexcept;

	public:
		/**
		 * Static char array string constructor.
		 * @tparam total_chars Length of the string.
		 * @param string [in] String to use.
		 */
		template<size_t total_chars>
		stick_constexpr type_str(const char_t (&string)[total_chars]) noexcept;
		/**
		 * Construct string using a pointer and its length.
		 * @param string [in] Pointer to the start of the string.
		 * @param length [in] Length of the string. Default auto-get.
		 * @param offset_front [in] Front padding. Default = 0.
		 * @param offset_back [in] Back padding. Default = 0.
		 */
		stick_constexpr type_str(const_cstring string, size_t length = -1ul,
		                         size_t offset_front = 0ul,
		                         size_t offset_back = 0ul) noexcept;


		/**
		 * Begin iterator.
		 * @return Pointer to the first char of the string
		 */
		stick_constexpr const_cstring begin() const noexcept;

		/**
		 * End iterator.
		 * @return Pointer to the char behind the last on the string
		 */
		stick_constexpr const_cstring end() const noexcept;


		/**
		 * Pointer to the static string.
		 * @return Const string.
		 */
		stick_constexpr const_cstring data() const noexcept;

		/**
		 * Get the length of the string.
		 * @return The length of the string.
		 */
		stick_constexpr size_t length() const noexcept;


		/**
		 * Get the char of the string at a given position.
		 * @param position [in] Position of the char in the string.
		 * @return char_t at the position.
		 */
		stick_constexpr char_t operator[](size_t position) const noexcept;

		/**
		 * Compares equality with other string.
		 * @param string [in] String to compare.
		 * @return True if strings are equal, false otherwise.
		 */
		stick_constexpr bool_t
		operator==(const type_str &string) const noexcept;

		/**
		 * Compares difference with other string.
		 * @param string [in] String to compare.
		 * @return True if strings are different, false otherwise.
		 */
		stick_constexpr bool_t
		operator!=(const type_str &string) const noexcept;

		/**
		 * Cast this to a constant string.
		 * @return String with the same content as this.
		 */
		operator string() const noexcept;
	};



	/**
	 * Get identification fot types easily at compile time.
	 * @tparam type Type to identify.
	 */
	template<typename type>
	class type_id {

	protected:
		/**
		 * Get the name of the type from the extended function name.
		 * @return type_str with the type name.
		 */
		static stick_constexpr type_str extract_name() noexcept;

		/**
		 * Get the hash of the type.
		 * @param data [in] String to be hashed.
		 * @param length [in] Length of the string to be hashed.
		 * @param hash Stores the hash across recursion.
		 * @return uint64_t holding the hash of the string.
		 */
		static stick_constexpr uint64_t
		hash_fnv1a(const_cstring data, size_t length,
		           uint64_t hash = 0xcbf29ce484222325ul) noexcept;

	public:
		/**
		 * Gets the name of the given type.
		 * @return Cstring (constexpr for cxx14+) holding the type name.
		 */
		static stick_constexpr type_str name() noexcept;

		/**
		 * Gets a unique type identifier associated to the given type.
		 * @return Unique 64bit id (constexpr for cxx14+) for the type.
		 */
		static stick_constexpr uint64_t id() noexcept;


		/**
		 * Check if two types are the same.
		 * @tparam cmp_type Type to compare.
		 * @return Return true on same types, false otherwise.
		 */
		template<typename cmp_type>
		stick_constexpr bool_t
		operator==(const type_id<cmp_type> &) const noexcept;

		/**
		 * Check if two types are different.
		 * @tparam cmp_type Type to compare.
		 * @return Return true on different types, false otherwise.
		 */
		template<typename cmp_type>
		stick_constexpr bool_t
		operator!=(const type_id<cmp_type> &) const noexcept;
	};



	/**
	 * Compare if two types are equal.
	 * @param [in] first_type First type to compare.
	 * @param [in] second_type Second type to compare.
	 * @return True if types are equal, false otherwise.
	 */
#	define same_type(first_type, second_type)                                 \
		(type_id<first_type>::id() == type_id<second_type>::id())

	/**
	 * Compare if two types are different.
	 * @param [in] first_type First type to compare.
	 * @param [in] second_type Second type to compare.
	 * @return True if types are different, false otherwise.
	 */
#	define diff_types(first_type, second_type)                                \
		(type_id<first_type>::id() != type_id<second_type>::id())

	/**
	 * Checks if the variable is of type.
	 * @param [in] var Variable to be checked.
	 * @param [in] type Type the variable should be.
	 * @return True if variable id of type, false otherwise.
	 */
#	define var_is_of_type(var, type)                                          \
		(type_id<decltype(var)>::id() == type_id<type>::id())


}   // namespace stick


#	define _stick_lib_templates_types_impl_
#	include "../templates/types_impl.tpp"
#	undef _stick_lib_templates_types_impl_


#endif   //_stick_lib_templates_types_
