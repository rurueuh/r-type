#include "DeadLevel.hpp"

DeadLevel::DeadLevel()
{
	auto player = _world->CreateEntity();
    player->assign<DrawableComponent>("../assets/player.png");
    player->assign<TransformComponent>(sf::Vector2f(200, 200), sf::Vector2f(1, 1), 0);

    try {
        _world->registerSystem<ECS::System::DrawableSystem>(0);
    } catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}

DeadLevel::~DeadLevel()
{
}

void DeadLevel::update(const float dt)
{
}
