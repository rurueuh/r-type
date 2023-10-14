/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** TextureManager
*/

#include "TextureManager.hpp"

sf::Texture &TextureManager::getTexture(const std::string &path)
{
    if (_textures.find(path) == _textures.end()) {
        sf::Texture texture;
        texture.loadFromFile(path);
        _textures[path] = texture;
    }
    return _textures[path];
}
