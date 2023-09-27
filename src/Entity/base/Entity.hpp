/*
** EPITECH PROJECT, 2023
** B-rtype
** File description:
** Entity
*/

#pragma once

#include <bits/stdc++.h>
#include "Component.hpp"

class Entity {
    public:
        Entity(uint64_t id) : _id(id) {};
        virtual ~Entity() = default;

        uint64_t getId() const { return _id; };

        void addComponent(std::shared_ptr<Component> Component) noexcept
        {
            if (hasComponent(Component)){
                #ifdef DEBUG
                    PRINT_ERROR("Entity already has this Component")
                #endif
                return;
            }
            _Components.push_back(Component);
        }
        std::vector<std::shared_ptr<Component>> &getComponents() noexcept
        {
            return _Components;
        }

        template <typename T>
        std::shared_ptr<T> getComponent() noexcept
        {
            for (auto &Component : _Components) {
                if (typeid(*Component) == typeid(T))
                    return std::dynamic_pointer_cast<T>(Component);
            }
            return nullptr;
        }

        template <typename T>
        bool hasComponent() noexcept
        {
            for (auto &Component : _Components) {
                if (typeid(*Component) == typeid(T))
                    return true;
            }
            return false;
        }
        bool hasComponent(std::shared_ptr<Component> content) noexcept
        {
            for (auto &Component : _Components) {
                if (typeid(*Component) == typeid(*content))
                    return true;
            }
            return false;
        }
    protected:
    private:
        uint64_t _id = -1;
        std::vector<std::shared_ptr<Component>> _Components = {};
};

inline std::ostream &operator<<(std::ostream &os, Entity &entity) {
    std::string name = typeid(entity).name();
    os << "\t"+name+"{ " << std::endl;
    os << "\t\tId: " << entity.getId() << std::endl;
    os << "\t\tComponents { " << std::endl;
    for (auto &Component : entity.getComponents()) {
        std::string output;
        output += Component->toString();
        os << output << std::endl;
    }
    std::cout << "\t\t}" << std::endl;
    os << "\t}" << std::endl;
    return os;
}