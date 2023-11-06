#pragma once

#include "System.hpp"
#include "Component.hpp"
#include "GameEngine.hpp"


namespace ECS {
    namespace System {
        class AnimationSystem : public ECS::BaseSystem {
        public:
            AnimationSystem() = default;
            ~AnimationSystem() = default;

            virtual void tick(ECS::World* world, const float& dt) override {
                world->each<AnimationComponent>([&](ECS::Entity* ent, AnimationComponent* anim) {
                    anim->clockTime += dt;
                    if (anim->clockTime >= anim->timeSwitch) {
                        anim->clockTime = 0.f;
                        anim->actualFrame++;
                        if (anim->actualFrame >= anim->animFrame.size()) {
                            anim->actualFrame = 0;
                        }
                    }

                    auto drawable = ent->get<DrawableComponent>();
                    if (drawable) {
                    #ifndef SERVER
                        drawable->sprite.setTextureRect(anim->animFrame[anim->actualFrame]);
                    #endif
                        drawable->area = anim->animFrame[anim->actualFrame];
                    }
		        });
            }
        private:
        };
    }
}