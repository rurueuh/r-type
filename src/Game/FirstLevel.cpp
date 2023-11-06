#include "FirstLevel.hpp"
#include "Component.hpp"
#include "GameEngine.hpp"
#include "World.hpp"
#include "Entity.hpp"
#include "DeadLevel.hpp"
#include "WinLevel.hpp"

#ifndef SERVER
    static sf::SoundBuffer *_buffer = nullptr;
    static sf::Sound *_sound = nullptr;
    static sf::Music *_music = nullptr;
#endif
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
    #ifndef SERVER
        _sound->play();
    #endif
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

static void shootEnemy(ECS::World *world, const float &dt, ECS::Entity *ent)
{
    if (!ent->has<DataComponent>())
        return;
	auto cooldown = ent->get<DataComponent>()->get<float>("timeShoot");
    if (cooldown < 3.5)
        return;
    #ifndef SERVER
        _sound->play();
    #endif
    ent->get<DataComponent>()->set("timeShoot", 0.f);
	auto transform = ent->get<TransformComponent>();
	auto velocity = ent->get<VelocityComponent>();
	auto bullet = world->CreateEntity();
	bullet->assign<DrawableComponent>("../assets/sheet1.png", sf::IntRect(337, 255, 12, 4));
	bullet->assign<TransformComponent>(transform->position, sf::Vector2f(-2.f, 2.f), 0.f);
	bullet->assign<LifeSpan>(2.f);
    bullet->assign<OnDie>([](ECS::World* world, ECS::Entity* ent) {
		std::cout << "Bullet die" << std::endl;
	});
	bullet->assign<CollisionComponent>(sf::FloatRect(transform->position.x, transform->position.y, 32, 14),
        ECS::Collision::BULLET_ENEMY);
	if (!velocity)
		bullet->assign<VelocityComponent>(-620.f, 0.f);
	else
		bullet->assign<VelocityComponent>(-620.f + (velocity->velocity.x), 0.f + (velocity->velocity.y));
}

static void shootEnemyBoss(ECS::World *world, const float &dt, ECS::Entity *ent)
{
    if (!ent->has<DataComponent>())
        return;
	auto cooldown = ent->get<DataComponent>()->get<float>("timeShoot");
    if (cooldown < 3.5)
        return;
    #ifndef SERVER
        _sound->play();
    #endif
    ent->get<DataComponent>()->set("timeShoot", 0.f);
	auto transform = ent->get<TransformComponent>();
	auto velocity = ent->get<VelocityComponent>();
    for (int i = 0; i < 12; i++) {
        auto bullet = world->CreateEntity();
        auto x = rand() % 100;
        auto y = rand() % 100;
        bullet->assign<DrawableComponent>("../assets/sheet1.png", sf::IntRect(337, 255, 12, 4));
        bullet->assign<TransformComponent>(sf::Vector2f(transform->position.x + x, transform->position.y + y), sf::Vector2f(-4.f, 4.f), 0.f);
        bullet->assign<LifeSpan>(2.f);
        bullet->assign<CollisionComponent>(sf::FloatRect(transform->position.x, transform->position.y, 32, 14),
            ECS::Collision::BULLET_ENEMY);
        if (!velocity)
            bullet->assign<VelocityComponent>(-620.f, 0.f);
        else
            bullet->assign<VelocityComponent>(-620.f + (velocity->velocity.x + x), 0.f + (velocity->velocity.y + y));
        bullet->assign<EnemyPath>(EnemyPathType::FOLLOW_PATH_BOSS);
        bullet->assign<OnDie>([](ECS::World* world, ECS::Entity* ent) {
            std::cout << "Bullet die" << std::endl;
        });
    }
    
}

static void collisionPlayerEnemy(ECS::World *world, ECS::Entity *e1, ECS::Entity *e2)
{
    auto pv = e1->get<PvComponent>();
    auto ppv = e2->get<PvComponent>();
    pv->_health -= 10;
    ppv->_health -= 1;
}

static void collisionBulletEnemy(ECS::World *world, ECS::Entity *e1, ECS::Entity *e2)
{
    auto pv = e2->get<PvComponent>();
    pv->_health -= 20;
    e1->die();
}

static void collisionBulletPlayer(ECS::World *world, ECS::Entity *e1, ECS::Entity *e2)
{
    auto pv = e2->get<PvComponent>();
    pv->_health -= 10;
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
    sf::sleep(sf::milliseconds(1000));
}

