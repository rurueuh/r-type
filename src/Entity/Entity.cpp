#include "Entity.hpp"
#include "World.hpp"

namespace ECS {
	std::string Entity::serialise(void) {
		std::string serialised = "";
		/*
		"id": 1,
		"components": {
			"PvComponent": {
				10000
			},
		}
		*/
		serialised += "\"id\": " + std::to_string(this->getId()) + ",";
		serialised += "\"components\": {";
		for (auto& pair : handler->components) {
			if (pair.second.size() == 0)
				continue;
			serialised += "\"" + Utils::getTypeName(pair.first) + "\": {";
			for (void* component : pair.second) {
				auto tr = static_cast<Component*>(component);
				serialised += tr->toString();
			}
			serialised += "},";
		}
		serialised += "}";


		// remplace all ,} by }
		size_t pos = 0;
		while ((pos = serialised.find(",}", pos)) != std::string::npos) {
			serialised.replace(pos, 2, "}");
		}

		return serialised;
	}
}
