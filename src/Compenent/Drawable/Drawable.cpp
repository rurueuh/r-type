/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Drawable
*/

#include "Drawable.hpp"

Drawable::Drawable(Entity *self, std::string texture) : Component(self, false, true), _texture(), _sprite(_texture)
{
    std::cout << "Drawable::Drawable" << std::endl;
}

Drawable::~Drawable()
{
}

void Drawable::loadTexture(const std::string &path)
{
    if ( !_texture.loadFromFile(path) )
        throw std::runtime_error("Drawable::loadTexture: Failed to load texture" + path);
    _sprite.setTexture(_texture);
}

void Drawable::update(const float dt)
{
}

void Drawable::draw(sf::RenderTarget& target)
{
    target.draw(_sprite);
}
