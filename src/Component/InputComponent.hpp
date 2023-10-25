#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include "ComponentBase.hpp"

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
	InputComponent() : input("") {};
	~InputComponent() = default;


	virtual std::string toString(void) {
		std::stringstream ss = std::stringstream();
		ss << input;
		return ss.str();
	}

	virtual void fromString(std::string str) override {
		std::stringstream ss = std::stringstream(str);
		ss >> input;
	}

	Input::Key getKeyPressed(void) {
		for (auto key : Input::keyConfig) {
			if (input.find(key.second) != std::string::npos)
				return key.first;
		}
		return Input::Key::none;
	}
	bool isKeyPressed(Input::Key key) {
		return input.find(Input::keyConfig[key].second) != std::string::npos;
	}

	std::string input = "";
	private:
};