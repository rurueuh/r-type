/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** ShootComponent
*/

#pragma once

#include "ComponentBase.hpp"
#include "ShootType.hpp"
#include <sstream>

struct ShootComponent : public Component {
    ShootComponent(int damage, ShootType type) : damage(damage), type(type) {};
    ShootComponent() : damage(0), type(ShootType::MISSILE) {};


    virtual std::string toString() override {
        std::stringstream ss = std::stringstream();
        ss << damage << ' ' << type;
        return ss.str();
    }

    virtual void fromString(std::string str) override {
        std::stringstream ss = std::stringstream(str);
        ss >> damage >> type;
    }

    ShootType type;
    int damage;
};
