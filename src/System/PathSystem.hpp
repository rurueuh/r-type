#pragma once

#include "System.hpp"
#include "Component.hpp"
#include "GameEngine.hpp"
#include <math.h>

namespace ECS::System::Path {
    typedef std::map<EnemyPathType, void(*)(ECS::World*, const float&, ECS::Entity*)> ShootPathType;
};

namespace ECS {
    namespace System {
        class PathSystem : public ECS::BaseSystem {
        public:
            PathSystem(ECS::System::Path::ShootPathType typeOfShoot) : _typeShoot(typeOfShoot) {};
            ~PathSystem() = default;

            virtual void tick(ECS::World* world, const float& dt) override {
                world->each<EnemyPath>([&](ECS::Entity* ent, EnemyPath* path) {
                    std::map<EnemyPathType, void(*)(ECS::World*, const float&, ECS::Entity *)> pathMap = {
						{ FOLLOW_PLAYER, PathSystem::PathFollowPlayer },
                        { FOLLOW_PATH, PathSystem::PathFollowPath },
                        { FOLLOW_PLAYER_BOSS, PathSystem::PathFollowPlayer },
                        { FOLLOW_PATH_BOSS, PathSystem::PathFollowPath },
					};
                    
                    pathMap[path->pathType](world, dt, ent);
                    if (_typeShoot.find(path->pathType) != _typeShoot.end()) {
						_typeShoot[path->pathType](world, dt, ent);
					}
                });
            }

            static void PathFollowPlayer(ECS::World* world, const float& dt, ECS::Entity* ent) {
                std::vector<ECS::Entity*> players = {};
                world->each<PlayerComponent>([&](ECS::Entity* ent, PlayerComponent* player) {
					players.push_back(ent);
				});

                if (players.size() == 0)
					return;
                auto player = players[0];
                auto playerTransform = player->get<TransformComponent>();
                auto playerVelocity = player->get<VelocityComponent>();
                auto transform = ent->get<TransformComponent>();
                auto velocity = ent->get<VelocityComponent>();

                float distanceBetween = (float)std::sqrt(std::pow(transform->position.x - playerTransform->position.x, 2) + pow(transform->position.y - playerTransform->position.y, 2));
                distanceBetween = distanceBetween / 100.f;
                constexpr float maxSpeed = 128.f;
                distanceBetween = std::max(distanceBetween, maxSpeed);


                constexpr float speed = 64.f;
                if (transform->position.x < 1200) {
                    velocity->velocity.x += 1.f * speed * dt;
                }
                else if (transform->position.x > 1600) {
                    velocity->velocity.x += -1.f * speed * dt;
                }
                else {
                    if (transform->position.x < playerTransform->position.x) {
                        velocity->velocity.x += 1.f * distanceBetween * dt;
                    }
                    else if (transform->position.x > playerTransform->position.x) {
                        velocity->velocity.x += -1.f * distanceBetween * dt;
                    }
                }
                if (transform->position.y < 0) {
                    velocity->velocity.y = 1.f * speed * dt;
                    transform->position.y = 0;
                }
                else if (transform->position.y > 900) {
                    velocity->velocity.y = -1.f * speed * dt;
                    transform->position.y = 900;
                }
                else {
                    if (transform->position.y < playerTransform->position.y) {
                        velocity->velocity.y += 1.f * distanceBetween * dt;
                    }
                    else if (transform->position.y > playerTransform->position.y) {
                        velocity->velocity.y += -1.f * distanceBetween * dt;
                    }
                }
            }

            static void PathFollowPath(ECS::World* world, const float& dt, ECS::Entity* ent) {
                auto transform = ent->get<TransformComponent>();
                auto velocity = ent->get<VelocityComponent>();
                auto path = ent->get<EnemyPath>();

                if (transform->position.y < 0) {
                    velocity->velocity.y = -velocity->velocity.y / 2;
                    transform->position.y = 0;
                    path->_isDownMove = true;
                    return;
                }
                else if (transform->position.y > 900) {
                    velocity->velocity.y = -velocity->velocity.y / 2;
                    transform->position.y = 900;
                    path->_isDownMove = false;
                    return;
                }

                if (path->_isDownMove) {
                    velocity->velocity.y += 1.f * 64.f * dt;
                }
                else {
                    velocity->velocity.y += -1.f * 64.f * dt;
                }
            }
        private:
            ECS::System::Path::ShootPathType _typeShoot = {};
        };
    }
}