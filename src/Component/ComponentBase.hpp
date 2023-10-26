#pragma once

#include <iostream>

struct Component {
	Component() {};
	~Component() {};

	inline virtual std::string toString(void) const = 0;
	virtual void fromString(std::string) = 0;
};
