#include "Client.hpp"
#include "GameEngine.hpp"
#include <memory>

#ifndef SERVER // CLIENT ONLY
    Client::Client()
    {
        (void)connect(IP, PORT);
        _UDPsocket.setBlocking(false);
        _networkInterceptor = std::make_shared<sf::Thread>(&Client::update, this);
        _networkInterceptor->launch();
    }

    void Client::send(std::string type, std::string data)
    {
		sf::Packet packet;
        std::string compressedType, compressedData;
        snappy::Compress(type.data(), type.size(), &compressedType);
        snappy::Compress(data.data(), data.size(), &compressedData);
		packet << compressedType << compressedData;
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
            std::string uncompressedType, uncompressedData;
            snappy::Uncompress(type.data(), type.size(), &uncompressedType);
            snappy::Uncompress(data.data(), data.size(), &uncompressedData);
            //std::cout << "RECEIVER | received packet from " << sender << ":" << port << " | DATA : " << type << ": " << data << std::endl;
			return std::make_tuple(uncompressedType, uncompressedData);
		}
        //std::cerr << "error can join server" << std::endl;
		return std::make_tuple("ERROR", "ERROR");
    }

    bool Client::connect(sf::IpAddress ip, unsigned short port)
    {
        send("hello", "client");
        while (1) {
            _UDPsocket.setBlocking(true);
            auto [type, data] = receive();
            _UDPsocket.setBlocking(false);
            if (type != "hello") {
                std::cout << "bad type" << std::endl;
                return false;
            }
            _clientHash = data;
            break;
        }
		std::cout << "client hash: " << _clientHash << std::endl;
	    return true;
    }

    void Client::update(void)
    {
        while (true) {
            // TODO: si le thread time met trop de temps a recuperer les packets par rapport a l'envoie du server alors il met en "queue"
            // et �a deviens problematique car le client met du temps a les recuperer et il ajoute encore plus de packets en "queue"
            // faire un systeme d'horodatage et si il est trop elever alors on drop les packets pour essayer de le resync/deco
			auto [type, data] = receive();
            if (type == "ERROR") {
				sf::sleep(sf::microseconds(5));
				continue;
			}
            if (type == "alive") {
                send("alive", "hey im wake up");
            }
            if (type == "entities") {
				recvEntity(data);
			}
			//sf::sleep(sf::microseconds(5));
            
		}
    }
    static ECS::Entity* CreateEntity(std::string& token)
    {
        size_t id = std::stoi(token.substr(0, token.find(" ")));
        ECS::Entity* newentity = new ECS::Entity(nullptr, id);
        std::string components = "";
        size_t pos = 0;
        if ((pos = token.find("[")) != std::string::npos) {
            components = token.substr(pos + 1, token.find("]") - pos - 1);
            token.erase(pos, token.find("]") - pos + 1);
        }
        std::stringstream ss2(components);
        while (std::getline(ss2, token, ',')) {
            std::stringstream ss3(token);
            std::string componentName;
            std::string componentData;
            std::getline(ss3, componentName, '{');
            std::getline(ss3, componentData, '}');
            ECS::Component::FactoryAssignComponent(newentity, componentName, componentData);
        }
        return newentity;
    }
    void Client::recvEntity(std::string data)
    {
        #ifdef DEBUG
            if (fakeLag)
                sf::sleep(sf::seconds(fakeLagTime));
        #endif
        static int i = 0;
        static sf::Clock clock;
        if (clock.getElapsedTime().asSeconds() > 1) {
			clock.restart();
            std::cout << "entities recv in 1s: " << i << std::endl;
            std::cout << "entities recv: " << data << std::endl;
			i = 0;
		}
        i++;

        _mutex.lock();
        if (this->_isReadySync != false) {
            _mutex.unlock();
			return;
        }
        _mutex.unlock();
        for (auto& ent : this->_entities) {
            delete ent;
        }
        this->_entities.clear();

        // 0 [PvComponent { 100 },PositionComponent { 10 10 }]:1 [PvComponent { 10000 }]:
        // "0"|"[PvComponent { 100 },PositionComponent { 10 10 }]" : premiere etape sep id et components
        // "[PvComponent { 100 }" "PositionComponent { 10 10 }]" : deuxieme etape sep components grace a la virgule
        // "PvComponent { 100 }" "PositionComponent { 10 10 }" : troisieme etape retirer les crochets
        // "PvComponent" "100" "PositionComponent" "10 10" : quatrieme etape sep components grace aux bracket
        // repetition pour chaque entity (separe par ":")
        // 
        // parsing of data
        size_t id = 0;
        std::stringstream ss(data);
        std::string token;
        std::vector<std::string> entitiesToCreate = {};
        DEBUG_CLOCK_CREATE
        while (std::getline(ss, token, ':')) {
            entitiesToCreate.push_back(token);
            ECS::Entity *newentity = CreateEntity(token);
            this->_entities.push_back(newentity);
		}
        DEBUG_CLOCK_PRINT
        _mutex.lock();
        _isReadySync = true;
		_mutex.unlock();
    }
    
    void Client::networkSync(ECS::World* world)
    {
        _mutex.lock();
        if (this->_isReadySync == false) {
            _mutex.unlock();
            return;
        }
        // todo: voir si on peut pas unmutex ici pour pas bloquer le thread (recuperer une frame en avance)
        for (auto& entWorld : world->getEntities()) {
            delete entWorld;
        }
        world->getEntities().clear();
        for (auto& ent : this->_entities) {
            ent->assingWorld(world);
		}
        world->setEntities(this->_entities);
        this->_entities.clear();
        this->_isReadySync = false;
        _mutex.unlock();
    }

    void Client::onInput(ECS::World *world) {
        #ifndef SERVER // CLIENT ONLY
            auto &gameEngine = GameEngine::GetInstance();
            auto window = gameEngine.getWindow();
            if (window->hasFocus() == false) {
                return;
            }
            auto map = Utils::KEYMAP;
            sf::Keyboard::Key key = sf::Keyboard::Unknown;
            for (auto &keyMap : map) {
                if (sf::Keyboard::isKeyPressed(keyMap.first)) {
                    key = keyMap.first;
                }
            }
            this->send("input", std::to_string(key));
            world->each<PlayerComponent>([&](ECS::Entity* ent, PlayerComponent *player) {
                if (player->hash != this->getClientHash()) {
                    return;
                }
                if (ent->has<InputComponent>()) {
                    auto input = ent->get<InputComponent>();
                    if (Utils::KEYMAP.find(key) == Utils::KEYMAP.end()) {
                        return;
                    }
                    input->input = Utils::KEYMAP.at(key);
                }
            });
        #endif
    }
#endif
