/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** Hitbox
*/

#pragma once

#include "SFML.hpp"

struct Hitbox {
    Hitbox(sf::IntRect rect = {}) : rect(rect) {};
    sf::IntRect rect;
};
