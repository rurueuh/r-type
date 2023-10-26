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
    TransformComponent() : position(sf::Vector2f(0.f, 0.f)), scale(sf::Vector2f(0.f, 0.f)), rotation(0.f) {};
    sf::Vector2f position;
    sf::Vector2f scale;
    float rotation;

    inline virtual std::string toString() const override {
        std::string str = "";
        str += std::to_string(position.x) + " ";
        str += std::to_string(position.y) + " ";
        str += std::to_string(scale.x) + " ";
        str += std::to_string(scale.y) + " ";
        str += std::to_string(rotation);
        return str;
    }

    virtual void fromString(std::string str) override {
        std::stringstream ss = std::stringstream(str);
        ss >> position.x >> position.y >> scale.x >> scale.y >> rotation;
    }
};
