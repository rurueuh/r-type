#pragma once

#include "System.hpp"
#include "Component.hpp"
#include "GameEngine.hpp"

typedef std::function<void(ECS::World*, ECS::Entity* e1, ECS::Entity* e2)> CollisionAction;
typedef std::pair<ECS::Collision::CollisionType, ECS::Collision::CollisionType> CollisionActionKey;
typedef std::map <CollisionActionKey, CollisionAction > CollisionActionList;

namespace ECS {
    namespace System {
        class CollisionSystem : public ECS::BaseSystem {
        public:
            CollisionSystem(CollisionActionList action) : _action(action) {};
            ~CollisionSystem() = default;

            virtual void tick(ECS::World* world, const float& dt) override {
                // update all positions / todo: scale
                world->each<CollisionComponent>([&](ECS::Entity* ent, CollisionComponent* box) {
					auto transform = ent->get<TransformComponent>();
					if (!transform)
						return;
					box->_rect.left = transform->position.x;
					box->_rect.top = transform->position.y;
				});

                world->each<CollisionComponent>([&](ECS::Entity* ent, CollisionComponent* box) {
                    world->each<CollisionComponent>([&](ECS::Entity* ent2, CollisionComponent* box2) {
						if (ent == ent2)
							return;
                        if (box->_rect.intersects(box2->_rect)) {
                            CollisionActionKey key = { box->_type, box2->_type };
                            if (_action.find(key) != _action.end()) {
								_action.at(key)(world, ent, ent2);
							}
						}
					});
                });
            }
        private:
            CollisionActionList _action;
        };
    }
}