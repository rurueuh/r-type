#include "First_Level.hpp"
#include "Component.hpp"
#include "GameEngine.hpp"
#include "World.hpp"
#include "Entity.hpp"
#include "DeadLevel.hpp"

static void forward(ECS::Entity *ent, const float &dt)
{
	ent->get<VelocityComponent>()->velocity.y -= 1 * dt * 142;
}

static void backward(ECS::Entity *ent, const float &dt)
{
	ent->get<VelocityComponent>()->velocity.y += 1 * dt * 142;
}

static void left(ECS::Entity *ent, const float &dt)
{
	ent->get<VelocityComponent>()->velocity.x -= 1 * dt * 142;
}

static void right(ECS::Entity *ent, const float &dt)
{
	ent->get<VelocityComponent>()->velocity.x += 1 * dt * 142;
}

static void shoot(ECS::Entity *ent, const float &dt)
{
    static sf::Clock cooldown;
    if (cooldown.getElapsedTime().asSeconds() < 0.5)
		return;
    cooldown.restart();
    if (!ent) // for start cooldown shoot
        return;
    auto transform = ent->get<TransformComponent>();
    auto velocity = ent->get<VelocityComponent>();
    auto world = ent->getWorld();
    auto bullet = world->CreateEntity();
    bullet->assign<DrawableComponent>("../assets/player.png", sf::IntRect(1, 3, 32, 14));
    bullet->assign<TransformComponent>(transform->position, sf::Vector2f(1.f, 1.f), 0.f);
    bullet->assign<LifeSpan>(3.f);
    bullet->assign<OnDie>([](ECS::World *world,ECS::Entity* ent) {
        std::cout << "Bullet die" << std::endl;
    });
    bullet->assign<CollisionComponent>(sf::FloatRect(transform->position.x, transform->position.y, 32, 14),
        ECS::Collision::BULLET_PLAYER);
    if (!velocity)
        bullet->assign<VelocityComponent>(620.f, 0.f);
    else
        bullet->assign<VelocityComponent>(620.f + (velocity->velocity.x), 0.f + (velocity->velocity.y));
}

static void collisionPlayerWall(ECS::World *world, ECS::Entity *e1, ECS::Entity *e2)
{
	auto transform = e1->get<TransformComponent>();
	auto velocity = e1->get<VelocityComponent>();
	if (!transform || !velocity)
		return;
	transform->position.x -= velocity->velocity.x;
	transform->position.y -= velocity->velocity.y;
	velocity->velocity = sf::Vector2f(0.f, 0.f);
}

static void collisionBulletWall(ECS::World *world, ECS::Entity *e1, ECS::Entity *e2)
{
    e2->die();
}

static void checkPlayerEnd(ECS::World* world, ECS::Entity* ent)
{
    // get all player
std::vector<ECS::Entity*> players = {};
    world->each<PlayerComponent>([&](ECS::Entity* ent, PlayerComponent* player) {
	players.push_back(ent);
	});
	// check if all player are dead
	bool allDead = true;
	for (auto player : players) {
		if (player->get<PvComponent>()->_health > 0)
			allDead = false;
	}
	if (allDead) {
		std::cout << "All player are dead" << std::endl;
        auto &levelManager = LevelManager::getInstance();
        levelManager.addLevel<DeadLevel>();
        levelManager.removeLevel<DevLevel>();
        levelManager.setCurrentLevel<DeadLevel>();

	}
}

FirstLevel::FirstLevel() : Level()
{
    auto window = GameEngine::GetInstance().getWindow();
    sf::Vector2u size = { 1600, 900 };
    #ifndef SERVER
        size = window->getSize();
    #endif
    CreateBackground(window, size);
    CreateWall(window, size);
    CreatePlayers();
    auto wall = _world->CreateEntity();
    wall->assign<DrawableComponent>("../assets/player.png", sf::IntRect(1, 3, 32, 14));
    wall->assign<TransformComponent>(sf::Vector2f(600, 600), sf::Vector2f(3.f, 3.f), 0.f);
    wall->assign<CollisionComponent>(sf::FloatRect(600, 600, 32 * 3, 14 * 3), ECS::Collision::WALL);
    CollisionActionList collisionAction = {
        { {ECS::Collision::PLAYER, ECS::Collision::WALL}, collisionPlayerWall},
		{ {ECS::Collision::BULLET_PLAYER, ECS::Collision::WALL}, collisionBulletWall},
        { {ECS::Collision::PLAYER, ECS::Collision::ENEMY}, collisionPlayerEnemy},
        { {ECS::Collision::BULLET_PLAYER, ECS::Collision::ENEMY}, collisionBulletEnemy},
	};
    try {
        _world->registerSystem<ECS::System::TransformSystem>(0);
        _world->registerSystem<ECS::System::DrawableSystem>(1);
        _world->registerSystem<ECS::System::CollisionSystem>(2, collisionAction);
        _world->registerSystem<ECS::System::InputSystem>(3);
        _world->registerSystem<ECS::System::VelocitySystem>(4);
        _world->registerSystem<ECS::System::LifeSpanSystem>(5);
        _world->registerSystem<ECS::System::HpSystem>(6);
    } catch (const std::exception &e) {
        std::cout << "ERROR : " << e.what() << std::endl;
    }
}

