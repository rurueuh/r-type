#pragma once

#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <vector>
#include "Utils/Utils.hpp"
#include <any>
#include <iostream>
#include <string>
#include <sstream>
#include "Utils/Utils.hpp"
#include <iostream>
#include <type_traits>
#include "ComponentBase.hpp"

namespace InternalECS {
	class World;
	class Entity;

	class ComponentHandler {
	public:
		std::unordered_map<std::type_index, std::vector<Component *>> components = std::unordered_map<std::type_index, std::vector<Component *>>();
		std::unordered_map<void*, std::vector<std::type_index>> entities;

		template <typename T, typename... Args>
		T* assignComponent(void* entity, Args&&... args) {
			T* component = new T(std::forward<Args>(args)...);
			components[Utils::getTypeId<T>()].push_back(component);
			entities[entity].push_back(Utils::getTypeId<T>());
			return component;
		}

		~ComponentHandler() {
			for (auto& pair : components) {
				for (Component* component : pair.second) {
					delete component;
				}
			}
		}

	private:
	};
}


namespace ECS {

	class World;

	class 
	Entity
	{
	public:
		friend class World;


		Entity(World* world, size_t id) : m_world(world), m_id(id) {}
		~Entity() {
			if (handler != nullptr) {
				delete handler;
			}
		}

		World* getWorld() const { return m_world; }
		size_t getId() const { return m_id; }

		void assingWorld(World* world) { m_world = world; };

		template <typename T, typename... Args>
		T* assign(Args&&... args) {
			return handler->assignComponent<T>(this, std::forward<Args>(args)...);
		}

		template <typename T>
		T* get() {
			auto& components = handler->components[Utils::getTypeId<T>()];
			for (void* component : components) {
				if (component != nullptr) {
					return static_cast<T*>(component);
				}
			}
			return nullptr;
		}

		template <typename T>
		bool has() {
			auto& components = handler->components[Utils::getTypeId<T>()];
			if (components == std::vector<Component *>())
				return false;
			return true;
		}

		void die(bool force = false) { // TODO: add force dead to remove in m_world
			this->m_WaitingForDestroy = true;
		}

		bool isDead() { return m_WaitingForDestroy; };
		
		std::string serialise(void);

	private:
			InternalECS::ComponentHandler *handler = new InternalECS::ComponentHandler();
			World *m_world = nullptr;
			size_t m_id = -1;
			bool m_WaitingForDestroy = false;
	};
}
