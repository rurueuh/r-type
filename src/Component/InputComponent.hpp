#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include "ComponentBase.hpp"

namespace ECS {
	class Entity;
}

namespace Input {
	/**
	 * @brief Enum for input key
	*/
	enum Key {
		none, 
		forward, 
		backward,
		left,
		right,
		jump,
		secret,
	};
	/**
	 * @brief Map for input key
	*/
	const std::vector<std::pair<Key, std::string>> keyConfig = {
		{Key::forward, "z"},
		{Key::backward, "s"},
		{Key::left, "q"},
		{Key::right, "d"},
		{Key::jump, " "},
		{Key::secret, "m"},
	};
};

/**
 * @brief Component for input
*/
class InputComponent : public Component {
public:
	/**
	 * @brief Construct a new Input Component object
	 * @param input The input
	*/
	InputComponent(std::string input) : input(input) {};
	/**
	 * @brief Construct a new Input Component object
	 * @param functionInput The function input
	 * @details The function input is a map of function to call when the key is pressed
	 * The key is the key of the input
	*/
	InputComponent(std::unordered_map<Input::Key, std::function<void(ECS::Entity *, const float&)>> functionInput) : functionInput(functionInput) {};
	InputComponent() : input("") {};
	~InputComponent() = default;

	/**
	 * @brief Put the input on string
	 * @return The string of the input
	*/
	inline virtual std::string toString(void) const {
		std::string str = "";
		str += input;
		return str;
	}

	/**
	 * @brief Construct the input from string
	 * @param str The string of the input
	*/
	virtual void fromString(std::string str) override {
		std::stringstream ss = std::stringstream(str);
		ss >> input;
	}

	/**
	 * @brief Get the key pressed
	 * @return The key pressed
	*/
	Input::Key getKeyPressed(void) {
		for (auto &key : Input::keyConfig) {
			if (input.find(key.second) != std::string::npos)
				return key.first;
		}
		return Input::Key::none;
	}
	/**
	 * @brief Check if the key is pressed
	 * @param key The key to check
	 * @return true if the key is pressed
	 * @return false if the key is not pressed
	*/
	bool isKeyPressed(Input::Key key) {
		return input.find(Input::keyConfig[key].second) != std::string::npos;
	}

	std::string input = "";
	std::unordered_map<Input::Key, std::function<void(ECS::Entity*, const float &)>> functionInput = {};
	private:
};