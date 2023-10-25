#include "GameEngine.hpp"
#include "snappy.h"
#include <algorithm>

GameEngine::GameEngine()
{
    srand(time(NULL));
}

void thread_serialize(std::vector<ECS::Entity*> &entities, int start, int stop, std::string& result)
{
    std::string tmp = "";
    if (stop > entities.size()) {
        return;
    };
    for (int i = start; i < stop; i++) {
        result += entities[i]->serialise() + ":";
    }
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
        std::vector<std::string> entitiesString;
        std::ostringstream entitiesStream;

        auto maxThread = std::thread::hardware_concurrency();
        std::vector<std::shared_ptr<sf::Thread>> listThread;
        int entitiesPerThread = std::max((unsigned int)entities.size() / maxThread, (unsigned int)1);
        int remainingEntities = entities.size() % maxThread;
        for (unsigned int i = 0; i < maxThread; i++) {
            entitiesString.push_back(std::string());
        }

        for (unsigned int i = 0; i < maxThread; i++) {
            int start = i * entitiesPerThread;
            int stop = (i + 1) * entitiesPerThread;
            std::shared_ptr<sf::Thread> thread = std::make_shared<sf::Thread>(std::bind(&thread_serialize, entities, start, stop, std::ref(entitiesString[i])));
            listThread.push_back(thread);
            thread->launch();
        }

        for (auto &thread : listThread) {
            thread->wait();
        }

        for (auto &str : entitiesString) {
            entitiesStream << str;
        }

        std::string result = entitiesStream.str();
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
    auto &manager = LevelManager::getInstance();
    auto &level = manager.getCurrentLevel();
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

