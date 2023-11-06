#pragma once

#include "SFML.hpp"
#include "ComponentBase.hpp"
#include <unordered_map>
#include <any>

namespace ECS::Component {
    /**
     * @brief typedef for component data map
     * @details typedef for component data map
    */
    typedef std::unordered_map<std::string, float> ComponentDataMap;
};

/**
 * @brief DataComponent is a component that can store any data please stock data where can be convert to float
 * @details DataComponent is a component that can store any data please stock data where can be convert to float
*/
struct DataComponent : public Component {
    /**
     * @brief Construct a new Data Component object
     * @param data The data to store
    */
    DataComponent(ECS::Component::ComponentDataMap data) : _data(data) {};
    DataComponent() : _data({}) {};


    /**
     * @brief Put the data on string
     * @return The string of the data
    */
    inline virtual std::string toString() const override {
        std::string str = "";
        for (auto& [key, value] : _data) {
            str += key + "|" + std::to_string(static_cast<float>(value));
        }
        return str;
    }

    /**
     * @brief Construct the data from string
     * @param str The string of the data
    */
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


    /**
     * @brief Set the data
     * @param key The key of the data
     * @param value The value of the data
    */
    inline void set(std::string key, float value) {
        _data[key] = value;
    }

    /**
     * @brief Get the data
     * @param key The key of the data
     * @return The data
    */
    template <typename T>
    inline T get(std::string key) {
        if (!has<T>(key))
            return static_cast<float>(0.f);
        return static_cast<T>(_data[key]);
    }

    /**
     * @brief Check if the data exist
     * @param key The key of the data
     * @return true if exist
     * @return false if not exist
    */
    template <typename T>
    inline bool has(std::string key) {
        if (_data.size() == 0)
            return false;
        return _data.find(key) != _data.end();
    }

    /**
     * @brief Get the data map
     * @return The data map
    */
    ECS::Component::ComponentDataMap _data = {};
};

