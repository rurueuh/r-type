#include "TestSystem.hpp"
#include "World.hpp"
#include "PvComponent.hpp"
#include "SFML.hpp"

void TestSystem::tick(ECS::World* world, const float& dt)
{
	world->each<PvComponent>([](ECS::Entity &ent, PvComponent* pv) {
		if (pv->health <= 0) {
			ent.die();
		}
		std::cout << "hp : " << pv->health-- << std::endl;
	});
}
