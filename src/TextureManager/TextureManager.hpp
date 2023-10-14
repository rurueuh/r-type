/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** TextureManager
*/

#pragma once
#include <map>
#include "SFML.hpp"

class TextureManager {
    public:
        TextureManager() = default;
        ~TextureManager() = default;

        static sf::Texture& getTexture(const std::string& path);

    protected:
    private:
      static std::map<std::string, sf::Texture> _textures;
};
