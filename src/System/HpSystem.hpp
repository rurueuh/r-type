#pragma once

#include "System.hpp"
#include "Component.hpp"
#include "GameEngine.hpp"


namespace ECS {
    namespace System {
        class HpSystem : public ECS::BaseSystem {
        public:
            HpSystem() = default;
            ~HpSystem() = default;

            virtual void tick(ECS::World* world, const float& dt) override {
                world->each<PvComponent>([&](ECS::Entity* ent, PvComponent* pv) {
                    if (pv->health <= 0) {
				        ent->die();
			        }
		        });
            }
        private:
        };
    }
}