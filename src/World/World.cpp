#include "World.hpp"
#include "GameEngine.hpp"

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

	Entity *World::CreateEntity()
	{
		auto id = Utils::getCounterEntity();
		Entity *entity = new Entity(this, id);
		m_entities.push_back(entity);
		return m_entities.back();
	}

	std::vector<Entity*> World::CreateEntity(int nb)
	{
		std::vector<Entity *> entities;
		for (int i = 0; i < nb; i++) {
			entities.push_back(CreateEntity());
		}
		return entities;
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
		
		for (size_t i = 0; i < m_entities.size(); i++) {
			if (m_entities[i]->isDead()) {
				if (m_entities[i]->has<OnDie>()) {
					m_entities[i]->get<OnDie>()->_onDie(this, m_entities[i]);
				}
				#ifndef SERVER
					auto &engine = GameEngine::GetInstance();
					auto &client = engine.getClient();
					auto hash = client.getClientHash();
					if (hash != "me") { // MULTIPLAYER so delete be do in replication
						return;
					}
				#endif // SERVER
				delete m_entities[i];

				m_entities.erase(m_entities.begin() + i);
			}
		}
	}
};
