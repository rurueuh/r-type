#pragma once

#include "Entity/Entity.hpp"
#include "Utils/Utils.hpp"
#include <functional>
#include <algorithm>
#include "System.hpp"
#include "SFML.hpp"
#include "Component.hpp"

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

			std::vector<Entity*> CreateEntity(int nb);

			/**
			 * @brief make a call with function with all entity has the component in template.
			 * @brief world->each<PositionComponent>([&](ECS::Entity* ent, PositionComponent *position) {position->y += 1;});
			 */
			template<typename T>
			void each(std::function<void(Entity*, T *)> f) {
				int i = 0;
				for (; i < m_entities.size(); i++) {
					if (m_entities[i]->has<T>()) {
						auto* comp = m_entities[i]->get<T>();
						f(m_entities[i], comp);
					}
				}
				/*for (auto& ent : m_entities) {
					if (ent->has<T>()) {
						auto* comp = ent->get<T>();
						f(ent, comp);
					}
				}*/
			};

			/**
			 * @brief make a call with function with all entity.
			 * @brief world->all([](ECS::Entity* ent) {...});
			 */
			void all(std::function<void(Entity*)> f) {
				std::for_each(m_entities.begin(), m_entities.end(), f);
			}

			/**
			 * @brief make all "tick" of all system register
			 * @arg (optional) float dt | if not give automatic override it with dt
			*/
			void tick(float dt = 0);

			/**
			 * @brief add a system to system list to update (use tick funct and need to herit from BaseSystem.
			 * @param priority order to execute if dupplicate prio throw exception
			 */
			template <typename T, typename... Args>
			bool registerSystem(size_t priority, Args&&... args){
				BaseSystem* newRegister = new T(std::forward<Args>(args)...);
				if (m_system[priority] != nullptr) {
					throw std::runtime_error("double insert system priority");
					return true;
				}
				else {
					m_system[priority] = newRegister;
				}
				return false;
			}

			std::vector<Entity*> getEntities() { return m_entities; };
			void setEntities(std::vector<Entity*> entities) { m_entities = entities; };

			template <typename T>
			std::vector<Entity*> GetEntitiesByTag(void) {
				std::vector<Entity*> entities = {};
				for (auto& ent : m_entities) {
					if (ent->has<T>()) {
						entities.push_back(ent);
					}
				}
				return entities;
			}
		private:
			World() {};
			~World() {
				for (auto& sys : m_system) {
					delete sys.second;
				}
			};

			void updateWorld(void);

			std::vector<Entity*> m_entities = std::vector<Entity*>();
			std::unordered_map<size_t, BaseSystem*> m_system = std::unordered_map<size_t, BaseSystem*>();
	};
}
