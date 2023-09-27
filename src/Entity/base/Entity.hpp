/*
** EPITECH PROJECT, 2023
** B-rtype
** File description:
** Entity
*/

#pragma once

#include <bits/stdc++.h>
#include "Componant.hpp"

class Entity {
    public:
        Entity(uint64_t id) : _id(id) {};
        virtual ~Entity() = default;

        uint64_t getId() const { return _id; };

        void addComponent(std::shared_ptr<Componant> componant) noexcept
        {
            _componants.push_back(componant);
        }

    protected:
    private:
        uint64_t _id = -1;
        std::vector<std::shared_ptr<Componant>> _componants = {};
};
