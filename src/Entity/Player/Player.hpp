/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Player
*/

#pragma once

#include "Entity.hpp"

class Player : public Entity {
    public:
        Player();
        ~Player();

        void update(const float dt);
        void draw(sf::RenderTarget& target);

    protected:
    private:
};
