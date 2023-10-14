#include "SFML.hpp"
#include "World/World.hpp"
#include "Entity.hpp"
#include "TestSystem.hpp"
#include "Component.hpp"
#include "LevelManager.hpp"
#include "DevLevel.hpp"
#include "GameEngine.hpp"
#include "Utils/Utils.hpp"

std::string compress_str(std::string str)
{
    int j = 0;
    std::string result;
    for (int i = 0; i < str.length(); i++) {

        int count = 0;
        while (i < str.length() - 1 && str[i] == str[i + 1]) {
            count++;
            i++;
        }

        if (count > 0) {
            result += str[i];
            result += std::to_string(count + 1);
        } else {
            result += str[i];
        }
    }
    return result;
}

std::string decompressString(std::string str) {
    std::string result;
    for (int i = 0; i < str.length(); i++) {
        if (isdigit(str[i])) {
            int count = str[i] - '0';
            while (count > 0) {
                result += str[i - 1];
                count--;
            }
        } else {
            result += str[i];
        }
    }
    return result;
}

int main(void)
{
    Utils::registerComponent<PvComponent>("PvComponent");
    Utils::registerComponent<PlayerInputComponent>("PlayerInputComponent");
    auto &engine = GameEngine::GetInstance();
    engine.Init<DevLevel>();
    engine.Run();

    return 0;
}