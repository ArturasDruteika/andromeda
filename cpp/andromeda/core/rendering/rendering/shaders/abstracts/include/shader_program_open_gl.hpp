#ifndef RENDERING__SHADERS__ABSTRACTS__SHADER_PROGRAM_OPEN_GL__HPP
#define RENDERING__SHADERS__ABSTRACTS__SHADER_PROGRAM_OPEN_GL__HPP


#include "pch.hpp"


namespace andromeda::rendering
{
	/// @brief Base class for OpenGL shader programs.
	///
	/// Encapsulates an OpenGL shader program object and provides common
	/// functionality for creating, binding, and unbinding shader programs.
	class ShaderProgramOpenGL
	{
	public:
		/// @brief Constructs an empty shader program.
		ShaderProgramOpenGL();

		/// @brief Destroys the shader program and releases its resources.
		~ShaderProgramOpenGL();

		// Getters

		/// @brief Retrieves the OpenGL shader program identifier.
		///
		/// @return Shader program identifier.
		unsigned int get_program_id() const;

		/// @brief Binds the shader program.
		void bind() const;

		/// @brief Unbinds the currently active shader program.
		void unbind() const;

	protected:
		/// @brief Creates and links an OpenGL shader program.
		///
		/// @param vertex_code Vertex shader source code.
		/// @param fragment_code Fragment shader source code.
		/// @param geometry_code Optional geometry shader source code.
		void create_shader_program(
			const std::string& vertex_code,
			const std::string& fragment_code,
			const std::string& geometry_code = {}
		);

	protected:
		/// @brief OpenGL shader program identifier.
		unsigned int m_program_id;
	};
}


#endif // RENDERING__SHADERS__ABSTRACTS__SHADER_PROGRAM_OPEN_GL__HPP