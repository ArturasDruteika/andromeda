#ifndef RENDERING__RAY__HPP
#define RENDERING__RAY__HPP


#include "glm/glm.hpp"


namespace andromeda::rendering
{
	struct Ray
	{
		glm::vec3 origin;
		glm::vec3 direction;
	};
}


#endif // RENDERING__RAY__HPP