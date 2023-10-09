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
		// 0,[PvComponent { 100 },PositionComponent { 10 10 }]:1,[PvComponent { 10000 }]:
		// "0"|"[PvComponent { 100 },PositionComponent { 10 10 }]" : premiere etape sep id et components
		// "[PvComponent { 100 }" "PositionComponent { 10 10 }]" : deuxieme etape sep components grace a la virgule
		// "PvComponent { 100 }" "PositionComponent { 10 10 }" : troisieme etape retirer les crochets
		// "PvComponent" "100" "PositionComponent" "10 10" : quatrieme etape sep components grace aux bracket
		// 
		serialised += std::to_string(this->getId()) + " ";
		serialised += "[";
		for (auto& pair : handler->components) {
			if (pair.second.size() == 0)
				continue;
			serialised += "" + Utils::getTypeName(pair.first) + " { ";
			for (void* component : pair.second) {
				auto tr = static_cast<Component*>(component);
				serialised += tr->toString();
			}
			serialised += " },";
		}
		serialised += "]";


		size_t pos = 0;
		while ((pos = serialised.find(",]", pos)) != std::string::npos) {
			serialised.replace(pos, 2, "]");
		}
		while ((pos = serialised.find(",[", pos)) != std::string::npos) {
			serialised.replace(pos, 2, "[");
		}

		return serialised;
	}
}
