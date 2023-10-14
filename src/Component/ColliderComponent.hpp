/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** ColliderComponent
*/

#pragma once

#include "SFML.hpp"

struct ColliderComponent {
    ColliderComponent(sf::Vector2f size) : size(size) {};
    ColliderComponent() : size(sf::Vector2f(0, 0)) {};
    sf::Vector2f size;
};

