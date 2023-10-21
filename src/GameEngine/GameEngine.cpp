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

        // find PlayerInputComponent {  }
        // and change to PlayerInputComponent { ${string} }
        auto entities = world->getEntities();

        sf::Packet packet;
        packet << "entities";
        std::string entitiesString = "";

        for (auto& entity : entities) { // todo: optimise / thread him
            std::string serialize = entity->serialise();
            entitiesString += serialize + ":";
	    }
        size_t pos = 0;
        while ((pos = entitiesString.find(",}", pos)) != std::string::npos) {
		    entitiesString.replace(pos, 2, "}");
	    }
        std::string string = _server.getInput();

        pos = 0;
        while ((pos = entitiesString.find("PlayerInputComponent", pos)) != std::string::npos) {
			entitiesString.replace(pos + 20, 5, "{ " + string + " }");
			pos += 1;
		}

        packet << entitiesString;
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
                if (event.type == sf::Event::KeyPressed) {
					_client.onInput(event.key.code);
                }
            }
            _window->clear();
        #endif

        manager.update();
        this->replicateEntities();

        #ifndef SERVER // CLIENT ONLY
            _window->display();
        #endif
        const auto TIMESLEEP = sf::milliseconds(10);
        sf::sleep(TIMESLEEP);
    }
}

void GameEngine::Shutdown(void)
{
    this->_isRunning = false;
    #ifndef SERVER // CLIENT ONLY
	    _window->close();
    #endif
}

