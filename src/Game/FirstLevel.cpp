#include "FirstLevel.hpp"
#include "Component.hpp"
#include "GameEngine.hpp"
#include "World.hpp"
#include "Entity.hpp"
#include "DeadLevel.hpp"
#include "WinLevel.hpp"

bool isBossAlive = true;

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
    bullet->assign<DrawableComponent>("./assets/player.png", sf::IntRect(1, 3, 32, 14));
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

static void collisionPlayerEnemy(ECS::World *world, ECS::Entity *e1, ECS::Entity *e2)
{
    auto pv = e1->get<PvComponent>();
    auto ppv = e2->get<PvComponent>();
    pv->_health -= 70;
    ppv->_health -= 1;
}

static void collisionBulletEnemy(ECS::World *world, ECS::Entity *e1, ECS::Entity *e2)
{
    auto pv = e2->get<PvComponent>();
    pv->_health -= 1;
    e1->die();
}

static void victory(ECS::World* world, ECS::Entity* ent)
{
    isBossAlive = false;
	std::cout << "Victory ours!" << std::endl;
    auto &levelManager = LevelManager::getInstance();
    levelManager.addLevel<WinLevel>();
    levelManager.removeLevel<FirstLevel>();
    levelManager.setCurrentLevel<WinLevel>();
}

