/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Player
*/

#include "Player.hpp"
#include "Drawable.hpp"

Player::Player()
{
    this->addComponent<Drawable>("./assets/player.png");
}

Player::~Player()
{
}

void Player::update(const float dt)
{
    std::cout << "Player update" << std::endl;
}

void Player::draw(sf::RenderTarget& target)
{
}
