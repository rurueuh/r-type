#include "InputSystem.hpp"
#include "GameEngine.hpp"

void InputSystem::tick(ECS::World* world, const float& dt)
{
	world->each<InputComponent>(
        [&](ECS::Entity *entity,
            InputComponent *input) {
            auto transform = entity->get<TransformComponent>();
            auto velocity = entity->get<VelocityComponent>();
            auto inputKey = input->getKeyPressed();

            if (!velocity || !transform)
                return;
            if (inputKey == Input::Key::forward)
                velocity->velocity.y -= 1 * dt * 142;
            if (inputKey == Input::Key::backward)
                velocity->velocity.y += 1 * dt * 142;
            if (inputKey == Input::Key::left)
                velocity->velocity.x -= 1 * dt * 142;
            if (inputKey == Input::Key::right)
                velocity->velocity.x += 1 * dt * 142;
            if (inputKey == Input::Key::jump) {
                auto world = entity->getWorld();
                auto bullet = world->CreateEntity();
                bullet->assign<DrawableComponent>("../assets/player.png", sf::IntRect(1, 3, 32, 14));
                bullet->assign<TransformComponent>(transform->position, sf::Vector2f(1.f, 1.f), 0.f);
                bullet->assign<VelocityComponent>(620, 0);
            }
        });
}
