/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** WeaponComponent
*/

#pragma once

#include "ComponentBase.hpp"
#include "ShootType.hpp"


/**
 * @brief Component for weapon
 * @brief damage: damage of the weapon
 * @brief fireRate: fire rate of the weapon
 * @brief type: type of the weapon
 * @deprecated not used
 */
class WeaponComponent : public Component {
public:
    WeaponComponent(int damage, float fireRate, ShootType type) : damage(damage), fireRate(fireRate), type(type) {};
    WeaponComponent() : damage(0), fireRate(0), type(ShootType::MISSILE) {};

    inline virtual std::string toString() const override {
        std::string str = "";
        str += std::to_string(damage) + " ";
        str += std::to_string(fireRate) + " ";
        str += std::to_string(type);
        return str;
    }

    virtual void fromString(std::string str) override {
        std::stringstream ss = std::stringstream(str);
        ss >> damage >> fireRate >> type;
    }
    int damage;
    float fireRate;
    ShootType type;
};