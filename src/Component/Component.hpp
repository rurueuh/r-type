/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-1-rtype-maximilien.vanstaevel
** File description:
** Component
*/

#pragma once

#include "ComponentBase.hpp"

#include "PvComponent.hpp"
#include "PlayerInputComponent.hpp"
#include "ColliderComponent.hpp"
#include "DamageComponent.hpp"
#include "DrawableComponent.hpp"
#include "TransformComponent.hpp"
#include "PositionComponent.hpp"
#include "Utils.hpp"
#include "Entity.hpp"

namespace ECS {
	class Entity;
	namespace Component {

		void FactoryAssignPvComponent(Entity* ent, std::string type, std::string str);
		void FactoryAssignPlayerInputComponent(Entity* ent, std::string type, std::string str);
		void FactoryAssignDrawableComponent(Entity* ent, std::string type, std::string str);
		void FactoryAssignTransformComponent(Entity* ent, std::string type, std::string str);

		// template Args...
		void FactoryAssignComponent(Entity* ent, std::string type, std::string str = "");
	};
};