static void checkPlayerEnd(ECS::World* world, ECS::Entity* ent)
{
    if (isBossAlive == false)
        victory(world, ent);
    #ifndef SERVER
        if (GameEngine::GetInstance().getClient().getClientHash() == "me") {
            auto &levelManager = LevelManager::getInstance();
            levelManager.addLevel<DeadLevel>();
            levelManager.removeLevel<FirstLevel>();
            levelManager.setCurrentLevel<DeadLevel>();
        }
    #endif
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
    isBossAlive = true;
    #ifndef SERVER
        _music = new sf::Music();
        _music->openFromFile("./assets/sound/music.ogg");
        _music->setLoop(true);
        _music->play();

        _buffer = new sf::SoundBuffer();
        _buffer->loadFromFile("./assets/sound/shoot.ogg");
        _sound = new sf::Sound();
        _sound->setBuffer(*_buffer);
    #endif

    auto levelEntity = _world->CreateEntity();
    auto data = levelEntity->assign<DataComponent>();
    levelEntity->assign<LevelTag>();

    data->set("schwarziSpawned", 0.f);
    data->set("fliesSpawned", 0.f);
    data->set("bossSpawned", 0.f);

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
        { {ECS::Collision::BULLET_ENEMY, ECS::Collision::PLAYER}, collisionBulletPlayer}
	};
    ECS::System::Path::ShootPathType typeOfShoot = {
        { FOLLOW_PLAYER, shootEnemy },
        { FOLLOW_PATH, shootEnemy },
        { FOLLOW_PLAYER_BOSS, shootEnemyBoss },
        { FOLLOW_PATH_BOSS, shootEnemyBoss },
    };
    try {
        _world->registerSystem<ECS::System::TransformSystem>(0);
        _world->registerSystem<ECS::System::DrawableSystem>(1);
        _world->registerSystem<ECS::System::CollisionSystem>(2, collisionAction);
        _world->registerSystem<ECS::System::InputSystem>(3);
        _world->registerSystem<ECS::System::VelocitySystem>(4);
        _world->registerSystem<ECS::System::LifeSpanSystem>(5);
        _world->registerSystem<ECS::System::HpSystem>(6);
        _world->registerSystem<ECS::System::PathSystem>(7, typeOfShoot);
        _world->registerSystem<ECS::System::AnimationSystem>(8);
    } catch (const std::exception &e) {
        std::cout << "ERROR : " << e.what() << std::endl;
    }
}

static void cheatCode(ECS::Entity *ent, const float &dt)
{
    static sf::Clock clock;
    if (clock.getElapsedTime().asSeconds() < 0.5)
        return;
    clock.restart();
    auto mob = ent->getWorld()->GetEntitiesByTag<EnemyTag>();
    if (mob.size() > 0)
        mob[0]->die();
}

