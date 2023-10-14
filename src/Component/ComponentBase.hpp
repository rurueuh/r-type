#pragma once

#include <iostream>

struct Component {
	Component() {};
	~Component() {};

	virtual std::string toString(void) = 0;
	virtual void fromString(std::string) = 0;
};
