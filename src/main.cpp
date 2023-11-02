#include "SFML.hpp"
#include "World/World.hpp"
#include "Entity.hpp"
#include "Component.hpp"
#include "LevelManager.hpp"
#include "DevLevel.hpp"
#include "DeadLevel.hpp"
#include "LobbyLevel.hpp"
#include "GameEngine.hpp"
#include "Utils/Utils.hpp"
#include <snappy.h>

void setLevel(const std::string &str)
{
    if (str == "DevLevel") {
		LevelManager::getInstance().addLevel<DevLevel>();
        LevelManager::getInstance().setCurrentLevel<DevLevel>();
    }

    else if (str == "DeadLevel") {
        LevelManager::getInstance().addLevel<DeadLevel>();
		LevelManager::getInstance().setCurrentLevel<DeadLevel>();
    }
    else if (str == "LobbyLevel") {
        LevelManager::getInstance().addLevel<LobbyLevel>();
        LevelManager::getInstance().setCurrentLevel<LobbyLevel>();
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
    Utils::registerComponent<EnemyPath>("EnemyPath");
    Utils::registerComponent<DataComponent>("DataComponent");

    Utils::registerLevel<DevLevel>("DevLevel");
    Utils::registerLevel<LobbyLevel>("LobbyLevel");
    Utils::registerLevel<DeadLevel>("DeadLevel");

    try {
        auto &engine = GameEngine::GetInstance();
        engine.Init<LobbyLevel>();
        engine.Run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
