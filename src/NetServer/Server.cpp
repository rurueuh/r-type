#include "Server.hpp"

Server::Server()
{
	if (_UDPsocket.bind(PORT) != sf::Socket::Status::Done) {
		throw std::runtime_error("error bind server on port " + PORT);
	}
	std::cout << "listening on : " << _UDPsocket.getLocalPort() << std::endl;
}

void Server::update(void)
{
}
