#include "LobbyLevel.hpp"
#include "Component.hpp"
#include "GameEngine.hpp"
#include "World.hpp"
#include "Entity.hpp"
#include "DevLevel.hpp"
#include "FirstLevel.hpp"

static sf::Clock cooldownInput;
static constexpr float cooldown = 0.25;
static uint8_t selector = 0;

static void forward(ECS::Entity *ent, const float &dt)
{
    auto world = ent->getWorld();
    if (cooldownInput.getElapsedTime().asSeconds() < cooldown)
        return;
    cooldownInput.restart();
    if (selector == 0) {
        selector = 1;
    } else if (selector == 1) {
        selector = 0;
    }

    int x = 0;
    world->each<TextComponent>([&](ECS::Entity* ent, TextComponent* text) {
        if (x == 1) {
            if (selector == 0) {
                text->_text = "Start <";
            } else if (selector == 1) {
                text->_text = "Start";
            }
        } else if (x == 2) {
            if (selector == 0) {
                text->_text = "Quit";
            } else if (selector == 1) {
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
                text->_text = "Start <";
            } else if (selector == 1) {
                text->_text = "Start";
            }
        } else if (x == 2) {
            if (selector == 0) {
                text->_text = "Quit";
            } else if (selector == 1) {
                text->_text = "Quit <";
            }
        }
        x++;
    });
}

static void use(ECS::Entity *ent, const float &dt)
{
    LevelManager::getInstance().removeLevel<LobbyLevel>();
    if (selector == 0) {
        LevelManager::getInstance().addLevel<FirstLevel>();
        LevelManager::getInstance().setCurrentLevel<FirstLevel>();
        sf::sleep(sf::seconds(1));
    } else if (selector == 1) {
        #ifndef SERVER
            auto &gameEngine = GameEngine::GetInstance();
            gameEngine.Shutdown();
        #else
            auto &gameEngine = GameEngine::GetInstance();
            gameEngine.getServer().disconnectClient();
            LevelManager::getInstance().addLevel<LobbyLevel>();
            LevelManager::getInstance().setCurrentLevel<LobbyLevel>();
            sf::sleep(sf::seconds(1));
        #endif
    }
}

static void secretLevel(ECS::Entity *ent, const float &dt)
{
    (void) ent;
    (void) dt;
    LevelManager::getInstance().removeLevel<LobbyLevel>();
    LevelManager::getInstance().addLevel<DevLevel>();
    LevelManager::getInstance().setCurrentLevel<DevLevel>();
    sf::sleep(sf::seconds(1));
}

LobbyLevel::LobbyLevel()
{
    const std::unordered_map<Input::Key, std::function<void(ECS::Entity*, const float&)>> input = {
        { Input::Key::forward, forward},
        { Input::Key::backward, backward},
        { Input::Key::jump, use},
        { Input::Key::secret, secretLevel},
    };
    const std::unordered_map<Input::Key, std::function<void(ECS::Entity*, const float&)>> nullInput = {};

    auto actualLevel = _world->CreateEntity();
    actualLevel->assign<PlayerComponent>();
    actualLevel->assign<InputComponent>(input);
    #ifndef SERVER
        actualLevel->get<PlayerComponent>()->hash = "me";
    #endif // SERVER
    const short maxPlayer = 4 - 1;
    for (short i = 0; i < maxPlayer; i++) {
        auto player = _world->CreateEntity();
        player->assign<PlayerComponent>();
        player->assign<InputComponent>(nullInput);
    }

	auto player = _world->CreateEntity();
    player->assign<DrawableComponent>("../assets/player.png");
    player->assign<TransformComponent>(sf::Vector2f(200, 200), sf::Vector2f(1, 1), 0);

    auto text = _world->CreateEntity();
    text->assign<TextComponent>("Welcome to the lobby");
    text->assign<TransformComponent>(sf::Vector2f(1600/2 - 40, 800/4), sf::Vector2f(1, 1), 0);

    auto restart = _world->CreateEntity();
    restart->assign<TextComponent>("Start <");
    restart->assign<TransformComponent>(sf::Vector2f(1600/2 - 40, 800/2), sf::Vector2f(1, 1), 0);

    auto quit = _world->CreateEntity();
    quit->assign<TextComponent>("Quit");
    quit->assign<TransformComponent>(sf::Vector2f(1600/2 - 40, 800/2 + 100), sf::Vector2f(1, 1), 0);

    auto nbPlayer = _world->CreateEntity();
    nbPlayer->assign<TextComponent>("0");
    nbPlayer->assign<TransformComponent>(sf::Vector2f(1600/2 - 40, 800/2 + 200), sf::Vector2f(1, 1), 0);
    nbPlayer->assign<DataComponent>();

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

LobbyLevel::~LobbyLevel()
{
}

void LobbyLevel::update(const float dt)
{
    auto world = _world;
    auto nbPlayerText = world->GetEntitiesByTag<DataComponent>();
    auto players = world->GetEntitiesByTag<PlayerComponent>();
    int nb = 0;
    for (auto &player : players) {
        if (player->get<PlayerComponent>()->hash != "")
            nb++;
    }
    if (nbPlayerText.size() > 0 && nbPlayerText[0]->has<TextComponent>())
        nbPlayerText[0]->get<TextComponent>()->_text = std::to_string(nb) + " player(s) active";
}
