#pragma once

#include <typeindex>
#include <typeinfo>

namespace Utils
{
	template <typename T>
	inline std::type_index getTypeId()
	{
		return std::type_index(typeid(T));
	}

	inline size_t getCounterEntity() {
		static size_t counter = 0;
		return counter++;
	}
}
