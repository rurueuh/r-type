#include "SFML.hpp"
#include "World/World.hpp"
#include "Entity.hpp"
#include "TestSystem.hpp"
#include "Component.hpp"
#include "LevelManager.hpp"
#include "DevLevel.hpp"
#include "GameEngine.hpp"
#include "Utils/Utils.hpp"

int main(void)
{
    Utils::registerComponent<PvComponent>("PvComponent");
    Utils::registerComponent<PlayerInputComponent>("PlayerInputComponent");
    auto &engine = GameEngine::GetInstance();
    engine.Init<DevLevel>();
    engine.Run();

    return 0;
}