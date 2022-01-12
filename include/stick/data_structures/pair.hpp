/**
 * Pair structure.
 * @brief Pair structure template.
 * @file pair.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_data_structures_pair_)
#	define _stick_lib_data_structures_pair_



#	include "../defines/types.hpp"


namespace stick {


	/**
	 * Structure to store two types together.
	 * @tparam first_type Type of the first value to store.
	 * @tparam second_type Type of the second value to store.
	 */
	template<typename first_type, typename second_type>
	class pair {

		first_type first_value;
		second_type second_value;

	public:
		/**
		 * Create pair with default values.
		 */
		pair() noexcept = default;
		/**
		 * Create pair with the given values.
		 * @param [in] first The first value to assign.
		 * @param [in] second The second value to assign.
		 */
		pair(first_type first, second_type second) noexcept;
		/**
		 * Copy constructor.
		 * @param [in] pair Pair to copy.
		 */
		pair(const pair &pair) noexcept;
		/**
		 * Move constructor.
		 * @param [in,out] pair Pair to move.
		 */
		pair(pair &&pair) noexcept;

		/**
		 * Destructor. Calls each value destructor.
		 */
		~pair() noexcept;


		/**
		 * Get the first value.
		 * @return First stored lvalue.
		 */
		first_type &first() noexcept;
		/**
		 * Get the second value.
		 * @return Second stored lvalue.
		 */
		second_type &second() noexcept;


		/**
		 * Copy assignment operator.
		 * @param [in] pair Pair to copy.
		 * @return Self instance.
		 */
		pair &operator=(const pair &pair) noexcept;
		/**
		 * Move assignment operator.
		 * @param [in] pair Pair to move.
		 * @return Self instance.
		 */
		pair &operator=(pair &&pair) noexcept;
	};


}   // namespace stick


#	define _stick_lib_data_structures_pair_impl_
#	include "../data_structures/pair_impl.hpp"
#	undef _stick_lib_data_structures_pair_impl_


#endif   //_stick_lib_data_structures_pair_
