/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** SpriteComponent
*/

#pragma once
#include "SFML.hpp"
#include "ComponentBase.hpp"

struct SpriteComponent : public Component {
    SpriteComponent(std::string path) : path(path) {
        texture.loadFromFile(path);
        sprite.setTexture(texture);
    };

    virtual std::string toString(void) {
    }

    virtual void fromString(std::string str) override {
    }

    sf::Sprite sprite;
    sf::Texture texture;
    std::string path;
};



