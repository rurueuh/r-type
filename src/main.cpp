#include "SFML.hpp"
#include "World/World.hpp"
#include "Entity.hpp"
#include "TestSystem.hpp"
#include "Component.hpp"
#include "LevelManager.hpp"
#include "DevLevel.hpp"

struct PositionComponent
{
    PositionComponent(float x, float y) : x(x), y(y){};
    PositionComponent() : x(0), y(0){};
    float x, y;
};

std::string compress_str(std::string str)
{
    int j = 0;
    std::string result;
    for (int i = 0; i < str.length(); i++) {

        int count = 0;
        while (i < str.length() - 1 && str[i] == str[i + 1]) {
            count++;
            i++;
        }

        if (count > 0) {
            result += str[i];
            result += std::to_string(count + 1);
        } else {
            result += str[i];
        }
    }
    return result;
}

std::string decompressString(std::string str) {
    std::string result;
    for (int i = 0; i < str.length(); i++) {
        if (isdigit(str[i])) {
            int count = str[i] - '0';
            while (count > 0) {
                result += str[i - 1];
                count--;
            }
        } else {
            result += str[i];
        }
    }
    return result;
}

int main(void)
{
    sf::RenderWindow window(sf::VideoMode({1600, 900}), "SFML ECS!");
    window.setFramerateLimit(240);

    auto &manager = LevelManager::getInstance();
    manager.addLevel<DevLevel>();

    std::string original = "0 [PositionComponent { 10 10 },PvComponent { 100 }]:1 [PvComponent { 10000 }]";
    std::string compressed = compress_str(original);
    std::cout << "original : " << original << std::endl;

    // try {
    //     world->registerSystem<TestSystem>(0);
    // } catch (const std::exception &e) {
    //     std::cout << "ERROR : " << e.what() << std::endl;
    //     return 1;
    // }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        manager.update();

        window.display();
    }
    return 0;
}