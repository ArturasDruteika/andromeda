#ifndef RENDERING__SHADERS__SUPPORT__UNIFORM_SETTER_OPEN_GL__HPP
#define RENDERING__SHADERS__SUPPORT__UNIFORM_SETTER_OPEN_GL__HPP


#include "pch.hpp"
#include "glm/glm.hpp"


namespace andromeda::rendering
{
	class UniformSetterOpenGL
	{
	public:
		UniformSetterOpenGL();
		~UniformSetterOpenGL();

		void set_uniform(unsigned int program, const std::string& name, int value) const;
		void set_uniform(unsigned int program, const std::string& name, float value) const;
		void set_uniform(unsigned int program, const std::string& name, const glm::vec3& vector) const;
		void set_uniform(unsigned int program, const std::string& name, const glm::vec4& vector) const;
		void set_uniform(unsigned int program, const std::string& name, const glm::mat3& matrix) const;
		void set_uniform(unsigned int program, const std::string& name, const glm::mat4& matrix) const;
		void set_uniform(unsigned int program, const std::string& name, const std::vector<float>& values) const;
		void set_uniform(unsigned int program, const std::string& name, const std::vector<glm::vec3>& vectors) const;
		void set_uniform(unsigned int program, const std::string& name, const std::vector<glm::vec4>& vectors) const;
		void set_uniform(unsigned int program, const std::string& name, const std::vector<glm::mat4>& matrices) const;
	};
}


#endif // RENDERING__SHADERS__SUPPORT__UNIFORM_SETTER_OPEN_GL__HPP