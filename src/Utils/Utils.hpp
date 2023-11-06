#pragma once

#include <typeindex>
#include <typeinfo>
#include <string>
#include <unordered_map>
#include <iostream>
#include "SFML.hpp"

namespace Utils
{
	const std::unordered_map<sf::Keyboard::Key, std::string> KEYMAP = {
			{sf::Keyboard::Key::Z, "z"},
			{sf::Keyboard::Key::Q, "q"},
			{sf::Keyboard::Key::S, "s"},
			{sf::Keyboard::Key::D, "d"},
			{sf::Keyboard::Key::Space, " "},
			{sf::Keyboard::Key::M, "m"},
	};

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

	inline std::unordered_map <std::type_index, std::string > typeMap;
	inline std::unordered_map <std::type_index, std::string > typeLevel;

	template <typename T>
	inline void registerComponent(std::string str)
	{
		if (typeMap.find(getTypeId<T>()) != typeMap.end())
			std::cerr << "WARNING: Component " << getTypeName(getTypeId<T>()) << " already registered" << std::endl;
		typeMap[getTypeId<T>()] = str;
	}

	inline std::string getRegisteredComponent(std::type_index index)
	{
		if (typeMap.find(index) == typeMap.end())
			return "Unknown";
		return typeMap[index];
	}

	template <typename T>
	inline void registerLevel(std::string str)
	{
		if (typeLevel.find(getTypeId<T>()) != typeLevel.end())
			std::cerr << "WARNING: Level " << getTypeName(getTypeId<T>()) << " already registered" << std::endl;
		typeLevel[getTypeId<T>()] = str;
	}

	inline std::string getRegisteredLevel(std::type_index index)
	{
		if (typeLevel.find(index) == typeLevel.end())
			return "Unknown";
		return typeLevel[index];
	}
}
