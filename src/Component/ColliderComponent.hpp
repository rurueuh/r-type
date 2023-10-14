/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** ColliderComponent
*/

#pragma once

#include "SFML.hpp"

struct ColliderComponent {
    ColliderComponent(Vector2f size) : size(size) {};
    ColliderComponent() : size(Vector2f(0, 0)) {};
    Vector2f size;
};

