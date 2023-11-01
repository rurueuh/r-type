#pragma once

#include "SFML.hpp"
#include "World/World.hpp"
#include "Component.hpp"
#include "snappy.h"

#ifndef SERVER // CLIENT ONLY
	constexpr int PORT = 4242;
	const sf::IpAddress IP(127, 0, 0, 1);
	constexpr bool fakeLag = false;
	constexpr float fakeLagTime = 0.2f;
#endif

class Client
{
public:
	Client();
	~Client() {
		if (_networkInterceptor != nullptr) {
			_networkInterceptor->terminate();
		}
		if (_threadGarbage != nullptr) {
			_threadGarbage->terminate();
		}
	}

	void send(std::string type, std::string data);
	std::tuple<std::string, std::string> receive(void);
	bool connect(sf::IpAddress ip, unsigned short port);
	void threadConnect(void);
	void update(void);
	void recvEntity(std::string data);
	void recvLevel(std::string data);

	void networkSync(ECS::World *world);
	void onInput(ECS::World *world);
	void setWorld(ECS::World* world) { _world = world; };

	std::string getClientHash(void) { return _clientHash; };

	void clearGarbage(void) {
		while (1) {
			_mutexGarbage.lock();
			for (auto& entity : _entitiesGarbage) {
				delete entity;
			}
			_entitiesGarbage.clear();
			_mutexGarbage.unlock();
		}
	}

private:
	std::string _clientHash = "me";
	sf::UdpSocket _UDPsocket = sf::UdpSocket();
	std::shared_ptr<sf::Thread> _networkInterceptor = nullptr;
	std::shared_ptr<sf::Thread> _threadGarbage = std::make_shared<sf::Thread>(&Client::clearGarbage, this);
	bool _isReadySync = false;
	sf::Mutex _mutex = sf::Mutex();
	sf::Mutex _mutexGarbage = sf::Mutex();

	std::string currentLevelServer = "";

	std::vector<ECS::Entity*> _entities;
	std::vector<ECS::Entity*> _entitiesGarbage;
	ECS::World *_world = nullptr;
};
