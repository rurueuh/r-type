/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** TransformSystem
*/

#include "TransformSystem.hpp"

void TransformSystem::tick(ECS::World *world, const float &dt)
{
    #ifndef SERVER
        world->each<TransformComponent>(
            [&](ECS::Entity *entity,
                TransformComponent *transform) {
                auto drawable = entity->get<DrawableComponent>();
                if (!drawable)
                    return;
                drawable->sprite.setPosition(transform->position);
                drawable->sprite.setScale(transform->scale);
                drawable->sprite.setRotation(transform->rotation);
            });
    #endif
}