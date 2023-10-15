/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** DrawableComponent
*/

#pragma once
#include "SFML.hpp"
#include "TextureManager.hpp"
#include "ComponentBase.hpp"
#include <sstream>

struct DrawableComponent : public Component {

    DrawableComponent() = default;

    DrawableComponent(std::string path) : path(path) {
        #ifndef SERVER
            texture = TextureManager::getTexture(path);
            sprite.setTexture(*texture);
        #endif
    };

    DrawableComponent(std::string path, sf::IntRect area) : path(path), area(area) {
        #ifndef SERVER
            texture = TextureManager::getTexture(path);
            sprite.setTexture(*texture);
            sprite.setTextureRect(area);
        #endif
    };

    virtual std::string toString() override {
        std::stringstream ss = std::stringstream();
        ss << path << ' ' << area.left << ' ' << area.top << ' ' << area.width << ' ' << area.height;
        return ss.str();
    }

    virtual void fromString( std::string str) override {
        std::stringstream ss = std::stringstream(str);
        ss >> path >> area.left >> area.top >> area.width >> area.height;
        #ifndef SERVER
            texture = TextureManager::getTexture(path);
            sprite.setTexture(*texture);
            sprite.setTextureRect(area);
        #endif
    }

    std::string path;
    #ifndef SERVER
        sf::Sprite sprite;
        sf::Texture *texture;
    #endif
    sf::IntRect area;
};
