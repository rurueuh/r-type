#include "DevLevel.hpp"
#include "Component.hpp"
#include "TestSystem.hpp"

struct PositionComponent {
    PositionComponent(float x, float y) : x(x), y(y) {};
    PositionComponent() : x(0), y(0) {};

    float x, y;

    virtual std::string toString(void) {
		std::stringstream ss;
		ss << x << " " << y;
        return ss.str();
    }
};

//struct TestComponent {
//    TestComponent(float x) : x(x) {};
//    float x;
//
//    std::string toString(void) {
//        std::stringstream ss;
//        ss << x;
//		return ss.str();
//    }
//    void loadFromString(std::string str) {
//		std::stringstream ss(str);
//		ss >> x;
//	}
//};


DevLevel::DevLevel() : Level()
{
    Utils::registerComponent<PvComponent>("PvComponent");
    Utils::registerComponent<PositionComponent>("PositionComponent");

    ECS::Entity* player = _world->CreateEntity();
    ECS::Entity *player2 = _world->CreateEntity();
    player->assign<PvComponent>(100);
    player->assign<PositionComponent>(10.f, 10.f);
    player2->assign<PvComponent>(10000);

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
