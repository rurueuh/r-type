#include "DevLevel.hpp"
#include "Component.hpp"
#include "GameEngine.hpp"
#include "World.hpp"
#include "Entity.hpp"
#include "DeadLevel.hpp"
#include <algorithm>
#include <vector>
#include <numeric>
#include <string_view>
#include <iostream>

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
    bullet->assign<DrawableComponent>("../assets/sheet1.png", sf::IntRect(337, 255, 12, 4));
    bullet->assign<TransformComponent>(transform->position, sf::Vector2f(2.f, 2.f), 0.f);
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
    e1->die();
}

static void collisionBulletAllyToBulletEnemy(ECS::World *world, ECS::Entity *e1, ECS::Entity *e2)
{
	e1->die();
    e2->die();
}

static void collisionBulletAllyToEnemy(ECS::World* world, ECS::Entity* e1, ECS::Entity* e2)
{
	e1->die();
	auto pv = e2->get<PvComponent>();
    if (pv)
		pv->_health -= 20;
}

static void collisionBulletEnemyToPlayer(ECS::World* world, ECS::Entity* e1, ECS::Entity* e2)
{
    e1->die();
    auto pv = e2->get<PvComponent>();
    if (pv)
		pv->_health -= 10;
}

static void checkPlayerEnd(ECS::World* world, ECS::Entity* ent)
{
    #ifndef SERVER
        if (GameEngine::GetInstance().getClient().getClientHash() == "me") {
            auto &levelManager = LevelManager::getInstance();
            levelManager.addLevel<DeadLevel>();
            levelManager.removeLevel<DevLevel>();
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
        levelManager.removeLevel<DevLevel>();
        levelManager.setCurrentLevel<DeadLevel>();

	}
}

