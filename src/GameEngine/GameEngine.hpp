#pragma once

#include "Level.hpp"
#include "LevelManager.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include <chrono>
#include <thread>

// todo: refactor this
void setLevel(const std::string& str);

class GameEngine
{
public:
	static GameEngine& GetInstance() {
		try {
			static GameEngine instance;
			return instance;
		} catch (const std::exception &e) {
			std::cerr << e.what() << std::endl;
			exit(84);
		}
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
	sf::RenderWindow *getWindow(void) { return _window; }
	void printFPS(void) {
		static sf::Clock clock;
		static int frame = 0;
		static float time = 0;
		frame++;
		time += clock.restart().asSeconds();
		if (time >= 1) {
			std::cout << "FPS: " << frame << std::endl;
			frame = 0;
			time = 0;
		}
	}

	#ifdef SERVER // SERVER ONLY
		Server &getServer(void) { return _server; }
	#else // CLIENT ONLY
		Client &getClient(void) { return *_client; }
		sf::Font &getFont(void) { return _font; }
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
		std::shared_ptr<Client> _client = std::make_shared<Client>();
		sf::Font _font;
	#endif

};
