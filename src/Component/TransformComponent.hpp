/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** TransformComponent
*/

#pragma once

#include "SFML.hpp"
#include "ComponentBase.hpp"

struct TransformComponent : public Component {
    TransformComponent(sf::Vector2f position, sf::Vector2f scale, float rotation) : position(position), scale(scale), rotation(rotation) {};
    TransformComponent() : position(sf::Vector2f(0, 0)), scale(sf::Vector2f(0, 0)), rotation(0) {};
    sf::Vector2f position;
    sf::Vector2f scale;
    float rotation;

    virtual std::string toString() override {
        std::stringstream ss = std::stringstream();
        ss << position.x << ' ' << position.y << ' ' << scale.x << ' ' << scale.y << ' ' << rotation;
        return ss.str();
    }

    virtual void fromString(std::string str) override {
        std::stringstream ss = std::stringstream(str);
        ss >> position.x >> position.y >> scale.x >> scale.y >> rotation;
    }
};
