#pragma once

namespace ECS {

	class World;

	class BaseSystem {
	public:
		BaseSystem() = default;
		virtual ~BaseSystem() = default;

		virtual void tick(World* world, const float& dt) {};
	};
}
