/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** WeaponComponent
*/

#pragma once

#include "ComponentBase.hpp"
#include "ShootType.hpp"


struct WeaponComponent : public Component {
    WeaponComponent(int damage, float fireRate, ShootType type) : damage(damage), fireRate(fireRate), type(type) {};
    WeaponComponent() : damage(0), fireRate(0), type(ShootType::MISSILE) {};

    virtual std::string toString() override {
        std::stringstream ss = std::stringstream();
        ss << damage << ' ' << fireRate << ' ' << type;
        return ss.str();
    }

    virtual void fromString(std::string str) override {
        std::stringstream ss = std::stringstream(str);
        ss >> damage >> fireRate >> type;
    }
    int damage;
    float fireRate;
    ShootType type;
};