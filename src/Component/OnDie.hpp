#pragma once

#include "SFML.hpp"
#include "ComponentBase.hpp"
#include <functional>

namespace ECS {
	class World;
    class Entity;
}

/**
 * @brief Component for on die
 * @details Used to know what to do when an entity die
*/
class OnDie : public Component {
public:
    /**
     * @brief Construct a new On Die Component object
     * @param action The action to do when the entity die
    */
    OnDie(std::function<void(ECS::World*, ECS::Entity*)> action) : _onDie(action) {};
    OnDie() {};

    /**
     * @brief Put the on die on string
     * @return The string of the on die
    */
    inline virtual std::string toString() const override {
        return "";
    }

    /// @brief Construct the on die from string
    /// @param str The string of the on die
    virtual void fromString(std::string str) override {
    }

    /**
     * @brief The action to do when the entity die
    */
    std::function<void(ECS::World*, ECS::Entity*)> _onDie = nullptr;
};
