/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** transformSystem
*/

#pragma once
#include "Component.hpp"
#include "System.hpp"
#include "World.hpp"

namespace ECS::System {
    class TransformSystem : public ECS::BaseSystem {
    public:
        TransformSystem() = default;
        ~TransformSystem() = default;

        virtual void tick(ECS::World* world, const float& dt) override
        {
#ifndef SERVER
            world->each<TransformComponent>(
                [&](ECS::Entity* entity,
                    TransformComponent* transform) {
                        auto drawable = entity->get<DrawableComponent>();
                        if (!drawable)
                            return;
                        drawable->sprite.setPosition(transform->position);
                        drawable->sprite.setScale(transform->scale);
                        drawable->sprite.setRotation(transform->rotation);
                });
#endif
        }

    protected:
    private:
    };
}
