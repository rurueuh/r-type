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

/**
 * @brief Component for shoot
 * @brief damage: damage of the shoot
 * @brief type: type of the shoot
 * @deprecated not used
 */
struct ShootComponent : public Component {
    ShootComponent(int damage, ShootType type) : damage(damage), type(type) {};
    ShootComponent() : damage(0), type(ShootType::MISSILE) {};


    inline virtual std::string toString() const override {
        std::string str = "";
        str += std::to_string(damage) + " ";
        str += std::to_string(type);
        return str;
    }

    virtual void fromString(std::string str) override {
        std::stringstream ss = std::stringstream(str);
        ss >> damage >> type;
    }

    ShootType type;
    int damage;
};
