#include "SFML.hpp"
#include "World/World.hpp"
#include "Entity.hpp"
#include "Component.hpp"
#include "LevelManager.hpp"
#include "DevLevel.hpp"
#include "GameEngine.hpp"
#include "Utils/Utils.hpp"
#include <snappy.h>

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

    auto &engine = GameEngine::GetInstance();
    engine.Init<DevLevel>();
    engine.Run();

    return 0;
}
