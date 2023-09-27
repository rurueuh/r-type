/*
** EPITECH PROJECT, 2023
** B-rtype
** File description:
** ComponantList
*/

#pragma once

#include <bits/stdc++.h>
#include "Componant.hpp"
#include "Entity.hpp"

class ComponantList {
    public:
        ComponantList() = default;
        ~ComponantList() = default;

        template<typename T>
        std::shared_ptr<T> addComponent(std::shared_ptr<Entity> &entity) noexcept
        {
            std::shared_ptr<T> componant = std::make_shared<T>();
            _componants.push_back(componant);
            entity->addComponent(componant);
            return componant;
        }

    protected:
    private:
        std::vector<std::shared_ptr<Componant>> _componants = {};
};
