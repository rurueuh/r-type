#include "InputSystem.hpp"
#include "GameEngine.hpp"

void InputSystem::tick(ECS::World* world, const float& dt)
{
	world->each<InputComponent>(
        [&](ECS::Entity *entity,
            InputComponent *input) {
            auto inputKey = input->getKeyPressed();

            for (auto &f : input->functionInput) {
                if (inputKey == f.first)
                    f.second(entity, dt);
            }
            input->input = "";
        });
}
