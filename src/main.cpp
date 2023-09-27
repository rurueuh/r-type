#include "SFML.hpp"
#include "EntityList.hpp"
#include "ComponentList.hpp"
#include "HpComponent.hpp"
#include "Entity.hpp"
#include "Player.hpp"

int main(void)
{
    EntityList list;
    ComponentList ComponentList;
    auto p = list.createEntity<Player>();
    auto p2 = list.createEntity<Player>();
    auto hp2 = ComponentList.addComponent<HpComponent>(p, 55);
    auto hp = ComponentList.addComponent<HpComponent>(p, 50);

    hp2->setHp(51);

    std::cout << list << std::endl;
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