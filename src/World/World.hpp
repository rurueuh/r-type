#pragma once

#include "Entity/Entity.hpp"
#include "Utils/Utils.hpp"
#include <functional>
#include <algorithm>

class ComponentHandler;

namespace ECS {
	class World
	{
		public:
			/*
			* @brief Creates a new world
			* @return A pointer to the new world
			*/
			static World* CreateWorld();

			/**
			 * @brief Destroys the world
			 */
			void destroyWorld();

			Entity* getEntity(size_t id) { return m_entities[id]; };

			/**
			 * @brief Create an entity to the world
			 */
			Entity* CreateEntity();

			/**
			 * @brief make a call with function with all entity has the component in template.
			 * @brief world->each<PositionComponent>([&](ECS::Entity* ent, PositionComponent *position) {position->y += 1;});
			 */
			template<typename T>
			void each(std::function<void(Entity*, T *)> f) {
				for (auto& ent : m_entities) {
					if (ent->has<T>()) {
						auto* comp = ent->get<T>();
						f(ent, comp);
					}
				}
			};

			/**
			 * @brief make a call with function with all entity.
			 * @brief world->all([](ECS::Entity* ent) {...});
			 */
			void all(std::function<void(Entity*)> f) {
				std::for_each(m_entities.begin(), m_entities.end(), f);
			}
		private:
			World() {};
			~World() {};

			std::vector<Entity*> m_entities = std::vector<Entity*>();
	};
}
