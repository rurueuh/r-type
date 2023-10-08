#pragma once

#include <typeindex>
#include <typeinfo>
#include <string>
#include <unordered_map>
#include <iostream>

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

	inline std::string getTypeName(std::type_index index) {
		// TODO: check if is a other solution can be better (like a real map)
		std::string name = index.name(); // Demangle
		name = name.substr(name.find_last_of(' ') + 1);
		return name;
	}

	static std::unordered_map<std::type_index, std::string>& getTypeMap()
	{
		static std::unordered_map <std::type_index, std::string > typeMap;
		return typeMap;
	}

	template <typename T>
	inline void registerComponent(std::string str)
	{
		auto &map = getTypeMap();
		if (map.find(getTypeId<T>()) != map.end())
			std::cerr << "WARNING: Component " << getTypeName(getTypeId<T>()) << " already registered" << std::endl;
		map[getTypeId<T>()] = str;
	}

	inline std::string getRegisteredComponent(std::type_index index)
	{
		auto &map = getTypeMap();
		if (map.find(index) == map.end())
			return "Unknown";
		return map[index];
	}
}
