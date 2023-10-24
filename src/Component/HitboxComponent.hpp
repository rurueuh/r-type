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

    virtual std::string toString() override {
        std::stringstream ss = std::stringstream();
        ss << rect.left << ' ' << rect.top << ' ' << rect.width << ' ' << rect.height;
        return ss.str();
    }

    virtual void fromString(std::string str) override {
        std::stringstream ss = std::stringstream(str);
        ss >> rect.left >> rect.top >> rect.width >> rect.height;

        rect = sf::IntRect(rect.left, rect.top, rect.width, rect.height);
    }

    sf::IntRect rect;
};
