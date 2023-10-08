#pragma once

#include <iostream>

struct Component {
	Component() {};
	~Component() {};

	virtual std::string toString(void) {
		return "test";
	}
};
