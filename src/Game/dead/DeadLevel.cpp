#include "DeadLevel.hpp"
#include "Component.hpp"
#include "GameEngine.hpp"
#include "World.hpp"
#include "Entity.hpp"
#include "DevLevel.hpp"

sf::Clock cooldownInput;
constexpr float cooldown = 0.25;
uint8_t selector = 0;

static void forward(ECS::Entity *ent, const float &dt)
{
    auto world = ent->getWorld();
    if (cooldownInput.getElapsedTime().asSeconds() < cooldown)
        return;
    cooldownInput.restart();
    if (selector == 0) {
        selector = 1;
    } else {
        selector = 0;
    }

    int x = 0;
    world->each<TextComponent>([&](ECS::Entity* ent, TextComponent* text) {
        if (x == 1) {
            if (selector == 0) {
                text->_text = "Restart <";
            } else {
                text->_text = "Restart";
            }
        } else if (x == 2) {
            if (selector == 0) {
                text->_text = "Quit";
            } else {
                text->_text = "Quit <";
            }
        }
        x++;
    });
}

static void backward(ECS::Entity *ent, const float &dt)
{
    auto world = ent->getWorld();
    if (cooldownInput.getElapsedTime().asSeconds() < cooldown)
        return;
    cooldownInput.restart();
    if (selector == 0) {
        selector = 1;
    } else {
        selector = 0;
    }

    int x = 0;
    world->each<TextComponent>([&](ECS::Entity* ent, TextComponent* text) {
        if (x == 1) {
            if (selector == 0) {
                text->_text = "Restart <";
            } else {
                text->_text = "Restart";
            }
        } else if (x == 2) {
            if (selector == 0) {
                text->_text = "Quit";
            } else {
                text->_text = "Quit <";
            }
        }
        x++;
    });
}

static void use(ECS::Entity *ent, const float &dt)
{
    LevelManager::getInstance().removeLevel<DeadLevel>();
    if (selector == 0) {
        LevelManager::getInstance().addLevel<DevLevel>();
        LevelManager::getInstance().setCurrentLevel<DevLevel>();
    } else {
        #ifndef SERVER
        auto &gameEngine = GameEngine::GetInstance();
        gameEngine.Shutdown();
        #else
            auto &gameEngine = GameEngine::GetInstance();
            gameEngine.getServer().disconnectClient();
        #endif
    }
}

DeadLevel::DeadLevel()
{
    const std::unordered_map<Input::Key, std::function<void(ECS::Entity*, const float&)>> input = {
        { Input::Key::forward, forward},
        { Input::Key::backward, backward},
        { Input::Key::jump, use},
    };
    auto actualLevel = _world->CreateEntity();
    actualLevel->assign<PlayerComponent>();
    actualLevel->assign<InputComponent>(input);
    #ifndef SERVER
        actualLevel->get<PlayerComponent>()->hash = "me";
    #endif // SERVER

	auto player = _world->CreateEntity();
    player->assign<DrawableComponent>("../assets/player.png");
    player->assign<TransformComponent>(sf::Vector2f(200, 200), sf::Vector2f(1, 1), 0);

    auto text = _world->CreateEntity();
    text->assign<TextComponent>("You died");
    text->assign<TransformComponent>(sf::Vector2f(1600/2 - 40, 800/4), sf::Vector2f(1, 1), 0);

    auto restart = _world->CreateEntity();
    restart->assign<TextComponent>("Restart <");
    restart->assign<TransformComponent>(sf::Vector2f(1600/2 - 40, 800/2), sf::Vector2f(1, 1), 0);

    auto quit = _world->CreateEntity();
    quit->assign<TextComponent>("Quit");
    quit->assign<TransformComponent>(sf::Vector2f(1600/2 - 40, 800/2 + 100), sf::Vector2f(1, 1), 0);

    try {
        _world->registerSystem<ECS::System::TextSystem>(0);
        _world->registerSystem<ECS::System::DrawableSystem>(1);
        _world->registerSystem<ECS::System::TransformSystem>(2);
        _world->registerSystem<ECS::System::InputSystem>(3);
        _world->registerSystem<ECS::System::VelocitySystem>(5);
    } catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}

DeadLevel::~DeadLevel()
{
}

void DeadLevel::update(const float dt)
{
}
