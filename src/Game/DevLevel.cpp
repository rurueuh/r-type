#include "DevLevel.hpp"
#include "Component.hpp"
#include "TestSystem.hpp"
#include "GameEngine.hpp"

DevLevel::DevLevel() : Level()
{
    std::vector<ECS::Entity*> starship = _world->CreateEntity(4);
    // ECS::Entity* ent = _world->CreateEntity();
    // ent->assign<PvComponent>(100);
    // ent->assign<DrawableComponent>("../assets/player.png", sf::IntRect(1, 3, 32, 14));
    // ent->assign<TransformComponent>(sf::Vector2f(400.f, 400.f), sf::Vector2f(1.f, 1.f), 0.f);
    for (auto ship : starship) {
        ship->assign<PlayerComponent>();
        ship->assign<InputComponent>();
        ship->assign<PvComponent>(100);
        ship->assign<DrawableComponent>("../assets/player.png", sf::IntRect(1, 3, 32, 14));
        ship->assign<VelocityComponent>(0, 0);
        const float x = rand() % 1800;
        const float y = 900.1;
        ship->assign<TransformComponent>(sf::Vector2f(x, y), sf::Vector2f(4.f, 4.f), 0.f);
    }
    #ifndef SERVER
        starship[0]->get<PlayerComponent>()->hash = "me";
    #endif // SERVER

    try {
        _world->registerSystem<TransformSystem>(0);
        _world->registerSystem<DrawableSystem>(1);
        //_world->registerSystem<InputSystem>(2);
        _world->registerSystem<PlayerInputSystem>(3);
        _world->registerSystem<VelocitySystem>(4);
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
