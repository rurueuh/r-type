#include "Entity.hpp"
#include "World.hpp"

namespace ECS
{
	std::string Entity::serialise(void)
	{
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
		std::ostringstream serialised;
		serialised << this->getId() << " [";
		for (const auto &pair : handler->components)
		{
			if (pair.second.empty())
				continue;
			serialised << Utils::getRegisteredComponent(pair.first) << " { ";
			for (void *component : pair.second)
			{
				auto tr = static_cast<Component *>(component);
				serialised << tr->toString();
			}
			serialised << " },";
		}
		std::string result = serialised.str();
		size_t pos = 0;
		while ((pos = result.find(",]", pos)) != std::string::npos)
		{
			result.replace(pos, 2, "]");
		}
		while ((pos = result.find(",[", pos)) != std::string::npos)
		{
			result.replace(pos, 2, "[");
		}
		return result;
	}
}
