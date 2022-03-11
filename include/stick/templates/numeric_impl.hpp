/**
 * Numeric related templates. Template implementations.
 * @brief Numeric related template implementations.
 * @file numeric_impl.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if defined(_stick_lib_templates_numeric_impl_)



namespace stick {


	template<size_t first_number, size_t second_number>
	struct find_max<first_number, second_number> {
		static const size_t result
		    = first_number >= second_number ? first_number : second_number;
	};

	template<size_t first_number, size_t second_number, size_t... other_numbers>
	struct find_max<first_number, second_number, other_numbers...> {
		static const size_t result
		    = first_number >= second_number
		          ? find_max<first_number, other_numbers...>::result
		          : find_max<second_number, other_numbers...>::result;
	};


	template<size_t first_number, size_t second_number>
	struct find_min<first_number, second_number> {
		static const size_t result
		    = first_number <= second_number ? first_number : second_number;
	};

	template<size_t first_number, size_t second_number, size_t... other_numbers>
	struct find_min<first_number, second_number, other_numbers...> {
		static const size_t result
		    = first_number <= second_number
		          ? find_max<first_number, other_numbers...>::result
		          : find_max<second_number, other_numbers...>::result;
	};


}   // namespace stick


#else
#	warning This file is included automatically and should not be used on its own!
#endif   //_stick_lib_templates_numeric_impl_
