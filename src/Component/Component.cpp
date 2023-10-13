#include "Component.hpp"
#include "Entity.hpp"
#include <map>
#include <functional>

void ECS::Component::FactoryAssignPvComponent(Entity* ent, std::string type, std::string data) {
	auto id = Utils::getRegisteredComponent(Utils::getTypeId<PvComponent>());
	if (type == id) {
		auto pv = ent->assign<PvComponent>();
		pv->fromString(data);
	}
}

void ECS::Component::FactoryAssignComponent(Entity* ent, std::string type, std::string str) {
	// remove useless space in type
	type.erase(std::remove_if(type.begin(), type.end(), isspace), type.end());
	std::vector<std::function<void(Entity*, std::string, std::string)>> funcs = {
		FactoryAssignPvComponent
	};
	std::vector<std::string> id = {
		Utils::getRegisteredComponent(Utils::getTypeId<PvComponent>())
	};
	// pour une raison inconnue (probablement le combo unordered_map + std::function) je ne peux pas cree de map
	for (size_t i = 0; i < id.size(); i++) {
		if (type == id[i]) {
			funcs[i](ent, type, str);
		}
	}
}
