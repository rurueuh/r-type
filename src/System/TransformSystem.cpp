/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** TransformSystem
*/

#include "TransformSystem.hpp"

void TransformSystem::tick(ECS::World *world, const float &dt)
{
    world->each<DrawableComponent, TransformComponent>(
        [&](ECS::Entity *entity,
            DrawableComponent *drawable,
            TransformComponent *transform) {
            drawable->sprite.setPosition(transform->position);
            drawable->sprite.setScale(transform->scale);
            drawable->sprite.setRotation(transform->rotation);
        });
}