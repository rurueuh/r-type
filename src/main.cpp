#include "SFML.hpp"
#include "World/World.hpp"
#include "Entity.hpp"
#include "TestSystem.hpp"
#include "Component.hpp"
#include "LevelManager.hpp"
#include "DevLevel.hpp"
#include "GameEngine.hpp"

struct PositionComponent {
    PositionComponent(float x, float y) : x(x), y(y) {};
    PositionComponent() : x(0), y(0) {};
	float x, y;
};

void setupServer(unsigned short port)
{
    sf::UdpSocket socket;
    if (socket.bind(port) != sf::Socket::Status::Done) {
        throw std::runtime_error("error bind server");
    }
    std::cout << "listening on : " << socket.getLocalPort() << std::endl;
    std::optional<sf::IpAddress> sender = sf::IpAddress::Any;
    unsigned short portRec = 0;
    char data[100] = {0};
    std::size_t received = 0;
    if (socket.receive(data, 100, received, sender, portRec) != sf::Socket::Status::Done)
    {
        std::cerr << "error receive" << std::endl;
    }
    std::cout << "Received " << received << " bytes from " << sender.value() << " on port " << port << std::endl;
    std::cout << "Get : " << data << std::endl;
}

int main(void)
{
    #ifdef SERVER
        /*setupServer(4242);
        while (1) {
            manager.update();
            std::this_thread::sleep_for(std::chrono::milliseconds(4));
        }*/
    #endif
    auto &engine = GameEngine::GetInstance();
    engine.Init<DevLevel>();
    engine.Run();

    return 0;
}