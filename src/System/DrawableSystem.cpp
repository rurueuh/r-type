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
        auto sprite = drawable->sprite;
        window->draw(sprite);
    });
    #endif
}