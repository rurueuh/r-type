#include "SFML.hpp"
#include "EntityList.hpp"
#include "ComponantList.hpp"
#include "HpComponant.hpp"
#include "Entity.hpp"
#include "Player.hpp"

int main(void)
{
    EntityList list;
    ComponantList componantList;
    auto p = list.createEntity<Player>();
    auto p2 = list.createEntity<Player>();
    auto hp = componantList.addComponent<HpComponant>(p);

    std::cout << p->getId() << std::endl;
    std::cout << p2->getId() << std::endl;
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML works!");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        window.clear();


        window.display();
    }
    return 0;
}