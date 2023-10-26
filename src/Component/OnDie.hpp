#pragma once

#include "SFML.hpp"
#include "ComponentBase.hpp"
#include <functional>

namespace ECS {
	class World;
    class Entity;
}

struct OnDie : public Component {
    OnDie(std::function<void(ECS::World*, ECS::Entity*)> action) : _onDie(action) {};
    OnDie() {};

    inline virtual std::string toString() const override {
        return "";
    }

    virtual void fromString(std::string str) override {
    }

    std::function<void(ECS::World*, ECS::Entity*)> _onDie = nullptr;
};
