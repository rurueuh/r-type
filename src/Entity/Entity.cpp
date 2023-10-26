#include "Entity.hpp"
#include "World.hpp"

namespace ECS
{
	std::string Entity::serialise(void)
	{
		std::ostringstream serialised;
		serialised << this->getId() << " [";
		for (const auto &pair : handler->components)
		{
			if (pair.second.empty())
				continue;
			serialised << Utils::getRegisteredComponent(pair.first) << " { ";
			for (auto component : pair.second)
			{
				serialised << component->toString();
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
