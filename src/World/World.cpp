#include "World.hpp"

namespace ECS {
	World* World::CreateWorld()
	{
		auto* world = new World();

		return world;
	}

	void World::destroyWorld()
	{
		delete this;
	}

	Entity* World::CreateEntity()
	{
		auto id = Utils::getCounterEntity();
		auto* entity = new Entity(this, id);
		m_entities.push_back(entity);
		return entity;
	}
};
