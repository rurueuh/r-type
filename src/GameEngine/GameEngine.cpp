#include "GameEngine.hpp"

GameEngine::GameEngine()
{
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

        #ifndef SERVER // CLIENT ONLY
            _window->display();
        #else // SERVER ONLY
            std::this_thread::sleep_for(std::chrono::milliseconds(4));
        #endif
    }
}

void GameEngine::Shutdown(void)
{
    this->_isRunning = false;
    #ifndef SERVER // CLIENT ONLY
	    _window->close();
    #endif
}

