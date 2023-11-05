#include "Component.hpp"
#include "Entity.hpp"
#include <map>
#include <functional>

void ECS::Component::FactoryAssignComponent(Entity* ent, std::string type, std::string str) {
	type.erase(std::remove_if(type.begin(), type.end(), isspace), type.end());
	std::map<std::string, std::function<void(Entity*, std::string, std::string)>> list = {
		{Utils::getRegisteredComponent(Utils::getTypeId<PvComponent>()), FactoryAssignCreateComponent<PvComponent>},
		{Utils::getRegisteredComponent(Utils::getTypeId<InputComponent>()), FactoryAssignCreateComponent<InputComponent>},
		{Utils::getRegisteredComponent(Utils::getTypeId<DrawableComponent>()), FactoryAssignCreateComponent<DrawableComponent>},
		{Utils::getRegisteredComponent(Utils::getTypeId<TransformComponent>()), FactoryAssignCreateComponent<TransformComponent>},
		{Utils::getRegisteredComponent(Utils::getTypeId<Hitbox>()), FactoryAssignCreateComponent<Hitbox>},
		{Utils::getRegisteredComponent(Utils::getTypeId<PlayerComponent>()), FactoryAssignCreateComponent<PlayerComponent>},
		{Utils::getRegisteredComponent(Utils::getTypeId<WeaponComponent>()), FactoryAssignCreateComponent<WeaponComponent>},
		{Utils::getRegisteredComponent(Utils::getTypeId<ShootComponent>()), FactoryAssignCreateComponent<ShootComponent>},
		{Utils::getRegisteredComponent(Utils::getTypeId<EnemyTag>()), FactoryAssignCreateComponent<EnemyTag>},
		{Utils::getRegisteredComponent(Utils::getTypeId<BackgroundTag>()), FactoryAssignCreateComponent<BackgroundTag>},
		{Utils::getRegisteredComponent(Utils::getTypeId<VelocityComponent>()), FactoryAssignCreateComponent<VelocityComponent>},
		{Utils::getRegisteredComponent(Utils::getTypeId<LifeSpan>()), FactoryAssignCreateComponent<LifeSpan>},
		{Utils::getRegisteredComponent(Utils::getTypeId<OnDie>()), FactoryAssignCreateComponent<OnDie>},
		{Utils::getRegisteredComponent(Utils::getTypeId<CollisionComponent>()), FactoryAssignCreateComponent<CollisionComponent>},
		{Utils::getRegisteredComponent(Utils::getTypeId<TextComponent>()), FactoryAssignCreateComponent<TextComponent>},
		{Utils::getRegisteredComponent(Utils::getTypeId<EnemyPath>()), FactoryAssignCreateComponent<EnemyPath>},
		{Utils::getRegisteredComponent(Utils::getTypeId<DataComponent>()), FactoryAssignCreateComponent<DataComponent>},
		{Utils::getRegisteredComponent(Utils::getTypeId<LevelTag>()), FactoryAssignCreateComponent<LevelTag>},
		{Utils::getRegisteredComponent(Utils::getTypeId<AnimationComponent>()), FactoryAssignCreateComponent<AnimationComponent>},
	};

	if (list.find(type) != list.end()) {
		list[type](ent, type, str);
	} else {
		std::cerr << "Component " << type << " not found" << std::endl;
	}	

}