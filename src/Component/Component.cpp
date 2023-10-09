#include "Component.hpp"
#include "Entity.hpp"
#include <map>
#include <functional>

void ECS::Component::FactoryAssignPvComponent(Entity* ent, std::type_index index, std::string str) {
	auto id = Utils::getTypeId<PvComponent>();
	if (index == id) {
		ent->assign<PvComponent>();
	}
}

void ECS::Component::FactoryAssignComponent(Entity* ent, std::type_index index, std::string str) {
	std::vector<std::function<void(Entity*, std::type_index, std::string)>> funcs = {
		FactoryAssignPvComponent
	};
	std::vector<std::type_index> id = {
		Utils::getTypeId<PvComponent>()
	};
	// pour une raison inconnue (probablement le combo unordered_map + std::function) je ne peux pas cr�e de map

	for (size_t i = 0; i < id.size(); i++) {
		if (index == id[i]) {
			funcs[i](ent, index, str);
		}
	}
}
