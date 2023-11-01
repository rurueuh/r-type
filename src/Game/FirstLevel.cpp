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