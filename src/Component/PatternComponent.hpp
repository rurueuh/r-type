#pragma once

#include "ComponentBase.hpp"

/**
 * @brief Component for pattern
 * @deprecated Not used anymore
*/
struct PatternComponent : public Component {
    /**
     * @brief Construct a new Pattern Component object
     * @param pattern The pattern
     * @param currentIndex The current index of the pattern
     * @deprecated Not used anymore
    */
    PatternComponent(std::string pattern, size_t currentIndex) : pattern(pattern), currentIndex(currentIndex) {};
    PatternComponent() : pattern("o"), currentIndex(0) {};

    inline virtual std::string toString() const override {
        return pattern;
    }

    virtual void fromString(std::string str) override {
        pattern = str;
        currentIndex = 0;
    }

    std::string pattern = "o";
    size_t currentIndex = 0;
};