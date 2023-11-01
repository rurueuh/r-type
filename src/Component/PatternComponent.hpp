#pragma once

#include "ComponentBase.hpp"

struct PatternComponent : public Component {
    PatternComponent(std::string pattern) : pattern(pattern) {};
    PatternComponent() : pattern("o") {};
    std::string pattern;
};