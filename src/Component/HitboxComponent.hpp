/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** Hitbox
*/

#pragma once

#include "SFML.hpp"
#include "ComponentBase.hpp"
#include <sstream>

/**
 * @brief Component for hitbox
 * @deprecated Not used anymore (use Collider instead)
 */
struct Hitbox : public Component {
    /**
     * @brief Constructor
     * @param rect The hitbox
    */
    Hitbox(sf::IntRect rect) : rect(rect) {};
    Hitbox() : rect({}) {};

    /**
     * @brief Convert the hitbox to a string
     * @return The hitbox as a string
    */
    inline virtual std::string toString() const override {
        std::string str = "";
        str += std::to_string(rect.left) + " ";
        str += std::to_string(rect.top) + " ";
        str += std::to_string(rect.width) + " ";
        str += std::to_string(rect.height);
        return str;
    }

    /**
     * @brief Convert a string to a hitbox
     * @param str The string to convert
    */
    virtual void fromString(std::string str) override {
        std::stringstream ss = std::stringstream(str);
        ss >> rect.left >> rect.top >> rect.width >> rect.height;

        rect = sf::IntRect(rect.left, rect.top, rect.width, rect.height);
    }

    sf::IntRect rect;
};
