#pragma once

#include <iostream>
#include <sstream>
#include "ComponentBase.hpp"

struct PvComponent : public Component {
    PvComponent(int health) : health(health) {};
    PvComponent() : health(0) {};
    int health = 0;

    inline virtual std::string toString(void) const {
        std::string str = "";
        str += std::to_string(health);
        return str;
	}

    virtual void fromString(std::string str) override {
        std::stringstream ss = std::stringstream(str);
        ss >> health;
    }
};