static void shootEnemy(ECS::World *world, const float &dt, ECS::Entity *ent)
{
    if (!ent->has<DataComponent>())
        return;
	auto cooldown = ent->get<DataComponent>()->get<float>("timeShoot");
    if (cooldown < 3.5)
        return;
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

DevLevel::DevLevel() : Level()
{
    auto levelEntity = _world->CreateEntity();
    levelEntity->assign<DataComponent>();
    levelEntity->assign<LevelTag>();
    std::sort(_infoEnemy.begin(), _infoEnemy.end(), [](const infoEnemySpawn_t& a, const infoEnemySpawn_t& b) {
        return a.time < b.time;
    });
    auto window = GameEngine::GetInstance().getWindow();
    sf::Vector2u size = { 1600, 900 };
    #ifndef SERVER
        size = window->getSize();
    #endif
    CreateBackground(window, size);
    CreatePlayers();
    auto wall = _world->CreateEntity();
    wall->assign<DrawableComponent>("../assets/player.png", sf::IntRect(1, 3, 32, 14));
    wall->assign<TransformComponent>(sf::Vector2f(600, 600), sf::Vector2f(3.f, 3.f), 0.f);
    wall->assign<CollisionComponent>(sf::FloatRect(600, 600, 32 * 3, 14 * 3), ECS::Collision::WALL);
    CollisionActionList collisionAction = {
        { {ECS::Collision::PLAYER, ECS::Collision::WALL}, collisionPlayerWall},
        { {ECS::Collision::BULLET_PLAYER, ECS::Collision::WALL}, collisionBulletWall },
        { {ECS::Collision::BULLET_PLAYER, ECS::Collision::ENEMY }, collisionBulletAllyToEnemy },
        { {ECS::Collision::BULLET_ENEMY, ECS::Collision::BULLET_PLAYER}, collisionBulletAllyToBulletEnemy },
		//{ {ECS::Collision::BULLET_ENEMY, ECS::Collision::WALL}, collisionBulletWall },
		{ {ECS::Collision::BULLET_ENEMY, ECS::Collision::PLAYER}, collisionBulletEnemyToPlayer },
	};
    ECS::System::Path::ShootPathType typeOfShoot = {
        { FOLLOW_PLAYER, shootEnemy }
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

void DevLevel::CreatePlayers()
{
    const std::unordered_map<Input::Key, std::function<void(ECS::Entity*, const float&)>> input = {
        { Input::Key::forward, forward },
        { Input::Key::backward, backward },
        { Input::Key::left, left },
        { Input::Key::right, right },
        { Input::Key::jump, shoot }
    };
    shoot(nullptr, 0.f); // for start cooldown shoot
    std::vector<ECS::Entity*> starship = _world->CreateEntity(4);
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
        ship->assign<DrawableComponent>("../assets/player.png", _infoPlayers[i % _infoPlayers.size()]);
        ship->assign<VelocityComponent>(0.1f, 0.1f);
        const float x = -800;
        const float y = -800;
        ship->assign<TransformComponent>(sf::Vector2f(x, y), sf::Vector2f(4.f, 4.f), 0.f);
        ship->assign<CollisionComponent>(sf::FloatRect(x, y, 32 * 4,14 * 4), ECS::Collision::PLAYER);
        ship->assign<OnDie>(checkPlayerEnd);
        auto d = ship->assign<DataComponent>();
        d->set("spawn", 0.f);
        i++;
    }
#ifndef SERVER
    starship[0]->get<PlayerComponent>()->hash = "me";
    starship[0]->get<TransformComponent>()->position = sf::Vector2f(200, 200);
    starship[0]->get<CollisionComponent>()->_rect = sf::FloatRect(200, 200, 32 * 4, 14 * 4);
    starship[0]->get<DataComponent>()->set("spawn", 1.f);

#endif // SERVER
}

void DevLevel::CreateBackground(sf::RenderWindow* window, sf::Vector2u& size)
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

DevLevel::~DevLevel()
{
}

void DevLevel::update(const float dt)
{
    std::vector<ECS::Entity*> data = _world->GetEntitiesByTag<LevelTag>();
    if (data.size() == 0)
        return;
    auto dataComponentLevel = data[0]->get<DataComponent>();

    static sf::Clock clock;
    std::vector<ECS::Entity*> Enemy = _world->GetEntitiesByTag<EnemyTag>();
    for (auto enemy : Enemy) {
        auto dataComponentEnemy = enemy->get<DataComponent>();
        if (!dataComponentEnemy)
            continue;
        auto timeShoot = dataComponentEnemy->get<float>("timeShoot");
        timeShoot += dt;
        dataComponentEnemy->set("timeShoot", timeShoot);
    }
    if (clock.getElapsedTime().asSeconds() > 0.1) {
        BackgroundParallax();
		clock.restart();
	}
    // Spawn enemy
    auto time = _clockEnemy.getElapsedTime().asSeconds();
    #ifndef SERVER
        {
            auto players = _world->GetEntitiesByTag<PlayerComponent>();
            if (players[0]->get<PlayerComponent>()->hash == "me")
                dataComponentLevel->set("timeLevel", time);
        }
        time = dataComponentLevel->get<float>("timeLevel");
    #else
        dataComponentLevel->set("timeLevel", time);
    #endif
    std::size_t i = 0;
    for (; i < _infoEnemy.size(); i++) {
        auto info = _infoEnemy[i];
        if (info.time <= time) {
            auto enemy = _world->CreateEntity();
            enemy->assign<DataComponent>();
            enemy->assign<DrawableComponent>("../assets/enemy.png", sf::IntRect(5, 6, 21, 24));
            enemy->assign<TransformComponent>(info.position, sf::Vector2f(2.f, 2.f), 0.f);
            enemy->assign<CollisionComponent>(sf::FloatRect(800, 400, 21 * 2, 24 * 2), ECS::Collision::ENEMY);
            enemy->assign<VelocityComponent>(0.1f, 0.1f);
            enemy->assign<PvComponent>(info.hp, info.hp);
            enemy->assign<EnemyTag>();
            enemy->assign<EnemyPath>(FOLLOW_PLAYER);
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
            std::remove(_infoEnemy.begin(), _infoEnemy.end(), info);
            break;
        }
    }
    if (_infoEnemy.size() == 0) {
        std::vector<ECS::Entity *> enemies = {};
        _world->each<EnemyTag>([&](ECS::Entity *ent, EnemyTag *tag) {
            enemies.push_back(ent);
        });
        if (enemies.size() == 0) {
            std::cout << "All enemy are dead" << std::endl;
            auto &levelManager = LevelManager::getInstance();
            levelManager.addLevel<DeadLevel>();
            levelManager.removeLevel<DevLevel>();
            levelManager.setCurrentLevel<DeadLevel>();
        }
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
