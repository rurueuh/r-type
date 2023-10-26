/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** VelocityComponent
*/

#pragma once
#include <sstream>
#include "SFML.hpp"
#include "ComponentBase.hpp"

struct VelocityComponent : public Component {
    public:
        VelocityComponent(float x, float y) : velocity(sf::Vector2f(x, y)) {};
        VelocityComponent(sf::Vector2f velocity) : velocity(velocity) {};
        VelocityComponent() = default;
        ~VelocityComponent() = default;

        sf::Vector2f velocity = sf::Vector2f(0, 0);

        inline virtual std::string toString(void) const {
            std::string str = "";
            str += std::to_string(velocity.x) + " ";
            str += std::to_string(velocity.y);
            return str;
        }

        virtual void fromString(std::string str) override {
            std::stringstream ss = std::stringstream(str);
            ss >> velocity.x >> velocity.y;
        }
    protected:
    private:
};
