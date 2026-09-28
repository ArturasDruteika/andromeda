#pragma once


#include "glm/glm.hpp"


namespace andromeda::rendering
{
	struct Ray
	{
		glm::vec3 origin;
		glm::vec3 direction;
	};
}
