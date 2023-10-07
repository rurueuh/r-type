#pragma once

#include "SFML.hpp"
constexpr int PORT = 4242;

class Server
{
public:
	Server();
	~Server() = default;

	void update(void);

private:
	sf::UdpSocket _UDPsocket = sf::UdpSocket();
};
