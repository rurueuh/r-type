/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Drawable
*/

#pragma once

#include "Component.hpp"

class Drawable : public Component {
    public:
        Drawable(Entity *self, std::string texture);
        ~Drawable();


    protected:
    private:
        sf::Texture _texture;
        sf::Sprite _sprite;
};
