/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** PlayerInputSystem
*/

#include "PlayerInputSystem.hpp"
#include "World.hpp"
#include "GameEngine.hpp"

PlayerInputSystem::PlayerInputSystem()
{
}

PlayerInputSystem::~PlayerInputSystem()
{
}

void PlayerInputSystem::tick(ECS::World *world, const float &dt)
{
    world->each<InputComponent>(
        [&](ECS::Entity *entity,
            InputComponent *input) {
            auto transform = entity->get<TransformComponent>();
            auto velocity = entity->get<VelocityComponent>();
            auto &inputStr = input->input;

            if (!velocity || !transform)
                return;
            if (std::find(inputStr.begin(), inputStr.end(), 'z') != inputStr.end())
                velocity->velocity.y -= 1 * dt * 142;
            if (std::find(inputStr.begin(), inputStr.end(), 's') != inputStr.end())
                velocity->velocity.y += 1 * dt * 142;
            if (std::find(inputStr.begin(), inputStr.end(), 'q') != inputStr.end())
                velocity->velocity.x -= 1 * dt * 142;
            if (std::find(inputStr.begin(), inputStr.end(), 'd') != inputStr.end())
                velocity->velocity.x += 1 * dt * 142;
            if (std::find(inputStr.begin(), inputStr.end(), ' ') != inputStr.end()) {
                auto world = entity->getWorld();
                auto bullet = world->CreateEntity();
                bullet->assign<DrawableComponent>("../assets/player.png", sf::IntRect(1, 3, 32, 14));
                bullet->assign<TransformComponent>(transform->position, sf::Vector2f(1.f, 1.f), 0.f);
                bullet->assign<VelocityComponent>(620, 0);
            }
            inputStr = "";
        });
}