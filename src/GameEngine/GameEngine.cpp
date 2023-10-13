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
    std::string entitiesString = "";

    for (auto& entity : entities) {
        std::string serialize = entity->serialise();
        entitiesString += serialize + ":";
	}
    size_t pos = 0;
    while ((pos = entitiesString.find(",}", pos)) != std::string::npos) {
		entitiesString.replace(pos, 2, "}");
	}
    packet << entitiesString;

    #ifdef SERVER // SERVER ONLY
        // is safe ?
        _server.sendToAll(packet);
	#else // CLIENT ONLY
        _client.networkSync(world);
        // TODO: send to server (client)
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
        const auto TIMESLEEP = std::chrono::nanoseconds(1000);
        std::this_thread::sleep_for(TIMESLEEP);
    }
}

void GameEngine::Shutdown(void)
{
    this->_isRunning = false;
    #ifndef SERVER // CLIENT ONLY
	    _window->close();
    #endif
}

