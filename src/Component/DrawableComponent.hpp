/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** SpriteComponent
*/

#pragma once
#include "SFML.hpp"
#include "TextureManager.hpp"
#include "ComponentBase.hpp"
#include <sstream>

struct SpriteComponent : public Component {

    SpriteComponent(std::string path) : path(path) {
        texture = TextureManager::getTexture(path);
        sprite.setTexture(texture);
    };

    SpriteComponent(std::string path, sf::IntRect area) : path(path), area(area) {
        texture = TextureManager::getTexture(path);
        sprite.setTexture(texture);
        sprite.setTextureRect(area);
    };

    virtual std::string toString() const override {
        std::stringstream ss = std::stringstream();
        ss << path << ' ' << area.left << ' ' << area.top << ' ' << area.width << ' ' << area.height;
        return ss.str();

    }

    virtual void fromString(const std::string& str) override {
        std::stringstream ss = std::stringstream(str);
        ss >> path >> area.left >> area.top >> area.width >> area.height;
        texture = TextureManager::getTexture(path);
        sprite.setTexture(texture);
        sprite.setTextureRect(area);
    }

    std::string path;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::IntRect area;
};
