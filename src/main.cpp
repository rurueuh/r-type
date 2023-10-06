#include "SFML.hpp"
#include "World/World.hpp"
#include "Entity.hpp"
#include "TestSystem.hpp"
#include "Component.hpp"
#include "LevelManager.hpp"
#include "DevLevel.hpp"

struct PositionComponent {
    PositionComponent(float x, float y) : x(x), y(y) {};
    PositionComponent() : x(0), y(0) {};
	float x, y;
};


int main(void)
{
    sf::RenderWindow window(sf::VideoMode({1600, 900}), "SFML ECS!");
    window.setFramerateLimit(240);
    
    auto &manager = LevelManager::getInstance();
    manager.addLevel<DevLevel>();

    //try {
    //    world->registerSystem<TestSystem>(0);
    //} catch (const std::exception &e) {
    //    std::cout << "ERROR : " << e.what() << std::endl;
    //    return 1;
    //}

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        window.clear();

        manager.update();

        window.display();
    }
    return 0;
}