void FirstLevel::CreatePlayers()
{
    const std::unordered_map<Input::Key, std::function<void(ECS::Entity*, const float&)>> input = {
        { Input::Key::forward, forward },
        { Input::Key::backward, backward },
        { Input::Key::left, left },
        { Input::Key::right, right },
        { Input::Key::jump, shoot },
        { Input::Key::secret, cheatCode}
    };
    shoot(nullptr, 0.f); // for start cooldown shoot
    std::vector<ECS::Entity*> starship = _world->CreateEntity(6);
    size_t i = 0;
    for (auto ship : starship) {
        ship->assign<PlayerComponent>();

        int yy = 3;
        yy += i * 17;
        std::vector<sf::IntRect> frame = {
            sf::IntRect(1, yy, 32, 14),
            sf::IntRect(34, yy, 32, 14),
            sf::IntRect(67, yy, 32, 14),
            sf::IntRect(100, yy, 32, 14),
            sf::IntRect(133, yy, 32, 14),
            sf::IntRect(100, yy, 32, 14),
            sf::IntRect(67, yy, 32, 14),
            sf::IntRect(34, yy, 32, 14),
        };
        #ifndef SERVER
            if (GameEngine::GetInstance().getClient().getClientHash() == "me") {
                frame = {
                    sf::IntRect(1, 3, 32, 14),
                    sf::IntRect(1, 20, 32, 14),
                    sf::IntRect(1, 37, 32, 14),
                    sf::IntRect(1, 54, 32, 14),
                };
            }
        #else
        #endif
        
        ship->assign<AnimationComponent>(frame, 0.1f);
        ship->assign<InputComponent>(input);
        ship->assign<PvComponent>(100.f, 100.f);
        ship->assign<DrawableComponent>("./assets/player.png", _infoPlayers[i % _infoPlayers.size()]);
        ship->assign<VelocityComponent>(0.1f, 0.1f);
        const float x = -400;
        const float y = -400;
        ship->assign<TransformComponent>(sf::Vector2f(x, y), sf::Vector2f(4.f, 4.f), 0.f);
        ship->assign<CollisionComponent>(sf::FloatRect(400, 400, 32 * 4,14 * 4), ECS::Collision::PLAYER);
        ship->assign<OnDie>(checkPlayerEnd);
        auto data = ship->assign<DataComponent>();
        data->set("spawn", 0.f);
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
    #ifndef SERVER
        delete _buffer;
        delete _sound;
        delete _music;
    #endif
}

void FirstLevel::update(const float dt)
{
    static sf::Clock clock;
    static sf::Clock enemySpawnClock;

    auto level = _world->GetEntitiesByTag<LevelTag>()[0];
    auto data = level->get<DataComponent>();
    bool schwarziSpawned = data->get<float>("schwarziSpawned");
    bool fliesSpawned = data->get<float>("fliesSpawned");
    bool bossSpawned = data->get<float>("bossSpawned");

    if (clock.getElapsedTime().asSeconds() > 0.1) {
        BackgroundParallax();
		clock.restart();
	}
    if (!schwarziSpawned && enemySpawnClock.getElapsedTime().asSeconds() > 3.0f) {
        data->set("schwarziSpawned", 1.f);
        CreateEnemies(0, 800, 100);
        CreateEnemies(0, 800, 350);
        CreateEnemies(0, 800, 600);
        enemySpawnClock.restart();
    }
    if (!fliesSpawned && schwarziSpawned && enemySpawnClock.getElapsedTime().asSeconds() > 13.0f) {
        data->set("fliesSpawned", 1.f);
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
    if (fliesSpawned && enemySpawnClock.getElapsedTime().asSeconds() > 30.0f && bossSpawned == false) {
        CreateEnemies(2, 900, 200);
        data->set("bossSpawned", 1.f);
    }

    std::vector<ECS::Entity*> Enemy = _world->GetEntitiesByTag<EnemyTag>();
    for (auto enemy : Enemy) {
        auto dataComponentEnemy = enemy->get<DataComponent>();
        if (!dataComponentEnemy)
            continue;
        auto timeShoot = dataComponentEnemy->get<float>("timeShoot");
        timeShoot += dt;
        dataComponentEnemy->set("timeShoot", timeShoot);
    }

    // spawn player
    std::vector<ECS::Entity*> players = {};
    _world->each<PlayerComponent>([&](ECS::Entity* ent, PlayerComponent* player) {
        players.push_back(ent);
    });
    for (auto player : players) {
        if (player->get<PlayerComponent>()->hash == "")
            continue;
        auto dataComponentPlayer = player->get<DataComponent>();
        if (!dataComponentPlayer)
            continue;
        if (dataComponentPlayer->get<float>("spawn") == 1.0f)
            continue;
        auto transform = player->get<TransformComponent>();
        auto velocity = player->get<VelocityComponent>();
        if (!transform || !velocity)
            continue;
        transform->position = sf::Vector2f(200, 200);
        velocity->velocity = sf::Vector2f(0.f, 0.f);
        dataComponentPlayer->set("spawn", 1.0f);
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
        enemy->assign<DataComponent>();
        enemy->assign<VelocityComponent>(0.f, 0.f);
        
        if (id == 2)
            enemy->assign<OnDie>(victory);
        if (id == 1) {
            std::vector<sf::IntRect> anims = {
                sf::IntRect(5, 6, 21, 24),
                sf::IntRect(38, 6, 21, 24),
                sf::IntRect(71, 6, 21, 24),
                sf::IntRect(104, 6, 21, 24),
                sf::IntRect(137, 6, 21, 24),
                sf::IntRect(170, 6, 21, 24),
                sf::IntRect(203, 6, 21, 24),
                sf::IntRect(236, 6, 21, 24),
            };
            enemy->assign<AnimationComponent>(anims, 0.2f);
            enemy->assign<EnemyPath>(EnemyPathType::FOLLOW_PATH);
        } else if (id == 0) {
            enemy->assign<EnemyPath>(EnemyPathType::FOLLOW_PLAYER);
        } else if (id == 2) {
            enemy->assign<EnemyPath>(EnemyPathType::FOLLOW_PLAYER_BOSS);
        }
}

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

