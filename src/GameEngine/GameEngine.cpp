#include "GameEngine.hpp"

GameEngine::GameEngine()
{
}

void GameEngine::replicateEntities(void)
{
    auto& manager = LevelManager::getInstance();
    auto level = manager.getCurrentLevel();
    auto world = level->getWorld();
    auto entities = world->getEntities();

    sf::Packet packet;
    packet << "entities";
    auto data = entities.data();
    // reconstruct entities from data

    world->all([&](ECS::Entity &entity) {
        // TODO: serialize entity
    });
    #ifdef SERVER // SERVER ONLY
        _server.sendToAll(packet);
	#else // CLIENT ONLY

    #endif
}

void GameEngine::Run(void)
{
    auto &manager = LevelManager::getInstance();
    while (this->_isRunning)
    {
        #ifndef SERVER // CLIENT ONLY
            sf::Event event;
            while (_window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    this->Shutdown();
                }
            }
            _window->clear();
        #endif

        manager.update();
        this->replicateEntities();

        #ifndef SERVER // CLIENT ONLY
            _window->display();
        #endif
        std::this_thread::sleep_for(std::chrono::milliseconds(4));
    }
}

void GameEngine::Shutdown(void)
{
    this->_isRunning = false;
    #ifndef SERVER // CLIENT ONLY
	    _window->close();
    #endif
}

