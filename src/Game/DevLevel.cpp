#include "DevLevel.hpp"
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

DevLevel::DevLevel() : Level()
{
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
		{ {ECS::Collision::BULLET_PLAYER, ECS::Collision::WALL}, collisionBulletWall }
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
    std::vector<ECS::Entity*> starship = _world->CreateEntity(6);
    size_t i = 0;
    for (auto ship : starship) {
        ship->assign<PlayerComponent>();
        ship->assign<InputComponent>(input);
        ship->assign<PvComponent>(100.f, 100.f);
        ship->assign<DrawableComponent>("../assets/player.png", _infoPlayers[i % _infoPlayers.size()]);
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
    static sf::Clock clock;
    if (clock.getElapsedTime().asSeconds() > 0.1) {
        BackgroundParallax();
        std::cout << dt << std::endl;
        _world->each<PvComponent>([&](ECS::Entity* ent, PvComponent* pv) {
            pv->_health -= 1.f * dt * 1000.f;
		});
		clock.restart();
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
    for (int i = 0; i < _infoBackgrounds.size(); i++) {
        auto& e = _backgrounds[i * 2];
        auto& e2 = _backgrounds[i * 2 + 1];

        auto t = e->get<VelocityComponent>();
        auto t2 = e2->get<VelocityComponent>();

        t->velocity = sf::Vector2f(_infoBackgrounds[i].speed, 0.f);
        t2->velocity = sf::Vector2f(_infoBackgrounds[i].speed, 0.f);
    }
}
