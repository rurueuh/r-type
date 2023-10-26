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
	enum Key {
		none, 
		forward, 
		backward,
		left,
		right,
		jump,
	};
	const std::vector<std::pair<Key, std::string>> keyConfig = {
		{Key::forward, "z"},
		{Key::backward, "s"},
		{Key::left, "q"},
		{Key::right, "d"},
		{Key::jump, " "},
	};
};

struct InputComponent : public Component {
	
	InputComponent(std::string input) : input(input) {};
	InputComponent(std::unordered_map<Input::Key, std::function<void(ECS::Entity *, const float&)>> functionInput) : functionInput(functionInput) {};
	InputComponent() : input("") {};
	~InputComponent() = default;


	inline virtual std::string toString(void) const {
		std::string str = "";
		str += input;
		return str;
	}

	virtual void fromString(std::string str) override {
		std::stringstream ss = std::stringstream(str);
		ss >> input;
	}

	Input::Key getKeyPressed(void) {
		for (auto &key : Input::keyConfig) {
			if (input.find(key.second) != std::string::npos)
				return key.first;
		}
		return Input::Key::none;
	}
	bool isKeyPressed(Input::Key key) {
		return input.find(Input::keyConfig[key].second) != std::string::npos;
	}

	std::string input = "";
	std::unordered_map<Input::Key, std::function<void(ECS::Entity*, const float &)>> functionInput = {};
	private:
};