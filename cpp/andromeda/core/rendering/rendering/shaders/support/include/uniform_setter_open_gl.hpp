#pragma once


#include "pch.hpp"
#include "glm/glm.hpp"


namespace andromeda::rendering
{
	/// @brief Provides helper functions for setting OpenGL shader uniforms.
	///
	/// Wraps common OpenGL uniform update operations for scalar values,
	/// vectors, matrices, and arrays.
	class UniformSetterOpenGL
	{
	public:
		/// @brief Constructs a uniform setter.
		UniformSetterOpenGL();

		/// @brief Destroys the uniform setter.
		~UniformSetterOpenGL();

		/// @brief Sets an integer uniform.
		///
		/// @param program OpenGL shader program identifier.
		/// @param name Uniform name.
		/// @param value Integer value.
		void set_uniform(unsigned int program, const std::string& name, int value) const;

		/// @brief Sets a floating-point uniform.
		///
		/// @param program OpenGL shader program identifier.
		/// @param name Uniform name.
		/// @param value Floating-point value.
		void set_uniform(unsigned int program, const std::string& name, float value) const;

		/// @brief Sets a 3-component vector uniform.
		///
		/// @param program OpenGL shader program identifier.
		/// @param name Uniform name.
		/// @param vector Vector value.
		void set_uniform(unsigned int program, const std::string& name, const glm::vec3& vector) const;

		/// @brief Sets a 4-component vector uniform.
		///
		/// @param program OpenGL shader program identifier.
		/// @param name Uniform name.
		/// @param vector Vector value.
		void set_uniform(unsigned int program, const std::string& name, const glm::vec4& vector) const;

		/// @brief Sets a 3×3 matrix uniform.
		///
		/// @param program OpenGL shader program identifier.
		/// @param name Uniform name.
		/// @param matrix Matrix value.
		void set_uniform(unsigned int program, const std::string& name, const glm::mat3& matrix) const;

		/// @brief Sets a 4×4 matrix uniform.
		///
		/// @param program OpenGL shader program identifier.
		/// @param name Uniform name.
		/// @param matrix Matrix value.
		void set_uniform(unsigned int program, const std::string& name, const glm::mat4& matrix) const;

		/// @brief Sets an array of floating-point values.
		///
		/// @param program OpenGL shader program identifier.
		/// @param name Uniform name.
		/// @param values Array of floating-point values.
		void set_uniform(unsigned int program, const std::string& name, const std::vector<float>& values) const;

		/// @brief Sets an array of 3-component vectors.
		///
		/// @param program OpenGL shader program identifier.
		/// @param name Uniform name.
		/// @param vectors Array of vector values.
		void set_uniform(unsigned int program, const std::string& name, const std::vector<glm::vec3>& vectors) const;

		/// @brief Sets an array of 4-component vectors.
		///
		/// @param program OpenGL shader program identifier.
		/// @param name Uniform name.
		/// @param vectors Array of vector values.
		void set_uniform(unsigned int program, const std::string& name, const std::vector<glm::vec4>& vectors) const;

		/// @brief Sets an array of 4×4 matrices.
		///
		/// @param program OpenGL shader program identifier.
		/// @param name Uniform name.
		/// @param matrices Array of matrix values.
		void set_uniform(unsigned int program, const std::string& name, const std::vector<glm::mat4>& matrices) const;
	};
}
