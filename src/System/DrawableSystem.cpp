/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** DrawableSystem
*/

#include "DrawableSystem.hpp"
#include "GameEngine.hpp"

void DrawableSystem::tick(ECS::World *world, const float &dt)
{
    #ifndef SERVER
        auto window = GameEngine::GetInstance().getWindow();

        world->each<DrawableComponent>([&](ECS::Entity *entity, DrawableComponent *drawable) {
            auto transform = entity->get<TransformComponent>();
            if (!transform)
				return;
            // todo: move this to a system
            drawable->sprite.setPosition(transform->position);
            drawable->sprite.setScale(transform->scale);
            drawable->sprite.setRotation(transform->rotation);
            auto &sprite = drawable->sprite;
            window->draw(sprite);
        });
    #endif
}