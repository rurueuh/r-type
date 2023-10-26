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

struct Hitbox : public Component {
    Hitbox(sf::IntRect rect) : rect(rect) {};
    Hitbox() : rect({}) {};

    inline virtual std::string toString() const override {
        std::string str = "";
        str += std::to_string(rect.left) + " ";
        str += std::to_string(rect.top) + " ";
        str += std::to_string(rect.width) + " ";
        str += std::to_string(rect.height);
        return str;
    }

    virtual void fromString(std::string str) override {
        std::stringstream ss = std::stringstream(str);
        ss >> rect.left >> rect.top >> rect.width >> rect.height;

        rect = sf::IntRect(rect.left, rect.top, rect.width, rect.height);
    }

    sf::IntRect rect;
};
