#include "GameEngine.hpp"
#include "snappy.h"

GameEngine::GameEngine()
{
    srand(time(NULL));
}

void GameEngine::replicateEntities(void)
{
    auto& manager = LevelManager::getInstance();
    auto level = manager.getCurrentLevel();
    auto world = level->getWorld();


#ifdef SERVER // SERVER ONLY
    // is safe ?

    _server.syncClientWithWorld(world);
    _server.syncClientInput(world);
    auto entities = world->getEntities();


    sf::Packet packet;
    packet << "entities";
    std::ostringstream entitiesString;

    for (const auto& entity : entities) {
        entitiesString << entity->serialise() << ":";
    }

    std::string result = entitiesString.str();
    size_t pos = result.find(",}");
    while (pos != std::string::npos) {
        result.replace(pos, 2, "}");
        pos = result.find(",}", pos + 1);
    }

    packet << result;
    _server.sendToAll(packet);

#else // CLIENT ONLY
    _client.networkSync(world);
    // TODO: send to server (client)
#endif
}

void GameEngine::Run(void)
{
    auto& manager = LevelManager::getInstance();
    auto& level = manager.getCurrentLevel();
    auto world = level->getWorld();
    while (this->_isRunning)
    {
#ifndef SERVER // CLIENT ONLY
        sf::Event event;
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this->Shutdown();
            }
            if (event.type == sf::Event::KeyPressed) {
            }
        }
        _client.onInput(world);
        _window->clear();
#endif

        manager.update();
        this->replicateEntities();

#ifndef SERVER // CLIENT ONLY
        _window->display();
#endif
        static sf::Clock clockFrame;
        float deltaTime = clockFrame.restart().asSeconds();
        const auto TIMESLEEP = sf::milliseconds(10);
        if (deltaTime < 0.1) {
            auto time = TIMESLEEP - sf::seconds(deltaTime);
            if (time.asMicroseconds() > 0)
                sf::sleep(TIMESLEEP - sf::seconds(deltaTime));
        }
        else {
            sf::sleep(TIMESLEEP);
        }
        printFPS();
    }
}

void GameEngine::Shutdown(void)
{
    this->_isRunning = false;
#ifndef SERVER // CLIENT ONLY
    _window->close();
#endif
}