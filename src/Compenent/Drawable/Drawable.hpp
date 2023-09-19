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
        Drawable(Entity *self);
        ~Drawable();

        void loadTexture(const std::string &path);

        void update(const float dt) override;
        void draw(sf::RenderTarget& target) override;

    protected:
    private:
        sf::Texture _texture;
        sf::Sprite _sprite;
};
