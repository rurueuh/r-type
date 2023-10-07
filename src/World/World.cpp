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


	/**
	* @brief make all "tick" of all system register
	* @arg (optional) float dt | if not give automatic override it with dt
	*/
	void World::tick(float dt) {
		if (dt == 0) { // automatic get ms of tick
			static sf::Clock clock;
			auto time = clock.getElapsedTime().asSeconds();
			dt = time;
			clock.restart();
		}
		for (auto& sys : m_system) {
			sys.second->tick(this, dt);
		}
		updateWorld();
	}

	void World::updateWorld(void)
	{
		for (auto& ent : m_entities) {
			if (ent->isDead()) {
				(void)std::remove(m_entities.begin(), m_entities.end(), ent);
				std::cout << "a entity die" << std::endl;
			}
		}
	}
};
