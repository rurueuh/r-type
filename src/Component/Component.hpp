/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** Component
*/

#pragma once

#include "ComponentBase.hpp"

#include "PvComponent.hpp"
#include "PlayerComponent.hpp"
#include "InputComponent.hpp"
#include "CollisionComponent.hpp"
#include "DamageComponent.hpp"
#include "DrawableComponent.hpp"
#include "TransformComponent.hpp"
#include "PositionComponent.hpp"
#include "HitboxComponent.hpp"
#include "ShootComponent.hpp"
#include "WeaponComponent.hpp"
#include "EnemyTag.hpp"
#include "BackgroundTag.hpp"
#include "VelocityComponent.hpp"
#include "LifeSpan.hpp"
#include "OnDie.hpp"
#include "TextComponent.hpp"
#include "EnemyPath.hpp"
#include "dataComponent.hpp"
#include "LevelTag.hpp"
#include "AnimationComponent.hpp"
#include "PatternComponent.hpp"

#include "Utils.hpp"
#include "Entity.hpp"

namespace ECS {
	class Entity;
	namespace Component {
		/**
		 * @brief Factory for component
		*/
		template <typename T>
		void FactoryAssignCreateComponent(Entity* ent, std::string type, std::string str) {
			auto id = Utils::getRegisteredComponent(Utils::getTypeId<T>());
			if (type == id) {
				auto component = ent->assign<T>();
				component->fromString(str);
			}
		}

		/**
		 * @brief Factory for component
		*/
		void FactoryAssignComponent(Entity* ent, std::string type, std::string str = "");
		
	};
};
