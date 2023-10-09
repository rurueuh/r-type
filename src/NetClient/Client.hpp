#pragma once

#include "SFML.hpp"
#include "World/World.hpp"

#ifndef SERVER // CLIENT ONLY
	constexpr int PORT = 4242;
	const sf::IpAddress IP(127, 0, 0, 1);
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

private:
	std::string _clientHash = "";
	sf::UdpSocket _UDPsocket = sf::UdpSocket();
	std::shared_ptr<sf::Thread> _networkInterceptor = nullptr;

	std::vector<ECS::Entity*> _entities;
};
