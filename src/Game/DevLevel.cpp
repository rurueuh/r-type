#include "DevLevel.hpp"
#include "Component.hpp"
#include "GameEngine.hpp"
#include "World.hpp"
#include "Entity.hpp"

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
    if (!velocity)
        bullet->assign<VelocityComponent>(620.f, 0.f);
    else
        bullet->assign<VelocityComponent>(620.f + (velocity->velocity.x), 0.f + (velocity->velocity.y));
}

DevLevel::DevLevel() : Level()
{
    const std::unordered_map<Input::Key, std::function<void(ECS::Entity*, const float&)>> input = {
        { Input::Key::forward, forward},
        { Input::Key::backward, backward},
		{ Input::Key::left, left},
		{ Input::Key::right, right},
        { Input::Key::jump, shoot}
    };
    std::vector<ECS::Entity*> starship = _world->CreateEntity(2);
    for (auto ship : starship) {
        ship->assign<PlayerComponent>();
        ship->assign<InputComponent>(input);
        ship->assign<PvComponent>(100);
        ship->assign<DrawableComponent>("../assets/player.png", sf::IntRect(1, 3, 32, 14));
        ship->assign<VelocityComponent>(0.1f, 0.1f);
        const float x = 400;
        const float y = 400;
        ship->assign<TransformComponent>(sf::Vector2f(x, y), sf::Vector2f(4.f, 4.f), 0.f);
    }
    #ifndef SERVER
        starship[0]->get<PlayerComponent>()->hash = "me";
    #endif // SERVER

    try {
        _world->registerSystem<ECS::System::TransformSystem>(0);
        _world->registerSystem<ECS::System::DrawableSystem>(1);
        _world->registerSystem<ECS::System::InputSystem>(2);
        _world->registerSystem<ECS::System::VelocitySystem>(3);
        _world->registerSystem<ECS::System::LifeSpanSystem>(4);
        _world->registerSystem<ECS::System::HpSystem>(5);
    } catch (const std::exception &e) {
        std::cout << "ERROR : " << e.what() << std::endl;
    }
}

DevLevel::~DevLevel()
{
}

void DevLevel::update(const float dt)
{
    static sf::Clock clock;
    if (clock.getElapsedTime().asSeconds() > 0.001) {
		clock.restart();
        _world->each<PvComponent>([&](ECS::Entity* ent, PvComponent* pv) {
		});
        _world->each<TransformComponent>([&](ECS::Entity* ent, TransformComponent* transform) {
            //transform->position.x += 1;
            if (transform->position.x > 1800) {
				transform->position.x = 0;
			}
        });
	}
}
