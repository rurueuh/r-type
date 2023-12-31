#pragma once

#include "SFML.hpp"
#include <memory>
#include "snappy.h"
#include "World.hpp"
#include "Component.hpp"

#ifdef SERVER // SERVER ONLY
	constexpr int PORT = 4242;
	const sf::IpAddress IP = sf::IpAddress::IpAddress::Any;
	constexpr int PING_TIME_INTERVAL = 5;
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
		bool operator!=(const client_t& other) const {
			return !(*this == other);
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
		void checkInput(std::string data, client_t &client);
		client_t &findClient(client_t &client);

		void sendToAll(sf::Packet &packet);
		void sendToAll(std::string type, std::string data);

		void syncClientWithWorld(ECS::World *world);
		void syncClientInput(ECS::World *world);
		void disconnectClient();

		std::unordered_map<std::string, std::string> &getInput(void) { return _input; };
	private:
		sf::UdpSocket _UDPsocket = sf::UdpSocket();
		std::shared_ptr<sf::Thread> _networkInterceptor = nullptr;
		std::shared_ptr<sf::Thread> _aliveChecker = nullptr;
		std::vector<client_t> _clients = {};
		std::unordered_map<std::string, std::string> _input = std::unordered_map<std::string, std::string>();
	};
#endif
