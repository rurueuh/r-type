#pragma once

#include "SFML.hpp"
#include "ComponentBase.hpp"
#include <unordered_map>
#include <any>

namespace ECS::Component {
    typedef std::unordered_map<std::string, float> ComponentDataMap;
};

/**
 * @brief DataComponent is a component that can store any data please stock data where can be convert to float
 * 
*/
struct DataComponent : public Component {
    DataComponent(ECS::Component::ComponentDataMap data) : _data(data) {};
    DataComponent() : _data({}) {};

    inline virtual std::string toString() const override {
        std::string str = "";
        for (auto& [key, value] : _data) {
            str += key + "|" + std::to_string(static_cast<float>(value));
        }
        return str;
    }

    virtual void fromString(std::string str) override {
        std::stringstream ss = std::stringstream(str);
        std::string key;
        std::string value;
        while (std::getline(ss, key, '|') && std::getline(ss, value, '|')) {
            // remove space from key
            key.erase(std::remove_if(key.begin(), key.end(), isspace), key.end());
            _data[key] = std::stof(value);
        }
    }

    inline void set(std::string key, float value) {
        _data[key] = value;
    }

    template <typename T>
    inline T get(std::string key) {
        if (!has<T>(key))
            return static_cast<float>(0.f);
        return static_cast<T>(_data[key]);
    }

    template <typename T>
    inline bool has(std::string key) {
        if (_data.size() == 0)
            return false;
        return _data.find(key) != _data.end();
    }

    ECS::Component::ComponentDataMap _data = {};
};

