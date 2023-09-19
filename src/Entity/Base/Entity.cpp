#include "Entity.hpp"
#include "Component.hpp"

void Entity::EntityUpdate(float dt)
{
	for (auto& comp : _components)
	{
		comp->CompenantUpdate(dt);
	}
	update(dt);
}

void Entity::EntityDraw(sf::RenderTarget& window)
{
	for (auto& comp : _components)
	{
		comp->CompenantDraw(window);
	}
	draw(window);
}