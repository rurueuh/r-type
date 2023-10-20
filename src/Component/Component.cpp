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

void ECS::Component::FactoryAssignPlayerInputComponent(Entity* ent, std::string type, std::string data) {
	auto id = Utils::getRegisteredComponent(Utils::getTypeId<InputComponent>());
	if (type == id) {
		auto playerInput = ent->assign<InputComponent>();
		playerInput->fromString(data);
	}
}

void ECS::Component::FactoryAssignDrawableComponent(Entity* ent, std::string type, std::string data) {
	auto id = Utils::getRegisteredComponent(Utils::getTypeId<DrawableComponent>());
	if (type == id) {
		auto sprite = ent->assign<DrawableComponent>();
		sprite->fromString(data);
	}
}

void ECS::Component::FactoryAssignTransformComponent(Entity* ent, std::string type, std::string data) {
	auto id = Utils::getRegisteredComponent(Utils::getTypeId<TransformComponent>());
	if (type == id) {
		auto transform = ent->assign<TransformComponent>();
		transform->fromString(data);
	}
}

void ECS::Component::FactoryAssignComponent(Entity* ent, std::string type, std::string str) {
	// remove useless space in type
	type.erase(std::remove_if(type.begin(), type.end(), isspace), type.end());
	std::vector<std::function<void(Entity*, std::string, std::string)>> funcs = {
		FactoryAssignPvComponent,
		FactoryAssignPlayerInputComponent,
		FactoryAssignDrawableComponent,
		FactoryAssignTransformComponent
	};
	std::vector<std::string> id = {
		Utils::getRegisteredComponent(Utils::getTypeId<PvComponent>()),
		Utils::getRegisteredComponent(Utils::getTypeId<InputComponent>()),
		Utils::getRegisteredComponent(Utils::getTypeId<DrawableComponent>()),
		Utils::getRegisteredComponent(Utils::getTypeId<TransformComponent>())
	};
	// pour une raison inconnue (probablement le combo unordered_map + std::function) je ne peux pas cree de map
	for (size_t i = 0; i < id.size(); i++) {
		if (type == id[i]) {
			funcs[i](ent, type, str);
		}
	}
}
