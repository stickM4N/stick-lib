/**
 * Hybrid FIFO-LIFO array template. Can be used as a queue and a stack
 * simultaneously.
 * @brief Hybrid array template.
 * @file array.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if not defined(_stick_lib_data_structures_array_)
#	define _stick_lib_data_structures_array_



#	include "../data_structures/list_constexpr.hpp"
#	include "../defines/types.hpp"
#	include "../memory/scoped_pointer.hpp"


namespace stick {


	template<typename type>
	class array {

		scoped_pointer<type> data;
		size_t data_start = 0ul;
		size_t data_size = 0ul;
		size_t front_pool = 0ul;
		size_t back_pool = 0ul;

	protected:
		/**
		 * Possible cases to move the array when push-ing and pop-ing values.
		 */
		enum class move_decision_result : uint8_t {
			expand_and_move_front,   /// Expand the array and move the front
			                         /// part.
			move_front,   /// Only move the front part.
			expand_and_move_back,   /// Expand the array and move the back part.
			move_back   /// Only move the back part.
		};

		/**
		 * Find the best way to move the array to push or pop values.
		 * @param [in] position Where the value is being push-ed or pop-ed.
		 * @return move_decision_result of the most effective
		 */
		move_decision_result make_move_decision(size_t position) const noexcept;


		/**
		 * Get the position of the first valid value in the allocated memory.
		 * @return Position of the first valid value in the allocated memory.
		 */
		size_t first_position() const noexcept;
		/**
		 * Get the position of the last valid value in the allocated memory.
		 * @return Position of the last valid value in the allocated memory.
		 */
		size_t last_position() const noexcept;


		/**
		 * Begin iterator of the allocated memory.
		 * @return Pointer to the first element allocated.
		 */
		type *allocated_begin() const noexcept;
		/**
		 * End iterator of the allocated memory.
		 * @return Pointer to one element after the last one allocated.
		 */
		type *allocated_end() const noexcept;

		/**
		 * Reverse begin iterator of the allocated memory.
		 * @return Pointer to the last allocated element.
		 */
		type *allocated_rbegin() const noexcept;
		/**
		 * Revere end iterator of the allocated memory.
		 * @return Pointer to one element before the first allocated.
		 */
		type *allocated_rend() const noexcept;

	public:
		/**
		 * Default constructor for empty array.
		 */
		array() noexcept = default;
		/**
		 * Create an array copying from a basic array.
		 * @param [in] array Pointer to the array to copy from.
		 * @param [in] length Number of elements to copy from the array.
		 * @throw memory_error when copying from a nullptr.
		 */
		explicit array(const type *array, size_t length);
		/**
		 * Create an array copying from a constexpr list.
		 * @param [in] array Constant list to initialize the array.
		 * @throw memory_error when array is empty.
		 */
		array(const list_constexpr<type> &array);
		/**
		 * Create an empty array with reserved space.
		 * @param [in] size Number of elements to reserve space for.
		 * @param [in] front_pool_length Extra element to reserve space at the
		 * beginning of the array.
		 * @param [in] back_pool_length Extra element to reserve space at the
		 * end of the array.
		 * @throw memory_error when copying from a nullptr or allocating 0 byte.
		 */
		explicit array(size_t size, size_t front_pool_length = 0ul,
		               size_t back_pool_length = 0ul);
		/**
		 * Default copy constructor.
		 * @param [in] array Array to copy from.
		 */
		array(const array &array) noexcept = default;
		/**
		 * Move constructor.
		 * @param [in,out] array Array to move from and clear.
		 */
		array(array &&array) noexcept;

		/**
		 * Clear the array completely and its parameters. Also deallocates the
		 * memory.
		 */
		~array() noexcept;


		/**
		 * Begin iterator.
		 * @return Pointer to the first element.
		 */
		type *begin() const noexcept;
		/**
		 * End iterator.
		 * @return Pointer to one element after the last.
		 */
		type *end() const noexcept;

		/**
		 * Reverse begin iterator.
		 * @return Pointer to the last element.
		 */
		type *rbegin() const noexcept;
		/**
		 * Reverse end iterator.
		 * @return Pointer to one element before the first.
		 */
		type *rend() const noexcept;



		/**
		 * Get the number of valid elements in the array.
		 * @return Number of valid elements.
		 */
		size_t size() const noexcept;
		/**
		 * Get the total number allocated elements in the array.
		 * @return Number of allocated elements.
		 */
		size_t allocated_size() const noexcept;

		/**
		 * Get the number of front elements that can be pushed before
		 * reallocating the array.
		 * @return Number of free elements in the front.
		 */
		size_t available_front_pool() const noexcept;
		/**
		 * Get the number of back elements that can be pushed before
		 * reallocating the array.
		 * @return Number of free elements in the back.
		 */
		size_t available_back_pool() const noexcept;

		/**
		 * Check if the array is empty.
		 * @return True if there are no valid elements, false otherwise.
		 */
		bool_t empty() const noexcept;


		/**
		 * Set the amount of elements to pad in the front on each reallocation.
		 * @param [in] size Number of elements to pad front.
		 * @return Self instance.
		 */
		array &set_front_pool(size_t size) noexcept;
		/**
		 * Set the amount of elements to pad in the back on each reallocation.
		 * @param [in] size Number of elements to pad back.
		 * @return Self instance.
		 */
		array &set_back_pool(size_t size) noexcept;


		/**
		 * Expand the allocated memory to fit more values preserving the current
		 * ones.
		 * @param [in] front_size Number of front elements to reserve.
		 * @param [in] back_size Number of back elements to reserve.
		 * @return Self instance.
		 */
		array &expand(size_t front_size, size_t back_size) noexcept;
		/**
		 * Expand the allocated memory to fit more values in the front of the
		 * array preserving the current ones.
		 * @param [in] size Number of front elements to reserve.
		 * @return Self instance.
		 */
		array &expand_front(size_t size) noexcept;
		/**
		 * Expand the allocated memory to fit more values in the back of the
		 * array preserving the current ones.
		 * @param [in] size Number of back elements to reserve.
		 * @return Self instance.
		 */
		array &expand_back(size_t size) noexcept;


		/**
		 * Reduce allocated memory preserving values in the array.
		 * @param [in] front_size Number of elements to reduce from front pool.
		 * Default = max front padding.
		 * @param [in] back_size Number of elements to reduce from back pool.
		 * Default = max back padding.
		 * @return Self instance.
		 */
		array &compact(size_t front_size = -1ul,
		               size_t back_size = -1ul) noexcept;
		/**
		 * Reduce allocated memory preserving values in the front of the array.
		 * @param [in] size Number of elements to reduce from front pool.
		 * Default = max back padding.
		 * @return Self instance.
		 */
		array &compact_front(size_t size = -1ul) noexcept;
		/**
		 * Reduce allocated memory preserving values in the back of the array.
		 * @param [in] size Number of elements to reduce from back pool. Default
		 * = max back padding.
		 * @return Self instance.
		 */
		array &compact_back(size_t size = -1ul) noexcept;


		/**
		 * Insert a value at a given position in the array.
		 * @param [in] value Value to be inserted.
		 * @param [in] position Position to insert the value in.
		 * @throw out_of_range_error when inserting in an invalid position.
		 * @return Self instance.
		 */
		array &push(const type &value, ssize_t position);
		/**
		 * Insert a value at a given position in the array.
		 * @param [in] value Value to be inserted.
		 * @param [in] position Position to insert the value in.
		 * @throw out_of_range_error when inserting in an invalid position.
		 * @return Self instance.
		 */
		array &push(const type &value, size_t position);
		/**
		 * Insert a value at a given position in the array.
		 * @param [in] value Value to be inserted.
		 * @param [in] position Position to insert the value in.
		 * @throw out_of_range_error when inserting in an invalid position.
		 * @return Self instance.
		 */
		array &push(const type &value, int32_t position);
		/**
		 * Insert a value at a given position in the array.
		 * @param [in] value Value to be inserted.
		 * @param [in] position Position to insert the value in.
		 * @throw out_of_range_error when inserting in an invalid position.
		 * @return Self instance.
		 */
		array &push(const type &value, uint32_t position);
		/**
		 * Insert a value at the beginning of the array.
		 * @param [in] value Value to be inserted.
		 * @return Self instance.
		 */
		array &push_front(const type &value) noexcept;
		/**
		 * Insert a value at the end of the array.
		 * @param [in] value Value to be inserted.
		 * @return Self instance.
		 */
		array &push_back(const type &value) noexcept;


		/**
		 * Remove the value located a given position in the array.
		 * @param [in] position Position in which the value will be removed.
		 * @throw out_of_range_error when removing at an invalid position.
		 * @return Self instance.
		 */
		array &pop(ssize_t position);
		/**
		 * Remove the value located a given position in the array.
		 * @param [in] position Position in which the value will be removed.
		 * @throw out_of_range_error when removing at an invalid position.
		 * @return Self instance.
		 */
		array &pop(size_t position);
		/**
		 * Remove the value located a given position in the array.
		 * @param [in] position Position in which the value will be removed.
		 * @throw out_of_range_error when removing at an invalid position.
		 * @return Self instance.
		 */
		array &pop(int32_t position);
		/**
		 * Remove the value located a given position in the array.
		 * @param [in] position Position in which the value will be removed.
		 * @throw out_of_range_error when removing at an invalid position.
		 * @return Self instance.
		 */
		array &pop(uint32_t position);
		/**
		 * Remove a value from the beginning of the array.
		 * @param [in] value Value to be removed.
		 * @return Self instance.
		 */
		array &pop_front();
		/**
		 * Remove a value from the end of the array.
		 * @param [in] value Value to be removed.
		 * @return Self instance.
		 */
		array &pop_back();


		/**
		 * Clear array values keeping its allocated size.
		 * @return Self instance.
		 */
		array &clear() noexcept;


		/**
		 * Get the value at a given position. Negative integers start from the
		 * last allocated value.
		 * @param [in] position Position of the value to return.
		 * @throw out_of_range_error when accessing a value outside the array.
		 * @return The value stored in the given position.
		 */
		type &operator[](ssize_t position) const;
		/**
		 * Get the value at a given position.
		 * @param [in] position Position of the value to return.
		 * @throw out_of_range_error when accessing a value outside the array.
		 * @return The value stored in the given position.
		 */
		type &operator[](size_t position) const;
		/**
		 * Get the value at a given position. Negative integers start from the
		 * last allocated value. Exists for typical values.
		 * @param [in] position Position of the value to return.
		 * @throw out_of_range_error when accessing a value outside the array.
		 * @return The value stored in the given position.
		 */
		type &operator[](int32_t position) const;
		/**
		 * Get the value at a given position. Exists for typical values.
		 * @param [in] position Position of the value to return.
		 * @throw out_of_range_error when accessing a value outside the array.
		 * @return The value stored in the given position.
		 */
		type &operator[](uint32_t position) const;

		/**
		 * Replace an array copying from a constexpr list.
		 * @param [in] list Constant list to replace the array.
		 */
		array &operator=(const list_constexpr<type> &list) noexcept;
		/**
		 * Default copy initializer.
		 * @param [in] array Array to copy from.
		 * @return Self instance.
		 */
		array &operator=(const array &array) noexcept = default;
		/**
		 * Move initializer.
		 * @param [in] array Array to move from and clear.
		 * @return Self instance.
		 */
		array &operator=(array &&array) noexcept;

		/**
		 * Ability to cast the array to basic array.
		 * @return Pointer to the array of the valid values.
		 */
		operator type *() const noexcept;
	};


}   // namespace stick


#	define _stick_lib_data_structures_array_impl_
#	include "../data_structures/array_impl.hpp"
#	undef _stick_lib_data_structures_array_impl_


#endif   //_stick_lib_data_structures_array_
