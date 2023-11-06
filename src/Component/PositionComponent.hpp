/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** PositionComponent
*/

#pragma once

/**
 * @brief Component for position
 * @brief x: x position
 * @deprecated not used
 */
class PositionComponent {
    PositionComponent(float x, float y) : x(x), y(y) {};
    PositionComponent() : x(0), y(0) {};
    float x, y;
};