static void checkPlayerEnd(ECS::World* world, ECS::Entity* ent)
{
    if (isBossAlive == false)
        victory(world, ent);
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
        levelManager.removeLevel<FirstLevel>();
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
    CreatePlayers();
    CollisionActionList collisionAction = {
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
{
    const std::unordered_map<Input::Key, std::function<void(ECS::Entity*, const float&)>> input = {
        { Input::Key::forward, forward },
        { Input::Key::backward, backward },
        { Input::Key::left, left },
        { Input::Key::right, right },
        { Input::Key::jump, shoot }
    };
    shoot(nullptr, 0.f); // for start cooldown shoot
    std::vector<ECS::Entity*> starship = _world->CreateEntity(6);
    size_t i = 0;
    for (auto ship : starship) {
        ship->assign<PlayerComponent>();
        ship->assign<InputComponent>(input);
        ship->assign<PvComponent>(100.f, 100.f);
        ship->assign<DrawableComponent>("./assets/player.png", _infoPlayers[i % _infoPlayers.size()]);
        ship->assign<VelocityComponent>(0.1f, 0.1f);
        const float x = 400;
        const float y = 400;
        ship->assign<TransformComponent>(sf::Vector2f(x, y), sf::Vector2f(4.f, 4.f), 0.f);
        ship->assign<CollisionComponent>(sf::FloatRect(400, 400, 32 * 4,14 * 4), ECS::Collision::PLAYER);
        ship->assign<OnDie>(checkPlayerEnd);
        i++;
    }
#ifndef SERVER
    starship[0]->get<PlayerComponent>()->hash = "me";
#endif // SERVER
}

void FirstLevel::CreateBackground(sf::RenderWindow* window, sf::Vector2u& size)
{
    for (int i = 0; i < _backgrounds.size(); i += 2) {
        auto d = _backgrounds[i]->assign<DrawableComponent>(_infoBackgrounds[i / 2].path, _infoBackgrounds[i / 2].area);
        auto t = _backgrounds[i]->assign<TransformComponent>(sf::Vector2f(0, 0), sf::Vector2f(1.f, 1.f), 0.f);
        _backgrounds[i]->assign<VelocityComponent>(_infoBackgrounds[i / 2].speed, 0.f);
        _backgrounds[i]->assign<BackgroundTag>();
        t->setFullScreen(window, d->area);
        t->scale += sf::Vector2f(0.1f, 0.1f);

        auto rect2 = _infoBackgrounds[i / 2].area;
        rect2.left = size.x;
        auto d2 = _backgrounds[i + 1]->assign<DrawableComponent>(_infoBackgrounds[i / 2].path, rect2);
        auto t2 = _backgrounds[i + 1]->assign<TransformComponent>(sf::Vector2f(0, 0), sf::Vector2f(1.f, 1.f), 0.f);
        _backgrounds[i + 1]->assign<VelocityComponent>(_infoBackgrounds[i / 2].speed, 0.f);
        _backgrounds[i + 1]->assign<BackgroundTag>();
        t2->setFullScreen(window, d2->area);
        t2->scale += sf::Vector2f(0.1f, 0.1f);
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

    if (clock.getElapsedTime().asSeconds() > 0.1) {
        BackgroundParallax();
        //EnemyPatterns(dt);
		clock.restart();
	}
    if (!schwarziSpawned && enemySpawnClock.getElapsedTime().asSeconds() > 8.0f) {
        schwarziSpawned = true;
        CreateEnemies(0, 800, 100);
        CreateEnemies(0, 800, 350);
        CreateEnemies(0, 800, 600);
        enemySpawnClock.restart();
    }
    if (!fliesSpawned && schwarziSpawned && enemySpawnClock.getElapsedTime().asSeconds() > 12.0f) {
        fliesSpawned = true;
        CreateEnemies(1, 850, 100);
        CreateEnemies(1, 850, 300);
        CreateEnemies(1, 850, 500);
        CreateEnemies(1, 850, 700);
        CreateEnemies(1, 1050, 100);
        CreateEnemies(1, 1050, 300);
        CreateEnemies(1, 1050, 500);
        CreateEnemies(1, 1050, 700);
        CreateEnemies(1, 950, 10);
        CreateEnemies(1, 950, 200);
        CreateEnemies(1, 950, 400);
        CreateEnemies(1, 950, 800);
        CreateEnemies(1, 950, 600);
        CreateEnemies(1, 1250, 100);
        CreateEnemies(1, 1250, 300);
        CreateEnemies(1, 1250, 500);
        CreateEnemies(1, 1250, 700);
        CreateEnemies(1, 1150, 10);
        CreateEnemies(1, 1150, 200);
        CreateEnemies(1, 1150, 400);
        CreateEnemies(1, 1150, 800);
        CreateEnemies(1, 1150, 600);
        enemySpawnClock.restart();
    }
    if (fliesSpawned && enemySpawnClock.getElapsedTime().asSeconds() > 22.0f) {
        CreateEnemies(2, 900, 200);
    }
}

void FirstLevel::CreateEnemies(size_t id, size_t x, size_t y)
{
    auto enemy = _world->CreateEntity();
        enemy->assign<EnemyTag>();
        enemy->assign<DrawableComponent>(_infoEnemies[id].path, _infoEnemies[id].area);
        enemy->assign<TransformComponent>(sf::Vector2f(x, y), sf::Vector2f(3.f, 3.f), 0.f);
        enemy->assign<CollisionComponent>(sf::FloatRect(x, y, _infoEnemies[id].area.width * 3, _infoEnemies[id].area.height * 3), ECS::Collision::ENEMY);
        enemy->assign<PvComponent>(_infoEnemies[id].health, _infoEnemies[id].health);
        enemy->assign<PatternComponent>(_infoEnemies[id].pattern, 0);
        if (id == 2)
            enemy->assign<OnDie>(victory);
}

/*void FirstLevel::EnemyPatterns(const float dt)
{
    std::vector<ECS::Entity*> enemies = {};
    _world->each<EnemyTag>([&](ECS::Entity* ent, EnemyTag* enemy) {
        enemies.push_back(ent);
    });
    for (auto enemy : enemies) {
        auto pat = enemy->get<PatternComponent>();
        if (pat->pattern[pat->currentIndex] == 'N')
            pat->currentIndex = 0;
        switch (pat->pattern[pat->currentIndex]) {
        case 'o':
            pat->currentIndex++;
            break;
        case 'l':
            left(enemy, dt);
            pat->currentIndex++;
            break;
        case 'a':
            left(enemy, dt);
            forward(enemy, dt);
            pat->currentIndex++;
            break;
        case 'i':
            left(enemy, dt);
            backward(enemy, dt);
            pat->currentIndex++;
            break;
        case 'r':
            right(enemy, dt);
            pat->currentIndex++;
            break;
        
        default:
            break;
        }
    };
}*/

void FirstLevel::BackgroundParallax()
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

