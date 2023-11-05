#pragma once

#include <iostream>
#include <sstream>
#include "ComponentBase.hpp"

struct DamageComponent : public Component {
    DamageComponent(float damage) : _damage(damage) {};
    DamageComponent() : _damage(0) {};
    float _damage;

    inline virtual std::string toString(void) const {
        std::string str = "";
        str += std::to_string(_damage) + " ";
        return str;
	}

    virtual void fromString(std::string str) override {
        std::stringstream ss = std::stringstream(str);
        ss >> _damage;
    }
};