#include "DevLevel.hpp"
#include "Component.hpp"
#include "TestSystem.hpp"

DevLevel::DevLevel() : Level()
{
    ECS::Entity &player = _world->CreateEntity();
    ECS::Entity &player2 = _world->CreateEntity();
    ECS::Entity &player3 = _world->CreateEntity();
    player.assign<PvComponent>(100);
    player2.assign<PvComponent>(1000);
    player.assign<PvComponent>(150);

    try {
        //_world->registerSystem<TestSystem>(0);
    } catch (const std::exception &e) {
        std::cout << "ERROR : " << e.what() << std::endl;
    }
}

DevLevel::~DevLevel()
{
}

void DevLevel::update(const float dt)
{
}
