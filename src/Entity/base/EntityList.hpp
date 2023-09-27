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
            for (u_int64_t i = 0; i < 10000; i++)
                _freeIds.push(i);
        }
        ~EntityList()  = default;

        std::shared_ptr<Entity> &getEntity(u_int64_t id) {
            return _list[id];
        }
        template <typename T>
        std::shared_ptr<Entity> &createEntity() {
            u_int64_t id = _freeIds.front();
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
        std::queue<u_int64_t> _freeIds;
};
