#pragma once

#include <iostream>
#include <sstream>
#include "ComponentBase.hpp"

struct PlayerInputComponent : public Component {
	
	PlayerInputComponent(std::string input) : input(input) {};
	PlayerInputComponent() : input("") {};
	~PlayerInputComponent() = default;

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