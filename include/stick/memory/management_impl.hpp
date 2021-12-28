/**
 * Memory management utilities. Template implementations.
 * @brief Memory management template implementations.
 * @file management_impl.hpp
 * @author Julio C. Galindo (stickM4N)
 */
#if defined(_stick_lib_memory_management_impl_)


#	include "../error/memory_error.hpp"
#	include "../memory/storage.hpp"


namespace stick {


	template<typename type>
	inline type *allocate(size_t element_amount) {
		if (element_amount == 0)
			throw memory_error("Allocating 0 bytes is not a logic behaviour.");

		if (sizeof(type) * element_amount
		    >= 1ul << 31)   // Allocating +2 GigaBytes.
			throw memory_error(
			    "Allocating 2 gigabytes consecutively is prohibited, "
			    "try allocating separated memory spaces.");

		return new type[element_amount];
	}

	template<typename type>
	inline type *allocate_value(const type &value) {
		auto ptr = allocate<type>(1);
		*ptr = value;

		return ptr;
	}

	template<typename type, size_t alignment>
	inline type *allocate_aligned(size_t element_amount) {
		if (element_amount == 0)
			throw memory_error("Allocating 0 bytes is not a logic behaviour.");

		if ((sizeof(type) > alignment ? sizeof(type) : alignment)
		        * element_amount
		    >= 1ul << 31)   // Allocating +2 Gigabytes.
			throw memory_error(
			    "Allocating 2 gigabytes consecutively is prohibited, "
			    "try allocating separated memory spaces.");

		return new storage_aligned<sizeof(type), alignment>[element_amount];
	}

	template<typename type>
	inline void_t deallocate(type *&data) {
		if (data == nullptr)
			throw memory_error("Deallocating nullptr!");

		delete[] data;
		data = nullptr;
	}


	template<typename type>
	inline void_t set(type *address, const type &value,
	                  size_t element_amount) noexcept {
		auto data = reinterpret_cast<byte_t *>(address);
		auto value_data = reinterpret_cast<const byte_t *>(&value);

		for (size_t i = 0ul; i < element_amount; i++)
			for (size_t j = 0ul; j < sizeof(type); j++)
				data[i * sizeof(type) + j] = value_data[j];
	}
	template<typename type>
	inline void_t set(type *address, const byte_t &value,
	                  size_t element_amount) noexcept {
		auto data = reinterpret_cast<byte_t *>(address);

		for (size_t i = 0ul; i < element_amount; i++)
			for (size_t j = 0ul; j < sizeof(type); j++)
				data[i * sizeof(type) + j] = value;
	}

	template<typename type>
	inline void_t clear(type *address, size_t element_amount) noexcept {
		set(address, null, element_amount);
	}

	template<typename type>
	inline void_t copy(const type *source_address, type *destination_address,
	                   size_t element_amount) {
		if (source_address == destination_address)
			return;

		if ((source_address < destination_address
		     and source_address + element_amount >= destination_address)
		    or (destination_address < source_address
		        and destination_address + element_amount >= source_address))
			throw memory_error("Destination data will overwrite source data. "
			                   "Consider moving instead.");

		for (size_t i = 0ul; i < element_amount; i++)
			set(&destination_address[i], source_address[i]);
	}

	template<typename type>
	inline void_t move(type *source_address, type *destination_address,
	                   size_t element_amount) noexcept {

		if (source_address == destination_address)
			return;
		else if (source_address < destination_address) {
			for (size_t i = element_amount - 1; i < -1ul; i--)
				set(&destination_address[i], source_address[i]);

			if (source_address + element_amount >= destination_address)
				clear(source_address, destination_address - source_address);
			else
				clear(source_address, element_amount);

		} else {   // destination_address < source_address
			for (size_t i = 0ul; i < element_amount; i++)
				set(&destination_address[i], source_address[i]);

			if (destination_address + element_amount >= source_address)
				clear(source_address, source_address - destination_address);
			else
				clear(source_address, element_amount);
		}
	}


}   // namespace stick


#else
#	warning This file is included automatically and should not be used on its own!
#endif   //_stick_lib_memory_management_impl_
