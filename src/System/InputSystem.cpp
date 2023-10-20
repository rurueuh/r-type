#include "InputSystem.hpp"
#include "GameEngine.hpp"

void InputSystem::tick(ECS::World* world, const float& dt)
{
	world->each<InputComponent>(
		[&](ECS::Entity* entity,
			InputComponent* input) {
			auto transform = entity->get<TransformComponent>();
			auto &gameEngine = GameEngine::GetInstance();
			std::string inputStr = input->input;
			#ifdef SERVER
				inputStr = gameEngine.getServer().getInput();
			#endif // SERVER

			if (!transform)
				return;
			if (std::find(inputStr.begin(), inputStr.end(), 'z') != inputStr.end())
				transform->position.y -= 1 * dt * 142;
			if (std::find(inputStr.begin(), inputStr.end(), 's') != inputStr.end())
				transform->position.y += 1 * dt * 142;
			if (std::find(inputStr.begin(), inputStr.end(), 'q') != inputStr.end())
				transform->position.x -= 1 * dt * 142;
			if (std::find(inputStr.begin(), inputStr.end(), 'd') != inputStr.end())
				transform->position.x += 1 * dt * 142;
		});
}
