#pragma once

#include "SFML.hpp"

#ifndef SERVER // CLIENT ONLY
	constexpr int PORT = 4242;
	const sf::IpAddress IP = sf::IpAddress::IpAddress(127, 0, 0, 1);
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

private:
	std::string _clientHash = "";
	sf::UdpSocket _UDPsocket = sf::UdpSocket();
	std::shared_ptr<sf::Thread> _networkInterceptor = nullptr;
};
