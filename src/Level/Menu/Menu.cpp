/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Menu
*/

#include "Menu.hpp"
#include "Player.hpp"
#include "TextureManager.hpp"

Menu::Menu()
{
    TextureManager::loadTextureInMemory({"./1322308.jpeg"});
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