#pragma once

#include <iostream>
#include <sstream>
#include "ComponentBase.hpp"

struct PvComponent : public Component {
    PvComponent(int health) : health(health) {};
    PvComponent() : health(0) {};
    int health = 0;

    virtual std::string toString(void) {
        std::stringstream ss = std::stringstream();
        ss << health;
        return ss.str();
	}

    virtual void fromString(std::string str) override {
        std::stringstream ss = std::stringstream(str);
        ss >> health;
    }
};
