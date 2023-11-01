#include "DeadLevel.hpp"

DeadLevel::DeadLevel()
{
	auto player = _world->CreateEntity();
    player->assign<DrawableComponent>("../assets/player.png");
    player->assign<TransformComponent>(sf::Vector2f(200.f, 200.f), sf::Vector2f(1.f, 1.f), 0.f);

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
