#pragma once

#include <iostream>
#include <sstream>
#include "ComponentBase.hpp"

/**
 * @brief Component for player
 * @details The player is a string hash
*/
class PlayerComponent : public Component {
public:
	/**
	 * @brief Construct a new Player Component object
	 * @param hash The hash of the player
	 * @details The hash is the name of the player
	*/
	PlayerComponent(std::string hash) : hash(hash) {};
	PlayerComponent() : hash("") {};
	~PlayerComponent() = default;

	std::string hash = "";

	/**
	 * @brief Put the player on string
	 * @return The string of the player
	*/
	inline virtual std::string toString(void) const {
		std::string str = "";
		str += hash;
		return str;
	}

	/// @brief Construct the player from string
	/// @param str The string of the player
	virtual void fromString(std::string str) override {
		std::stringstream ss = std::stringstream(str);
		ss >> hash;
	}
};