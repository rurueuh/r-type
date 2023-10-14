#pragma once

#include "ComponentBase.hpp"

#include "PvComponent.hpp"
#include "PlayerInputComponent.hpp"

#include "Utils.hpp"
#include "Entity.hpp"

namespace ECS {
	class Entity;
	namespace Component {

		void FactoryAssignPvComponent(Entity* ent, std::string type, std::string str);
		void FactoryAssignPlayerInputComponent(Entity* ent, std::string type, std::string str);

		// template Args...
		void FactoryAssignComponent(Entity* ent, std::string type, std::string str = "");
	};
};
