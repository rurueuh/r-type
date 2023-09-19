/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Menu
*/

#pragma once

#include "Level.hpp"

class Menu : public Level {
    public:
        Menu();
        ~Menu();

        void update(const float dt) override;
        void draw(sf::RenderTarget& target) override;

    protected:
    private:
};
