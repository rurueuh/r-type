#include "DevLevel.hpp"
#include "Component.hpp"
#include "TestSystem.hpp"
#include "GameEngine.hpp"

DevLevel::DevLevel() : Level()
{
    ECS::Entity* player = _world->CreateEntity();
    ECS::Entity *player2 = _world->CreateEntity();

    player->assign<PvComponent>(100);
    player->assign<PlayerInputComponent>("");
    player2->assign<PvComponent>(10000);
    player->assign<DrawableComponent>("../assets/player.png", sf::IntRect(1, 3, 32, 14));
    player->assign<TransformComponent>(sf::Vector2f(100.f, 100.f), sf::Vector2f(1.f, 1.f), 0.f);
    try {
        _world->registerSystem<DrawableSystem>(1);
        _world->registerSystem<TransformSystem>(0);
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
	}
}
