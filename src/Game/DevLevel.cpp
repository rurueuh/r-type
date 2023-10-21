#include "DevLevel.hpp"
#include "Component.hpp"
#include "TestSystem.hpp"
#include "GameEngine.hpp"

DevLevel::DevLevel() : Level()
{
    std::vector<ECS::Entity*> players = _world->CreateEntity(400);

    for (auto player : players) {
        player->assign<PvComponent>(100);
        player->assign<DrawableComponent>("../assets/player.png", sf::IntRect(1, 3, 32, 14));
        player->assign<TransformComponent>(sf::Vector2f(100.f, 100.f), sf::Vector2f(1.f, 1.f), 0.f);
        player->assign<InputComponent>();
    }
    try {
        _world->registerSystem<TransformSystem>(0);
        _world->registerSystem<DrawableSystem>(1);
        _world->registerSystem<InputSystem>(2);
    } catch (const std::exception &e) {
        std::cout << "ERROR : " << e.what() << std::endl;
    }
}

DevLevel::~DevLevel()
{
}

void DevLevel::update(const float dt)
{
    static sf::Clock clock;
    if (clock.getElapsedTime().asSeconds() > 0.01) {
		clock.restart();
        _world->each<PvComponent>([&](ECS::Entity* ent, PvComponent* pv) {
            pv->health += 1;
		});
        _world->each<TransformComponent>([&](ECS::Entity* ent, TransformComponent* transform) {
            //transform->position.x += 1;
            if (transform->position.x > 1800) {
				transform->position.x = 0;
			}
        });
	}
}
