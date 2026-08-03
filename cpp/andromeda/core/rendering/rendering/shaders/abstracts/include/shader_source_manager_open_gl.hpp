#pragma once


#include "pch.hpp"
#include "../../support/include/shader_types.hpp"


namespace andromeda::rendering
{
	/// @brief Manages OpenGL shader source files.
	///
	/// Stores shader file paths and their corresponding source code, and
	/// provides functionality for loading shader source from disk.
	class ShaderSourceManagerOpenGL
	{
	public:
		/// @brief Constructs a shader source manager.
		///
		/// @param vertex_shader_filepath Path to the vertex shader source file.
		/// @param fragment_shader_filepath Path to the fragment shader source file.
		/// @param geometry_shader_filepath Optional path to the geometry shader source file.
		/// @param load `true` to immediately load the shader sources; otherwise,
		/// `false`.
		ShaderSourceManagerOpenGL(
			const std::filesystem::path& vertex_shader_filepath,
			const std::filesystem::path& fragment_shader_filepath,
			const std::filesystem::path& geometry_shader_filepath = {},
			bool load = true
		);

		/// @brief Destroys the shader source manager.
		~ShaderSourceManagerOpenGL();

		// Getters

		/// @brief Retrieves the vertex shader file path.
		///
		/// @return Path to the vertex shader source file.
		const std::filesystem::path& get_vertex_shader_path() const;

		/// @brief Retrieves the fragment shader file path.
		///
		/// @return Path to the fragment shader source file.
		const std::filesystem::path& get_fragment_shader_path() const;

		/// @brief Retrieves the geometry shader file path.
		///
		/// @return Path to the geometry shader source file.
		const std::filesystem::path& get_geometry_shader_path() const;

		/// @brief Retrieves the loaded vertex shader source code.
		///
		/// @return Vertex shader source code.
		const std::string& get_vertex_code() const;

		/// @brief Retrieves the loaded fragment shader source code.
		///
		/// @return Fragment shader source code.
		const std::string& get_fragment_code() const;

		/// @brief Retrieves the loaded geometry shader source code.
		///
		/// @return Geometry shader source code.
		const std::string& get_geometry_code() const;

		/// @brief Loads shader source code from a file.
		///
		/// @param shader_type Type of shader to load.
		/// @param filepath Path to the shader source file.
		void load_shader_from_file(
			const ShaderType& shader_type,
			const std::filesystem::path& filepath
		);

	protected:
		/// @brief Path to the vertex shader source file.
		std::filesystem::path m_vertex_shader_path;

		/// @brief Path to the fragment shader source file.
		std::filesystem::path m_fragment_shader_path;

		/// @brief Path to the geometry shader source file.
		std::filesystem::path m_geometry_shader_path;

		/// @brief Loaded vertex shader source code.
		std::string m_vertex_code;

		/// @brief Loaded fragment shader source code.
		std::string m_fragment_code;

		/// @brief Loaded geometry shader source code.
		std::string m_geometry_code;
	};
}
