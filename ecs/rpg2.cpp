#include <SFML/Graphics.hpp>
#include "LevelManager.h"
#include "Menu.h"
#include "Game.h"
#include "rpg2.h"

std::shared_ptr<sf::RenderWindow> createWindow()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
    settings.majorVersion = 4;
    settings.minorVersion = 6;
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "RPG", sf::Style::Default, settings);
    window->setFramerateLimit(250);
	return window;
}

int main(void)
{
    auto window = createWindow();

    LevelManager &levelManager = LevelManager::getInstance();
    levelManager.addLevel<Menu>();

    while (window->isOpen())
    {
        Event(window);
        Update(levelManager);
        draw(window, levelManager);
    }

    TextureManager::clear();
    return 0;
}

void Update(LevelManager& levelManager)
{
    static sf::Clock clock;
    float dt = 0.0f;
    dt = clock.restart().asSeconds();
    levelManager.update(dt);
}

void draw(std::shared_ptr<sf::RenderWindow>& window, LevelManager& levelManager)
{
    window->clear();
    levelManager.draw((sf::RenderTarget &)*window);
    window->display();
}

void Event(std::shared_ptr<sf::RenderWindow>& window)
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                window->close();
        }
    }
}
