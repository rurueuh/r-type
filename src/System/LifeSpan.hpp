#pragma once

#include "System.hpp"
#include "Component.hpp"
#include "GameEngine.hpp"


namespace ECS {
    namespace System {
        class LifeSpanSystem : public ECS::BaseSystem {
        public:
            LifeSpanSystem() = default;
            ~LifeSpanSystem() = default;

            virtual void tick(ECS::World* world, const float& dt) override {
                world->each<LifeSpan>([&](ECS::Entity* ent, LifeSpan* lifeSpan) {
                    lifeSpan->_time -= dt;
                    if (lifeSpan->_time <= 0) {
						ent->die();
					}
                });
            }
        private:
        };
    }
}