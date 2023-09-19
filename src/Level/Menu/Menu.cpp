/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Menu
*/

#include "Menu.hpp"
#include "Player.hpp"

Menu::Menu()
{
    this->addEntity<Player>();
}

Menu::~Menu()
{
}

void Menu::update(const float dt)
{
    std::cout << "Menu update" << std::endl;
}

void Menu::draw(sf::RenderTarget& target)
{
}