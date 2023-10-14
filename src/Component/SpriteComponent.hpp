/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** SpriteComponent
*/

#pragma once
#include "SFML.hpp"

struct SpriteComponent {
    sf::Texture *texture;
    sf::IntRect rect;
    SpriteComponent(sf::Texture *texture, sf::IntRect rect = {}) : texture(texture), rect(rect) {};
    SpriteComponent() : texture(nullptr), rect() {}
};

