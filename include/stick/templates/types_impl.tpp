/**
 * Type identifier template. Template implementations.
 * @brief Type identifier template implementations.
 * @file types_impl.tpp
 * @author Julio C. Galindo (stickM4N)
 */
#if defined(_stick_lib_templates_types_impl_)


#	include "../defines/compiler.hpp"


namespace stick {


	stick_constexpr size_t type_str::get_length(const_cstring string,
	                                            size_t length) noexcept {
		return *string != str_end ? type_str::get_length(++string, ++length)
		                          : length;
	}
	stick_constexpr bool_t type_str::compare(const_cstring str1,
	                                         const_cstring str2,
	                                         size_t length) noexcept {
		return *str1 == *str2
		       and (length == 1ul
		            or type_str::compare(++str1, ++str2, --length));
	}


	template<size_t total_chars>
	stick_constexpr
	type_str::type_str(const char_t (&string)[total_chars]) noexcept
	    : str(string), str_length(total_chars - 1ul) { }
	stick_constexpr type_str::type_str(const_cstring string, size_t length,
	                                   size_t offset_front,
	                                   size_t offset_back) noexcept
	    : str(&string[offset_front]),
	      str_length((length == -1ul ? type_str::get_length(string) : length)
	                 - offset_front - offset_back) { }


	stick_constexpr const_cstring type_str::begin() const noexcept {
		return this->data();
	}

	stick_constexpr const_cstring type_str::end() const noexcept {
		return this->begin() + this->length();
	}


	stick_constexpr const_cstring type_str::data() const noexcept {
		return this->str;
	}

	stick_constexpr size_t type_str::length() const noexcept {
		return this->str_length;
	}


	stick_constexpr char_t
	type_str::operator[](size_t position) const noexcept {
		return this->str[position];
	}

	stick_constexpr bool_t
	type_str::operator==(const type_str &string) const noexcept {
		return this->length() == string.length()
		       and this->compare(this->data(), string.data(), this->length());
	}

	stick_constexpr bool_t
	type_str::operator!=(const type_str &string) const noexcept {
		return not this->operator==(string);
	}

	type_str::operator string() const noexcept {
		return { this->data(), this->length() };
	}



	template<typename type>

	stick_constexpr type_str type_id<type>::extract_name() noexcept {

#	if stick_COMPILER_ID == stick_COMPILER_ID_CLANG
		return type_str(stick_CONTEXT_PRETTY_FUNCTION, -1ul, 67ul, 1ul);

#	elif stick_COMPILER_ID == stick_COMPILER_ID_GCC
		return type_str(stick_CONTEXT_PRETTY_FUNCTION, -1ul, 83ul, 1ul);

		/* TODO: Add predefined return according to other compiler notations.
#	elif stick_COMPILER_ID == stick_COMPILER_ID_MSVC

#	elif stick_COMPILER_ID == stick_COMPILER_ID_SUNPRO
		*/

#	else   // stick_COMPILER_ID == stick_COMPILER_ID_UNKNOWN
#		if stick_HAS_CONSTEXPR14

		const_cstring context = stick_CONTEXT_PRETTY_FUNCTION;
		size_t name_start_index = 0ul;
		size_t name_end_index = 0ul;

		for (name_start_index = 0ul; context[name_start_index] != '=';
		     name_start_index++)
			;
		for (name_end_index = name_start_index += 2ul;
		     context[name_end_index] != ']'; name_end_index++)
			;

		return type_str { &context[name_start_index],
			              name_end_index - name_start_index };

#		else
#			error Cannot determine the name correctly without cxx14 standard.
#		endif

#	endif
	}

	template<typename type>
	stick_constexpr uint64_t type_id<type>::hash_fnv1a(const_cstring data,
	                                                   size_t length,
	                                                   uint64_t hash) noexcept {
		return length > 0ul
		           ? hash_fnv1a(data + 1ul, --length,
		                        (hash ^= *data) *= 0x00000100000001B3ul)
		           : hash;
	}


	template<typename type>
	stick_constexpr type_str type_id<type>::name() noexcept {
		return type_id<type>::extract_name();
	}

	template<typename type>
	stick_constexpr uint64_t type_id<type>::id() noexcept {
		return type_id<type>::hash_fnv1a(type_id<type>::name().data(),
		                                 type_id<type>::name().length());
	}


	template<typename type>
	template<typename cmp_type>
	stick_constexpr bool_t
	type_id<type>::operator==(const type_id<cmp_type> &) const noexcept {
		return type_id<type>::id() == type_id<cmp_type>::id();
	}

	template<typename type>
	template<typename cmp_type>
	stick_constexpr bool_t
	type_id<type>::operator!=(const type_id<cmp_type> &) const noexcept {
		return type_id<type>::id() != type_id<cmp_type>::id();
	}


}   // namespace stick


#else
#	warning This file is included automatically and should not be used on its own!
#endif   //_stick_lib_templates_types_impl_