void FirstLevel::CreatePlayers()
{}

void FirstLevel::CreateBackground(sf::RenderWindow* window, sf::Vector2u& size)
{}

void FirstLevel::CreateWall(sf::RenderWindow* window, sf::Vector2u& size)
{
    sf::Texture wallTexture;
    if (!wallTexture.loadFromFile("../assets/firstLevelWalls.png")) {
        // Handle the case where loading the texture fails
        std::cerr << "Failed to load wall texture." << std::endl;
        return;
    }

    for (unsigned int x = 0; x < wallTexture.getSize().x; ++x) {
        for (unsigned int y = 0; y < wallTexture.getSize().y; ++y) {
            sf::Color pixelColor = wallTexture.getPixel(x, y);

            if (pixelColor == sf::Color::Black) {
                // Create a wall entity at the corresponding position
                auto wall = _world->CreateEntity();
                wall->assign<DrawableComponent>("file.png", sf::IntRect(x, y, 1, 1)); // Assuming 1 pixel wall
                wall->assign<TransformComponent>(sf::Vector2f(x, y), sf::Vector2f(1.f, 1.f), 0.f);
                wall->assign<CollisionComponent>(sf::FloatRect(x, y, 1, 1), ECS::Collision::WALL);
            }
        }
    }
}

FirstLevel::~FirstLevel()
{
}

void FirstLevel::update(const float dt)
{
    static sf::Clock clock;
    static sf::Clock enemySpawnClock;
    static bool schwarziSpawned = false;
    static bool fliesSpawned = false;
    static bool bossSpawned = false;

    if (clock.getElapsedTime().asSeconds() > 0.1) {
        BackgroundParallax();
        ScrollWalls(dt)
        _world->each<PvComponent>([&](ECS::Entity* ent, PvComponent* pv) {
            pv->_health -= 1.f * dt * 1000.f;
		});
		clock.restart();
	}
    if (!enemiesSpawned && clock.getElapsedTime().asSeconds() > 5.0f) {
        CreateEnemies(1);
        schwarziSpawned = true;
    }
    if (!enemiesSpawned && clock.getElapsedTime().asSeconds() > 10.0f) {
        CreateEnemies(2);
        fliesSpawned = true;
    }
    if (!enemiesSpawned && clock.getElapsedTime().asSeconds() > 15.0f) {
        CreateEnemies(3);
        bossSpawned = true;
    }
}

void FirstLevel::CreateEnemies(size_t id)
{}

void DevLevel::BackgroundParallax()
{
    _world->each<TransformComponent>([&](ECS::Entity* ent, TransformComponent* transform) {
        if (ent->has<BackgroundTag>()) {
            auto window = GameEngine::GetInstance().getWindow();
            if (transform->position.x < -1580) {
                auto drawable = ent->get<DrawableComponent>();
                sf::Vector2u size = { 1600, 900 };
#ifndef SERVER
                size = GameEngine::GetInstance().getWindow()->getSize();
#endif
                transform->position.x = (float)size.x;
                drawable->area.left = size.x;
                drawable->area.width = size.x;
            }
        }
        });
    std::vector<ECS::Entity*> backgrounds = {};
    _world->each<VelocityComponent>([&](ECS::Entity* ent, VelocityComponent* velocity) {
        if (ent->has<BackgroundTag>()) {
            backgrounds.push_back(ent);
        }
        });
    _backgrounds = backgrounds;
    if (_backgrounds.size() == 0)
        return;
    for (int i = 0; i < _infoBackgrounds.size(); i++) {
        auto& e = _backgrounds[i * 2];
        auto& e2 = _backgrounds[i * 2 + 1];

        auto t = e->get<VelocityComponent>();
        auto t2 = e2->get<VelocityComponent>();

        t->velocity = sf::Vector2f(_infoBackgrounds[i].speed, 0.f);
        t2->velocity = sf::Vector2f(_infoBackgrounds[i].speed, 0.f);
    }
}

void FirstLevel::ScrollWalls(const float dt)
{
    _world->each<TransformComponent>([&](ECS::Entity* ent, TransformComponent* transform) {
        if (ent->has<DrawableComponent>()) {
            transform->position.x -= 10.0f * dt; // Adjust the scroll speed as needed
        }
    });
}
