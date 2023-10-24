#include "Component.hpp"
#include "Entity.hpp"
#include <map>
#include <functional>

void ECS::Component::FactoryAssignComponent(Entity* ent, std::string type, std::string str) {
	// remove useless space in type
	type.erase(std::remove_if(type.begin(), type.end(), isspace), type.end());
	std::vector<std::function<void(Entity*, std::string, std::string)>> funcs = {
		FactoryAssignCreateComponent<PvComponent>,
		FactoryAssignCreateComponent<InputComponent>,
		FactoryAssignCreateComponent<DrawableComponent>,
		FactoryAssignCreateComponent<TransformComponent>,
		FactoryAssignCreateComponent<PlayerComponent>,
		FactoryAssignCreateComponent<VelocityComponent>
	};
	std::vector<std::string> id = {
		Utils::getRegisteredComponent(Utils::getTypeId<PvComponent>()),
		Utils::getRegisteredComponent(Utils::getTypeId<InputComponent>()),
		Utils::getRegisteredComponent(Utils::getTypeId<DrawableComponent>()),
		Utils::getRegisteredComponent(Utils::getTypeId<TransformComponent>()),
		Utils::getRegisteredComponent(Utils::getTypeId<PlayerComponent>()),
		Utils::getRegisteredComponent(Utils::getTypeId<VelocityComponent>())
	};
	// pour une raison inconnue (probablement le combo unordered_map + std::function) je ne peux pas cree de map
	for (size_t i = 0; i < id.size(); i++) {
		if (type == id[i]) {
			funcs[i](ent, type, str);
			return;
		}
		if (i == id.size() - 1) {
			std::cerr << "ERROR : Component " << type << " not found" << std::endl;
		}
	}
}
