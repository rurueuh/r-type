/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** TransformComponent
*/

#pragma once

#include "SFML.hpp"
#include "ComponentBase.hpp"
#include "DrawableComponent.hpp"

/**
 * @brief Component for transform
 * @brief position: position
 * @brief scale: scale
 * @brief rotation: rotation
 */
struct TransformComponent : public Component {
    /**
     * @brief Construct a new Transform Component object
     * @param position position
     * @param scale scale
     * @param rotation rotation
     * @return A new TransformComponent
    */
    TransformComponent(sf::Vector2f position, sf::Vector2f scale, float rotation) : position(position), scale(scale), rotation(rotation) {};
    TransformComponent() : position(sf::Vector2f(0.f, 0.f)), scale(sf::Vector2f(0.f, 0.f)), rotation(0.f) {};
    sf::Vector2f position;
    sf::Vector2f scale;
    float rotation;

    /**
     * @brief Get the Transform object
     * @return std::string
    */
    inline virtual std::string toString() const override {
        std::string str = "";
        str += std::to_string(position.x) + " ";
        str += std::to_string(position.y) + " ";
        str += std::to_string(scale.x) + " ";
        str += std::to_string(scale.y) + " ";
        str += std::to_string(rotation);
        return str;
    }

    /**
     * @brief Set the Transform object
     * @param str
    */
    virtual void fromString(std::string str) override {
        std::stringstream ss = std::stringstream(str);
        ss >> position.x >> position.y >> scale.x >> scale.y >> rotation;
    }
    
    /**
     * @brief Set the Full Screen object
     * @param window
     * @param area
    */
    void setFullScreen(sf::RenderWindow* window, sf::IntRect &area) {
        sf::Vector2u size = { 1600, 900 };
    #ifndef SERVER
            size = window->getSize();
    #endif
        sf::Vector2f scale = sf::Vector2f((float)size.x / area.width, (float)size.y / area.height);
        sf::Vector2f position = sf::Vector2f((float)area.left, (float)area.top);
        this->scale = scale;
        this->position = position;
	}
};
