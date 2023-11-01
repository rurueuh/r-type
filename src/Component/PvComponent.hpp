#pragma once

#include <iostream>
#include <sstream>
#include "ComponentBase.hpp"

struct PvComponent : public Component {
    PvComponent(float health, float max) : _health(health), _maxHealth(max)  {};
    PvComponent() : _health(0), _maxHealth(0) {};
    float _health = 0;
    float _maxHealth = 0;

    inline virtual std::string toString(void) const {
        std::string str = "";
        str += std::to_string(_health) + " ";
        str += std::to_string(_maxHealth);
        return str;
	}

    virtual void fromString(std::string str) override {
        std::stringstream ss = std::stringstream(str);
        ss >> _health >> _maxHealth;
    }
};
