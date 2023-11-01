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
                    if (pv->_health <= 0) {
				        ent->die();
			        } else if (pv->_health > pv->_maxHealth) {
				        pv->_health = pv->_maxHealth;
			        }
		        });
            }
        private:
        };
    }
}