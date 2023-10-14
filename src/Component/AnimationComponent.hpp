/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** AnimationComponent
*/

#pragma once
#include "SFML.hpp"

struct AnimationComponent {
    AnimationComponent(sf::Texture *texture, sf::IntRect rect = {}) : texture(texture), rect(rect) {};
    AnimationComponent() : texture(nullptr), rect(sf::IntRect(0, 0, 0, 0)) {};
    sf::Texture *texture;
    sf::IntRect rect;
};