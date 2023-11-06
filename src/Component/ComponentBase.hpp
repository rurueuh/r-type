#pragma once

#include <iostream>
#include <string>
#include <sstream>

/**
 * @brief Base class for all components
*/
struct Component {
	Component() {};
	~Component() {};

	/**
	 * @brief Convert the component to a string
	 * @return std::string
	*/
	inline virtual std::string toString(void) const = 0;

	/**
	 * @brief Convert the string to a component
	*/
	virtual void fromString(std::string) = 0;
};
