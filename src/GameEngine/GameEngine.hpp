#pragma once

#include "Level.hpp"
#include "LevelManager.hpp"
#include "Server.hpp"
#include "Client.hpp"

class GameEngine
{
public:
	static GameEngine& GetInstance() {
		static GameEngine instance;
		return instance;
	}

	template<typename T>
	void Init(void) {
		#ifndef SERVER // CLIENT ONLY
			_window = new sf::RenderWindow(sf::VideoMode({1600, 900}), "SFML ECS!");
			//_window->setFramerateLimit(240);
		#endif
		_isRunning = true;
		LevelManager::getInstance().addLevel<T>();
	}
	void Run(void);
	void Shutdown(void);

	#ifdef SERVER // SERVER ONLY
		Server &getServer(void) { return _server; }
	#else // CLIENT ONLY
		Client &getClient(void) { return _client; }
	#endif
		
private:
	GameEngine();
	~GameEngine() = default;

	void replicateEntities(void);

	sf::RenderWindow *_window = nullptr;
	bool _isRunning = false;
	#ifdef SERVER // SERVER ONLY
		Server _server;
	#else // CLIENT ONLY
		Client _client;
	#endif

};
