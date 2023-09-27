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

        template<typename T, typename ...Args>
        std::shared_ptr<T> addComponent(std::shared_ptr<Entity> &entity, Args &&...args) noexcept
        {
            std::shared_ptr<T> Component = std::make_shared<T>(std::forward<Args>(args)...);
            _Components.push_back(Component);
            entity->addComponent(Component);
            return Component;
        }

    protected:
    private:
        std::vector<std::shared_ptr<Component>> _Components = {};
};
