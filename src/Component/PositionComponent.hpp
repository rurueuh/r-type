/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** PositionComponent
*/

#pragma once

struct PositionComponent {
    PositionComponent(float x, float y) : x(x), y(y) {};
    PositionComponent() : x(0), y(0) {};
    float x, y;
};