#pragma once

#include "ComponentBase.hpp"

struct PatternComponent : public Component {
    PatternComponent(std::string pattern) : pattern(pattern) {};
    std::string pattern;
};