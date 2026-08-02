#pragma once


#include "pch.hpp"


namespace andromeda::rendering
{
	/// @brief Compiles and links OpenGL shader programs.
	///
	/// Provides helper functions for compiling individual shader stages and
	/// linking them into an executable OpenGL shader program.
	class ShaderCompilerOpenGL
	{
	public:
		/// @brief Constructs a shader compiler.
		ShaderCompilerOpenGL();

		/// @brief Destroys the shader compiler.
		~ShaderCompilerOpenGL();

		/// @brief Compiles a shader from source code.
		///
		/// @param type OpenGL shader type (for example, vertex, fragment, or geometry).
		/// @param source Shader source code.
		/// @return Identifier of the compiled shader object.
		unsigned int compile(unsigned int type, const std::string& source);

		/// @brief Links compiled shaders into an OpenGL shader program.
		///
		/// @param vertex_shader Compiled vertex shader identifier.
		/// @param fragment_shader Compiled fragment shader identifier.
		/// @param geometry_shader Optional compiled geometry shader identifier.
		/// @return Identifier of the linked shader program.
		unsigned int link(
			unsigned int vertex_shader,
			unsigned int fragment_shader,
			unsigned int geometry_shader = 0
		);

	private:
		/// @brief Checks whether shader compilation succeeded.
		///
		/// @param shader Compiled shader identifier.
		/// @param type OpenGL shader type.
		/// @return `true` if compilation succeeded; otherwise, `false`.
		bool check_compile_errors(unsigned int shader, int type);

		/// @brief Checks whether shader program linking succeeded.
		///
		/// @param program Linked shader program identifier.
		/// @return `true` if linking succeeded; otherwise, `false`.
		bool check_link_errors(unsigned int program);
	};
}
