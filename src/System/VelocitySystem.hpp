/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** PlayerInputSystem
*/

#pragma once

#include "System.hpp"
#include "Component.hpp"
#include "World.hpp"

namespace ECS::System {

    class VelocitySystem : public ECS::BaseSystem {
    public:
        VelocitySystem() = default;
        ~VelocitySystem() = default;

        virtual void tick(ECS::World* world, const float& dt) {
            world->each<VelocityComponent>(
                [&](ECS::Entity* entity,
                    VelocityComponent* velocity) {
                        auto transform = entity->get<TransformComponent>();

                        if (!transform)
                            return;
                        transform->position.x += velocity->velocity.x * dt;
                        transform->position.y += velocity->velocity.y * dt;

                        // remove 0.1f (static value) to each velocity (0.1f is the friction)
                        constexpr float frictionFix = 0.5f;
                        if (velocity->velocity.x < frictionFix && velocity->velocity.x > -frictionFix)
                            velocity->velocity.x = 0;
                        else 
                            velocity->velocity.x -= velocity->velocity.x * frictionFix * dt;
                        if (velocity->velocity.y < frictionFix && velocity->velocity.y > -frictionFix)
                            velocity->velocity.y = 0;
                        else
                            velocity->velocity.y -= velocity->velocity.y * 0.1f * dt;
                        // std::cout << velocity->velocity.x << " " << velocity->velocity.y << std::endl;
                });
        }

    protected:
    private:
    };
}
