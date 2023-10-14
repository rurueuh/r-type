#include "Server.hpp"

#ifdef SERVER // SERVER ONLY
	Server::Server()
	{
		if (_UDPsocket.bind(PORT) != sf::Socket::Status::Done) {
			throw std::runtime_error("error bind server on port " + PORT);
		}
		std::cout << "listening on : " << _UDPsocket.getLocalPort() << std::endl;
		_UDPsocket.setBlocking(false);
		_networkInterceptor = std::make_shared<sf::Thread>(&Server::update, this);
		_networkInterceptor->launch();
	}

	void Server::send(std::string type, std::string data, client_t& client)
	{
		sf::Packet packet;
		packet << type << data;
		if (_UDPsocket.send(packet, client.ip, client.port) != sf::Socket::Status::Done) {
			throw std::runtime_error("error can join server");
		}
		#ifdef DEBUG
			std::string str = "SENDER | message sent to " + client.ip.toString() + ":" + std::to_string(client.port) + " | DATA : " + type + ": " + data + "\n";
		#endif
	}

	std::tuple<bool, std::string, std::string, client_t> Server::receive(void)
	{
		sf::Packet packet; // TypeString + data
		sf::IpAddress sender;
		unsigned short port;
		auto status = _UDPsocket.receive(packet, sender, port);
		if (status == sf::Socket::Status::Done) {
			std::string type;
			std::string data;
			packet >> type >> data;
			std::cout << "RECEIVER | received packet from " << sender << ":" << port << " | DATA : " << type << ": " << data << std::endl;
			return std::make_tuple(true, type, data, client_t{sender, port, ""});
		}
		return std::make_tuple(false, "ERROR", "ERROR", client_t{sender, port, ""});
	}

	void Server::update(void)
	{
		while (true) {
			checkAlive();
			auto [rcv, type, data, client] = receive();
			if (!rcv) {
				sendCheckAlive();
				sf::sleep(sf::microseconds(5));
				continue;
			}
			if (type != "hello" && std::find(_clients.begin(), _clients.end(), client) == _clients.end())
				continue; // not a client
			this->onMessage(type, data, client);
			sf::sleep(sf::microseconds(5));
		}
	}

	void Server::onMessage(std::string type, std::string data, client_t& client)
	{
		auto &clientRef = findClient(client);
		if (type == "hello") {
			this->_clients.push_back(client);
			// generate a string of 32 char randomly
			std::string hash = "";
			for (int i = 0; i < 32; i++) {
				hash += std::to_string(rand() % 10);
			}
			clientRef.hash = hash;
			std::cout << "SERVER | new client " << client.ip << ":" << client.port << " | hash : " << hash << std::endl;
			send("hello", hash, client);
		}
		else if (type == "alive") {
			clientRef.timeNoRespond.restart().asSeconds();
		}
		else if (type == "input") {
			std::cout << "SERVER | received Input | DATA : " << type << ": " << data << std::endl;
		} else {
			std::cout << "SERVER | received packet | DATA : " << type << ": " << data << std::endl;
		}
	}
	void Server::sendCheckAlive(void)
	{
		for (auto it = _clients.begin(); it != _clients.end(); it++) {
			if (it->nextPing.getElapsedTime().asSeconds() < PING_TIME_INTERVAL) {
				continue;
			}
			send("alive", "hey wake up", *it);
			it->nextPing.restart();
		}
	}
	void Server::checkAlive(void)
	{
		for (int i = 0; i < _clients.size(); i++) {
			if (_clients[i].timeNoRespond.getElapsedTime().asSeconds() > PING_TIME_OUT) {
				std::cout << "client " << _clients[i].ip << ":" << _clients[i].port << " is dead" << std::endl;
				_clients.erase(_clients.begin() + i);
				return;
			}
		}
	}
	client_t& Server::findClient(client_t& client)
	{
		for (auto it = _clients.begin(); it != _clients.end(); it++) {
			if (*it == client) {
				return *it;
			}
		}
		return client;
	}
	void Server::sendToAll(sf::Packet& packet)
	{
		for (auto it = _clients.begin(); it != _clients.end(); it++) {
			if (_UDPsocket.send(packet, it->ip, it->port) != sf::Socket::Status::Done) {
				throw std::runtime_error("error can join server");
			}
		}
	}
	void Server::sendToAll(std::string type, std::string data)
	{
		for (auto it = _clients.begin(); it != _clients.end(); it++) {
			send(type, data, *it);
		}
	}
#endif
