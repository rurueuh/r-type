#pragma once

#include <iostream>
#include <sstream>
#include "ComponentBase.hpp"

struct InputComponent : public Component {
	
	InputComponent(std::string input) : input(input) {};
	InputComponent() : input("") {};
	~InputComponent() = default;

	std::string input = "";

	virtual std::string toString(void) {
		std::stringstream ss = std::stringstream();
		ss << input;
		return ss.str();
	}

	virtual void fromString(std::string str) override {
		std::stringstream ss = std::stringstream(str);
		ss >> input;
	}
};