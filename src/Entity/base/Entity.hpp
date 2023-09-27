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
        std::vector<std::shared_ptr<Componant>> &getComponants() noexcept
        {
            return _componants;
        }

    protected:
    private:
        uint64_t _id = -1;
        std::vector<std::shared_ptr<Componant>> _componants = {};
};

inline std::ostream &operator<<(std::ostream &os, Entity &entity) {
    os << "\tEntity{ " << std::endl;
    os << "\t\tId: " << entity.getId() << std::endl;
    os << "\t\tComponants { " << std::endl;
    for (auto &componant : entity.getComponants()) {
        std::string output;
        output += componant->toString();
        os << output << std::endl;
    }
    std::cout << "\t\t}" << std::endl;
    os << "\t}" << std::endl;
    return os;
}