/*
** EPITECH PROJECT, 2023
** B-rtype
** File description:
** ComponentList
*/

#pragma once

#include <bits/stdc++.h>
#include "Component.hpp"
#include "Entity.hpp"

class ComponentList {
    public:
        ComponentList() = default;
        ~ComponentList() = default;

        template<typename T>
        std::shared_ptr<T> addComponent(std::shared_ptr<Entity> &entity) noexcept
        {
            std::shared_ptr<T> Component = std::make_shared<T>();
            _Components.push_back(Component);
            entity->addComponent(Component);
            return Component;
        }

    protected:
    private:
        std::vector<std::shared_ptr<Component>> _Components = {};
};
