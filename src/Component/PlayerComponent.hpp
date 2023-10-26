#pragma once

#include <iostream>
#include <sstream>
#include "ComponentBase.hpp"

struct PlayerComponent : public Component {
	
	PlayerComponent(std::string hash) : hash(hash) {};
	PlayerComponent() : hash("") {};
	~PlayerComponent() = default;

	std::string hash = "";

	inline virtual std::string toString(void) const {
		std::string str = "";
		str += hash;
		return str;
	}

	virtual void fromString(std::string str) override {
		std::stringstream ss = std::stringstream(str);
		ss >> hash;
	}
};