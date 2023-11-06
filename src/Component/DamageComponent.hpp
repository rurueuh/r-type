#pragma once

#include <iostream>
#include <sstream>
#include "ComponentBase.hpp"

/**
 * @brief Component for damage
*/
struct DamageComponent : public Component {
    /**
     * @brief Construct a new Damage Component object
     * @param damage
    */
    DamageComponent(float damage) : _damage(damage) {};
    DamageComponent() : _damage(0) {};
    /**
     * @brief Get the damage
    */
    float _damage;

    /**
     * @brief Put the damage on string
    */
    inline virtual std::string toString(void) const {
        std::string str = "";
        str += std::to_string(_damage) + " ";
        return str;
	}

    /**
     * @brief Construct the damage from string
    */
    virtual void fromString(std::string str) override {
        std::stringstream ss = std::stringstream(str);
        ss >> _damage;
    }
};