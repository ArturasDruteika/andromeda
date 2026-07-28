#include "../include/uniform_setter_open_gl.hpp"
#include "glad/gl.h"
#include <glm/gtc/type_ptr.hpp>
#include "spdlog/spdlog.h"


namespace andromeda::rendering
{
	UniformSetterOpenGL::UniformSetterOpenGL() = default;

	UniformSetterOpenGL::~UniformSetterOpenGL() = default;

	void UniformSetterOpenGL::set_uniform(
		unsigned int program,
		const std::string& name,
		int value
	) const
	{
		int location = glGetUniformLocation(program, name.c_str());
		if (location != -1)
		{
			glUniform1i(location, value);
		}
		else
		{
			spdlog::warn("Uniform '{}' not found in shader.", name);
		}
	}

	void UniformSetterOpenGL::set_uniform(
		unsigned int program,
		const std::string& name,
		float value
	) const
	{
		int location = glGetUniformLocation(program, name.c_str());
		if (location == -1)
		{
			spdlog::warn("Uniform '{}' not found in shader.", name);
			return;
		}
		glUniform1f(location, value);
	}


	void UniformSetterOpenGL::set_uniform(
		unsigned int program,
		const std::string& name,
		const glm::vec3& vector
	) const
	{
		int location = glGetUniformLocation(program, name.c_str());
		if (location == -1)
		{
			spdlog::warn("Uniform '{}' not found in shader.", name);
			return;
		}

		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void UniformSetterOpenGL::set_uniform(
		unsigned int program,
		const std::string& name,
		const glm::vec4& vector
	) const
	{
		int location = glGetUniformLocation(program, name.c_str());
		if (location == -1)
		{
			spdlog::warn("Uniform '{}' not found in shader.", name);
			return;
		}
		glUniform4f(location, vector.r, vector.g, vector.b, vector.a);
	}

	void UniformSetterOpenGL::set_uniform(
		unsigned int program,
		const std::string& name,
		const glm::mat3& matrix
	) const
	{
		int location = glGetUniformLocation(program, name.c_str());
		if (location == -1)
		{
			spdlog::warn("Uniform '{}' not found in shader.", name);
			return;
		}

		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void UniformSetterOpenGL::set_uniform(
		unsigned int program,
		const std::string& name,
		const glm::mat4& matrix
	) const
	{
		int location = glGetUniformLocation(program, name.c_str());
		if (location == -1)
		{
			spdlog::warn("Uniform '{}' not found in shader.", name);
			return;
		}

		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void UniformSetterOpenGL::set_uniform(
		unsigned int program,
		const std::string& name,
		const std::vector<float>& values
	) const
	{
		for (size_t i = 0; i < values.size(); ++i)
		{
			// construct "name[i]" for each element
			std::string indexed_name = name + "[" + std::to_string(i) + "]";
			int location = glGetUniformLocation(program, indexed_name.c_str());
			if (location == -1)
			{
				spdlog::warn("Uniform '{}' not found in shader.", indexed_name);
				continue;
			}
			// upload single float
			glUniform1f(location, values[i]);
		}
	}

	void UniformSetterOpenGL::set_uniform(
		unsigned int program,
		const std::string& name,
		const std::vector<glm::vec3>& vectors
	) const
	{
		for (size_t i = 0; i < vectors.size(); ++i)
		{
			std::string indexed_name = name + "[" + std::to_string(i) + "]";
			int location = glGetUniformLocation(program, indexed_name.c_str());
			if (location == -1)
			{
				spdlog::warn("Uniform '{}' not found in shader.", indexed_name);
				continue;
			}
			glUniform3f(location, vectors[i].x, vectors[i].y, vectors[i].z);
		}
	}

	void UniformSetterOpenGL::set_uniform(
		unsigned int program,
		const std::string& name,
		const std::vector<glm::vec4>& vectors
	) const
	{
		for (size_t i = 0; i < vectors.size(); ++i)
		{
			std::string indexed_name = name + "[" + std::to_string(i) + "]";
			int location = glGetUniformLocation(program, indexed_name.c_str());
			if (location == -1)
			{
				spdlog::warn("Uniform '{}' not found in shader.", indexed_name);
				continue;
			}
			glUniform4f(location, vectors[i].r, vectors[i].g, vectors[i].b, vectors[i].a);
		}
	}

	void UniformSetterOpenGL::set_uniform(
		unsigned int program,
		const std::string& name,
		const std::vector<glm::mat4>& matrices
	) const
	{
		if (matrices.empty())
			return;

		int location = glGetUniformLocation(program, name.c_str());

		// only try appending [0] if the caller passed the base name without brackets
		if (location == -1 && name.find('[') == std::string::npos)
		{
			std::string name_0 = name + "[0]";
			location = glGetUniformLocation(program, name_0.c_str());
		}

		if (location == -1)
		{
			spdlog::warn("Uniform '{}' not found in shader.", name);
			return;
		}

		glUniformMatrix4fv(
			location,
			static_cast<int>(matrices.size()),
			GL_FALSE,
			glm::value_ptr(matrices[0])
		);
	}
}