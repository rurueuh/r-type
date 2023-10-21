#include "InputSystem.hpp"
#include "GameEngine.hpp"

void InputSystem::tick(ECS::World* world, const float& dt)
{
	world->each<InputComponent>(
		[&](ECS::Entity* entity,
			InputComponent* input) {
			auto transform = entity->get<TransformComponent>();
			auto &gameEngine = GameEngine::GetInstance();
			auto &inputStr = input->input;
			#ifdef SERVER
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
			if (std::find(inputStr.begin(), inputStr.end(), ' ') != inputStr.end()) {
				auto world = entity->getWorld();
				auto bullet = world->CreateEntity();
				bullet->assign<DrawableComponent>("../assets/bullet.png", sf::IntRect(1, 3, 32, 14));
				bullet->assign<TransformComponent>(transform->position, sf::Vector2f(1.f, 1.f), 0.f);
				inputStr = "";
			}
		});
}
