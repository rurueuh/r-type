#include "DeadLevel.hpp"

DeadLevel::DeadLevel()
{
	auto player = _world->CreateEntity();
    player->assign<DrawableComponent>("../assets/player.png");
    player->assign<TransformComponent>(sf::Vector2f(200, 200), sf::Vector2f(1, 1), 0);

    auto text = _world->CreateEntity();
    text->assign<TextComponent>("You died");
    text->assign<TransformComponent>(sf::Vector2f(1600/2 - 40, 800/4), sf::Vector2f(1, 1), 0);
    text->assign<VelocityComponent>(30.f, 30.f);



    try {
        _world->registerSystem<ECS::System::TextSystem>(0);
        _world->registerSystem<ECS::System::DrawableSystem>(1);
        _world->registerSystem<ECS::System::TransformSystem>(2);
        _world->registerSystem<ECS::System::InputSystem>(3);
        _world->registerSystem<ECS::System::VelocitySystem>(4);
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
