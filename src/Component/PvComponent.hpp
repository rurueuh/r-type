#pragma once

#include <iostream>
#include <sstream>

struct PvComponent {
    PvComponent(int health) : health(health) {};
    PvComponent() : health(0) {};
    int health = 0;

    virtual std::string toString(void) {
        std::stringstream ss = std::stringstream();
        ss << health;
        return ss.str();
	}
};
