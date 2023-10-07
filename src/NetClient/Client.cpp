#include "Client.hpp"

#ifndef SERVER // CLIENT ONLY
    Client::Client()
    {
        (void)connect(IP, PORT);
        _networkInterceptor = std::make_shared<sf::Thread>(&Client::update, this);
        _networkInterceptor->launch();
    }

    void Client::send(std::string type, std::string data)
    {
		sf::Packet packet;
		packet << type << data;
        if (_UDPsocket.send(packet, IP, PORT) != sf::Socket::Status::Done) {
			throw std::runtime_error("error can join server");
		}
        #ifdef DEBUG
		    std::cout << "SENDER | message sent to " << IP << ":" << PORT << " | DATA : " << type << ": " << data << std::endl;
        #endif
    }

    std::tuple<std::string, std::string> Client::receive(void)
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
			return std::make_tuple(type, data);
		}
        std::cerr << "error can join server" << std::endl;
		return std::make_tuple("ERROR", "ERROR");
    }

    bool Client::connect(sf::IpAddress ip, unsigned short port)
    {
        send("hello", "client");
        auto [type, data] = receive();
        if (type != "hello" || data != "server") {
			std::cerr << "error can join server" << std::endl;
			return false;
		}
	    return true;
    }

    void Client::update(void)
    {
        while (true) {
			auto [type, data] = receive();
            if (type == "ERROR") {
				sf::sleep(sf::microseconds(500));
				continue;
			}
            if (type == "alive") {
                send("alive", "hey im wake up");
            }
			sf::sleep(sf::microseconds(500));
		}
    }
#endif
