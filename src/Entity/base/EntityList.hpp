/*
** EPITECH PROJECT, 2023
** B-rtype
** File description:
** EntityList
*/

#pragma once

#include <bits/stdc++.h>
#include "Entity.hpp"

class EntityList {
    public:
        EntityList() {
            _list.reserve(10000);
            for (uint64_t i = 0; i < 10000; i++)
                _freeIds.push(i);
        }
        ~EntityList()  = default;

        std::shared_ptr<Entity> &getEntity(uint64_t id) {
            return _list[id];
        }
        template <typename T>
        std::shared_ptr<Entity> &createEntity() {
            uint64_t id = _freeIds.front();
            _freeIds.pop();
            #ifdef DEBUG
                std::cout << "Created entity with id " << id << std::endl;
            #endif
            std::shared_ptr<Entity> newEntity = std::make_shared<T>(id);
            _list[id] = newEntity;
            return _list[id];
        }

    protected:
    private:
        std::vector<std::shared_ptr<Entity>> _list;
        std::queue<uint64_t> _freeIds;
};
