#pragma once

#include "ComponentBase.hpp"
#include "PvComponent.hpp"
#include "Utils.hpp"
#include "Entity.hpp"

namespace ECS {
	class Entity;
	namespace Component {

		void FactoryAssignPvComponent(Entity* ent, std::type_index index, std::string str);

		// template Args...
		void FactoryAssignComponent(Entity* ent, std::type_index index, std::string str = "");
	};
};
