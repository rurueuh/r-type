#include "WinLevel.hpp"
#include "Component.hpp"
#include "GameEngine.hpp"
#include "World.hpp"
#include "Entity.hpp"
#include "FirstLevel.hpp"
#include "LobbyLevel.hpp"

sf::Clock newCooldownInput;
constexpr float cooldown = 1.25;
uint8_t newSelector = 0;

static void forward(ECS::Entity *ent, const float &dt)
{
    auto world = ent->getWorld();
    if (newCooldownInput.getElapsedTime().asSeconds() < cooldown)
        return;
    newCooldownInput.restart();
    if (newSelector == 0) {
        newSelector = 1;
    } else {
        newSelector = 0;
    }

    int x = 0;
    world->each<TextComponent>([&](ECS::Entity* ent, TextComponent* text) {
        if (x == 1) {
            if (newSelector == 0) {
                text->_text = "Restart <";
            } else {
                text->_text = "Restart";
            }
        } else if (x == 2) {
            if (newSelector == 0) {
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
    if (newCooldownInput.getElapsedTime().asSeconds() < cooldown)
        return;
    newCooldownInput.restart();
    if (newSelector == 0) {
        newSelector = 1;
    } else {
        newSelector = 0;
    }

    int x = 0;
    world->each<TextComponent>([&](ECS::Entity* ent, TextComponent* text) {
        if (x == 1) {
            if (newSelector == 0) {
                text->_text = "Restart <";
            } else {
                text->_text = "Restart";
            }
        } else if (x == 2) {
            if (newSelector == 0) {
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
    LevelManager::getInstance().removeLevel<WinLevel>();
    if (newSelector == 0) {
        LevelManager::getInstance().addLevel<LobbyLevel>();
        LevelManager::getInstance().setCurrentLevel<LobbyLevel>();
        sf::sleep(sf::milliseconds(1000));
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

WinLevel::WinLevel() : Level()
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

    auto window = GameEngine::GetInstance().getWindow();
    auto _backgrounds = _world->CreateEntity();
    auto d = _backgrounds->assign<DrawableComponent>("./assets/victory.jpg", sf::IntRect(0, 0, 1920, 1080));
    auto t = _backgrounds->assign<TransformComponent>(sf::Vector2f(0, 0), sf::Vector2f(1.f, 1.f), 0.f);
    _backgrounds->assign<BackgroundTag>();
    t->setFullScreen(window, d->area);

    auto text = _world->CreateEntity();
    text->assign<TextComponent>("You won congratulations!");
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

WinLevel::~WinLevel()
{
}

void WinLevel::update(const float dt)
{
}