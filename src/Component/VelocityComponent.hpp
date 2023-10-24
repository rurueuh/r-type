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
        VelocityComponent(int x, int y) : velocity(sf::Vector2f(x, y)) {};
        VelocityComponent(sf::Vector2f velocity) : velocity(velocity) {};
        VelocityComponent() = default;
        ~VelocityComponent() = default;

        sf::Vector2f velocity = sf::Vector2f(0, 0);

        virtual std::string toString(void) {
            std::stringstream ss = std::stringstream();
            ss << velocity.x << " " << velocity.y;
            return ss.str();
        }

        virtual void fromString(std::string str) override {
            std::stringstream ss = std::stringstream(str);
            ss >> velocity.x >> velocity.y;
        }
    protected:
    private:
};
