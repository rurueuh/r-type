#pragma once

#include "SFML.hpp"
#include "ComponentBase.hpp"

/**
 * @brief Component for life span
 * @details The life span is the time before the entity is destroyed
*/
struct LifeSpan : public Component {
    /**
     * @brief Construct a new Life Span object
     * @param time The time before the entity is destroyed
    */
    LifeSpan(float time) : _time(time) {};
    LifeSpan() : _time(0.f) {};

    /**
     * @brief Put the life span on string
     * @return The string of the life span
    */
    inline virtual std::string toString() const override {
        std::string str = "";
        str += std::to_string(_time);
        return str;
    }

    /// @brief Construct the life span from string
    /// @param str The string of the life span
    virtual void fromString(std::string str) override {
        std::stringstream ss = std::stringstream(str);
        ss >> _time;
    }

    float _time = 0.f;
};
