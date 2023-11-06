#pragma once

#include <iostream>
#include <string>
#include <sstream>

struct Component {
	Component() {};
	~Component() {};

	inline virtual std::string toString(void) const = 0;
	virtual void fromString(std::string) = 0;
};
