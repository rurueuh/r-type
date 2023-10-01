#pragma once

#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include "Utils/Utils.hpp"


namespace InternalECS {
	class World;
	class Entity;

	class ComponentHandler {
	public:
		std::unordered_map<std::type_index, std::vector<void*>> components;

		template <typename T, typename... Args>
		T* assignComponent(void* entity, Args&&... args) {
			T* component = new T(std::forward<Args>(args)...);
			components[Utils::getTypeId<T>()].push_back(component);
			entities[entity].push_back(Utils::getTypeId<T>());
			return component;
		}

		~ComponentHandler() {
			for (auto& pair : components) {
				for (void* component : pair.second) {
					delete component;
				}
			}
		}

	private:
		std::unordered_map<void*, std::vector<std::type_index>> entities;


	};;
}


namespace ECS {

	class World;

	class Entity
	{
	public:
		friend class World;


		Entity(World* world, size_t id) : m_world(world), m_id(id) {}
		~Entity() = default;

		World* getWorld() const { return m_world; }
		size_t getId() const { return m_id; }

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
			if (components == std::vector<void*>())
				return false;
			return true;
		}
		

	private:
			InternalECS::ComponentHandler *handler = new InternalECS::ComponentHandler();
			World *m_world = nullptr;
			size_t m_id = -1;
			bool m_WaitingForDestroy = false;
	};
}
