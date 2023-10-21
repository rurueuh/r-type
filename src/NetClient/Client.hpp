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
	~Client() = default;

	void send(std::string type, std::string data);
	std::tuple<std::string, std::string> receive(void);
	bool connect(sf::IpAddress ip, unsigned short port);
	void update(void);
	void recvEntity(std::string data);

	void networkSync(ECS::World *world);
	void onInput(sf::Keyboard::Key key, ECS::World *world);
	void setWorld(ECS::World* world) { _world = world; };

	std::string getClientHash(void) { return _clientHash; };

private:
	std::string _clientHash = "me";
	sf::UdpSocket _UDPsocket = sf::UdpSocket();
	std::shared_ptr<sf::Thread> _networkInterceptor = nullptr;
	sf::Mutex _mutex = sf::Mutex();

	std::vector<ECS::Entity*> _entities;
	ECS::World *_world = nullptr;
};
