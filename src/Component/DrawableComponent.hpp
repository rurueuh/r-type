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

/**
 * @brief Component for drawable entity
*/
class DrawableComponent : public Component {
public:

    DrawableComponent() = default;
    /**
     * @brief Construct a new Drawable Component object
     * @param path Path to the texture
    */
    DrawableComponent(std::string path) : path(path) {
        #ifndef SERVER
            texture = TextureManager::getTexture(path);
            sprite.setTexture(*texture);
        #endif
    };

    /**
     * @brief Construct a new Drawable Component object
     * @param path Path to the texture
     * @param area Area of the texture
    */
    DrawableComponent(std::string path, sf::IntRect area) : path(path), area(area) {
        #ifndef SERVER
            texture = TextureManager::getTexture(path);
            sprite.setTexture(*texture);
            if (area.height != 0 && area.width != 0 && area.top != 0 && area.left != 0)
                sprite.setTextureRect(area);
        #endif
    };

    /**
     * @brief Construct a new Drawable Component object
     * @param path Path to the texture
     * @param area Area of the texture
     * @param origin Origin of the texture
    */
    inline virtual std::string toString() const override {
        std::string str = "";
        str += path + " ";
        str += std::to_string(area.left) + " ";
        str += std::to_string(area.top) + " ";
        str += std::to_string(area.width) + " ";
        str += std::to_string(area.height);
        return str;
    }

    /// @brief Construct the drawable from string
    /// @param str The string of the drawable
    virtual void fromString( std::string str) override {
        std::stringstream ss = std::stringstream(str);
        ss >> path >> area.left >> area.top >> area.width >> area.height;
        #ifndef SERVER
            texture = TextureManager::getTexture(path);
            sprite.setTexture(*texture);
            if (area.height != 0 && area.width != 0 && area.top != 0 && area.left != 0)
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
