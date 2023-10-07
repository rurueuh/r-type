#pragma once

#include "SFML.hpp"

#ifdef SERVER // SERVER ONLY
	constexpr int PORT = 4242;
	constexpr int PING_TIME_INTERVAL = 10;
	constexpr int PING_TIME_OUT = 20;

	typedef struct client_t {
		sf::IpAddress ip;
		unsigned short port;
		std::string hash;
		sf::Clock timeNoRespond;
		sf::Clock nextPing;
		bool operator==(const client_t& other) const {
			return ip.toInteger() == other.ip.toInteger() && port == other.port;
		}
	} client_t;

	class Server
	{
	public:
		Server();
		~Server() = default;

		void send(std::string type, std::string data, client_t &client);
		std::tuple<bool, std::string, std::string, client_t> receive(void);
		void update(void);
		void onMessage(std::string type, std::string data, client_t &client);
		void sendCheckAlive(void);
		void checkAlive(void);
		client_t &findClient(client_t &client);
	private:
		sf::UdpSocket _UDPsocket = sf::UdpSocket();
		std::shared_ptr<sf::Thread> _networkInterceptor = nullptr;
		std::shared_ptr<sf::Thread> _aliveChecker = nullptr;
		std::vector<client_t> _clients = {};
	};
#endif
