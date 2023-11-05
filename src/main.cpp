#include "SFML.hpp"
#include "World/World.hpp"
#include "Entity.hpp"
#include "Component.hpp"
#include "LevelManager.hpp"
#include "FirstLevel.hpp"
#include "DeadLevel.hpp"
#include "WinLevel.hpp"
#include "GameEngine.hpp"
#include "Utils/Utils.hpp"
#include <snappy.h>

void setLevel(const std::string &str)
{
    if (str == "FirstLevel") {
		LevelManager::getInstance().addLevel<FirstLevel>();
        LevelManager::getInstance().setCurrentLevel<FirstLevel>();
    }

    else if (str == "DeadLevel") {
        LevelManager::getInstance().addLevel<DeadLevel>();
		LevelManager::getInstance().setCurrentLevel<DeadLevel>();
    }

    else if (str == "WinLevel") {
        LevelManager::getInstance().addLevel<WinLevel>();
		LevelManager::getInstance().setCurrentLevel<WinLevel>();
    }
    else
        std::cerr << "Unknown level: " << str << std::endl;
}

int main(void)
{
    Utils::registerComponent<PvComponent>("PvComponent");
    Utils::registerComponent<InputComponent>("InputComponent");
    Utils::registerComponent<PlayerComponent>("PlayerComponent");
    Utils::registerComponent<DrawableComponent>("DrawableComponent");
    Utils::registerComponent<TransformComponent>("TransformComponent");
    Utils::registerComponent<VelocityComponent>("VelocityComponent");
    Utils::registerComponent<LifeSpan>("LifeSpan");
    Utils::registerComponent<OnDie>("OnDie");
    Utils::registerComponent<EnemyTag>("ETag");
    Utils::registerComponent<BackgroundTag>("BTag");
    Utils::registerComponent<CollisionComponent>("CollisionComponent");
    Utils::registerComponent<TextComponent>("TextComponent");
    Utils::registerComponent<PatternComponent>("PatternComponent");

    Utils::registerLevel<FirstLevel>("FirstLevel");
    Utils::registerLevel<DeadLevel>("DeadLevel");
    Utils::registerLevel<WinLevel>("WinLevel");

    try {
        auto &engine = GameEngine::GetInstance();
        engine.Init<FirstLevel>();
        engine.Run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
