#include "SFML.hpp"
#include "World/World.hpp"
#include "Entity.hpp"

struct PositionComponent {
    PositionComponent(float x, float y) : x(x), y(y) {};
    PositionComponent() : x(0), y(0) {};
	float x, y;
};

struct PvEComponent {
    PvEComponent(int health) : health(health) {};
    PvEComponent() : health(0) {};
    int health;
};

void my_system(ECS::Entity *e, PositionComponent *p) 
{
    std::cout << e->getId() << std::endl;
}

int main(void)
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML ECS!");
    ECS::World* world = ECS::World::CreateWorld();

    ECS::Entity* player = world->CreateEntity();
    ECS::Entity* player2 = world->CreateEntity();
    ECS::Entity* player3 = world->CreateEntity();
    player->assign<PositionComponent>(1000.f, 1000.f);
    player2->assign<PositionComponent>(0.f, 0.f);
    player->assign<PvEComponent>(100);
    player->assign<PvEComponent>(150); // ignorer

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        window.clear();

        world->each<PositionComponent>([&](ECS::Entity* ent, PositionComponent *position) {
            position->y += 1;
        });

        world->all([](ECS::Entity* ent) {
            std::cout << ent->has<PvEComponent>() << std::endl;
        });

        // std::function<void(ECS::Entity*)> f = my_system;
        world->each<PositionComponent>(my_system);

        auto pos = player->get<PositionComponent>();
        auto pos2 = player2->get<PositionComponent>();
        std::cout << pos->y << std::endl;
        std::cout << pos2->y << std::endl;

        window.display();
    }
    world->destroyWorld();
    return 0;
}