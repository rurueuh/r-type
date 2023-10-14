/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** TransformComponent
*/

#pragma once

#include "SFML.hpp"

struct TransformComponent {
    TransformComponent(sf::Vector2f position, sf::Vector2f scale, float rotation) : position(position), scale(scale), rotation(rotation) {};
    TransformComponent() : position(sf::Vector2f(0, 0)), scale(sf::Vector2f(0, 0)), rotation(0) {};
    sf::Vector2f position;
    sf::Vector2f scale;
    float rotation;
};