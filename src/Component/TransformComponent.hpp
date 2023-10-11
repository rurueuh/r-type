/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** TransformComponent
*/

#pragma once

#include "SFML.hpp"

struct TransformComponent {
    TransformComponent(Vector2f position, Vector2f scale, float rotation) : position(position), scale(scale), rotation(rotation) {};
    TransformComponent() : position(Vector2f(0, 0)), scale(Vector2f(0, 0)), rotation(0) {};
    Vector2f position;
    Vector2f scale;
    float rotation;
};