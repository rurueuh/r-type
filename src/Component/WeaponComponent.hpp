/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** WeaponComponent
*/

#pragma once

#include "ComponentBase.hpp"

enum WeaponType {
    LASER = 0,
    MISSILE,
    NONE
};

struct WeaponComponent : public Component {
    WeaponComponent(int damage, float fireRate, WeaponType type) : damage(damage), fireRate(fireRate), type(type) {};
    int damage;
    float fireRate;
    WeaponType type;

    virtual std::string toString() override {
        std::stringstream ss = std::stringstream();
        ss << damage << ' ' << fireRate << ' ' << type;
        return ss.str();
    }

    virtual void fromString(std::string str) override {
        std::stringstream ss = std::stringstream(str);
        ss >> damage >> fireRate >> type;
    }
}