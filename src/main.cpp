#include "SFML.hpp"
#include "World/World.hpp"
#include "Entity.hpp"
#include "TestSystem.hpp"
#include "Component.hpp"

struct PositionComponent {
    PositionComponent(float x, float y) : x(x), y(y) {};
    PositionComponent() : x(0), y(0) {};
	float x, y;
};


int main(void)
{
    sf::RenderWindow window(sf::VideoMode({1600, 900}), "SFML ECS!");
    window.setFramerateLimit(240);
    
    ECS::World* world = ECS::World::CreateWorld();

    ECS::Entity* player = world->CreateEntity();
    ECS::Entity* player2 = world->CreateEntity();
    ECS::Entity* player3 = world->CreateEntity();
    player->assign<PositionComponent>(1000.f, 1000.f);
    player2->assign<PositionComponent>(0.f, 0.f);
    player->assign<PvComponent>(100);
    player2->assign<PvComponent>(1000);
    player->assign<PvComponent>(150); // ignorer

    try {
        world->registerSystem<TestSystem>(0);
    } catch (const std::exception &e) {
        std::cout << "ERROR : " << e.what() << std::endl;
        return 1;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        window.clear();


        auto pos = player->get<PositionComponent>();
        auto pos2 = player2->get<PositionComponent>();

        world->tick();
        window.display();
    }
    world->destroyWorld();
    return 0;
}