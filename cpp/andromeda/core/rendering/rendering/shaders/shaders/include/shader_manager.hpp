#ifndef RENDERING__SHADERS__SHADERS__SHADER_MANAGER__HPP
#define RENDERING__SHADERS__SHADERS__SHADER_MANAGER__HPP


#include "shader_open_gl.hpp"
#include "../../support/include/shader_open_gl_types.hpp"
#include "pch.hpp"


namespace andromeda::rendering
{
	/// @brief Manages OpenGL shader programs.
	///
	/// Responsible for loading, creating, storing, and retrieving shader
	/// programs used by the renderer.
	class ShaderManager
	{
	public:
		/// @brief Constructs a shader manager.
		///
		/// @param init_shaders `true` to initialize shaders during construction;
		/// otherwise, `false`.
		ShaderManager(bool init_shaders);

		/// @brief Destroys the shader manager and its managed shaders.
		~ShaderManager();

		// Getters

		/// @brief Checks whether the shader manager has been initialized.
		///
		/// @return `true` if the shader manager is initialized; otherwise, `false`.
		bool is_initialized() const;

		/// @brief Retrieves a shader by type.
		///
		/// @param shader_type Shader type.
		/// @return Pointer to the requested shader, or `nullptr` if it is not available.
		ShaderOpenGL* get_shader(const ShaderOpenGLTypes& shader_type) const;

		/// @brief Retrieves the managed shader collection.
		///
		/// @return Map of shader types to shader instances.
		const std::unordered_map<ShaderOpenGLTypes, ShaderOpenGL*>& get_shaders_map() const;

		/// @brief Initializes all configured shaders.
		///
		/// @return `true` if initialization succeeded; otherwise, `false`.
		bool init_shaders();

		/// @brief Loads a shader from source files.
		///
		/// @param shader_type Shader type.
		/// @param vertex_shader_path Path to the vertex shader source.
		/// @param fragment_shader_path Path to the fragment shader source.
		/// @param geometry_shader_path Path to the geometry shader source.
		/// @return `true` if the shader was loaded successfully; otherwise, `false`.
		bool load_shader(
			const ShaderOpenGLTypes& shader_type,
			const std::filesystem::path& vertex_shader_path,
			const std::filesystem::path& fragment_shader_path,
			const std::filesystem::path& geometry_shader_path
		);

	private:
		/// @brief Creates a shader program.
		///
		/// @param shader_type Shader type.
		/// @param vertex_shader_path Path to the vertex shader source.
		/// @param fragment_shader_path Path to the fragment shader source.
		/// @param geometry_shader_path Path to the geometry shader source.
		/// @return `true` if the shader was created successfully; otherwise, `false`.
		bool create_shader(
			const ShaderOpenGLTypes& shader_type,
			const std::filesystem::path& vertex_shader_path,
			const std::filesystem::path& fragment_shader_path,
			const std::filesystem::path& geometry_shader_path
		);

		/// @brief Validates shader source file paths.
		///
		/// @param vertex_path Path to the vertex shader.
		/// @param fragment_path Path to the fragment shader.
		/// @param geometry_path Path to the geometry shader.
		/// @return `true` if all required paths are valid; otherwise, `false`.
		bool validate_shader_paths(
			const std::filesystem::path& vertex_path,
			const std::filesystem::path& fragment_path,
			const std::filesystem::path& geometry_path
		);

		/// @brief Validates a shader source file path.
		///
		/// @param path Shader source file path.
		/// @param type Human-readable shader type.
		/// @return `true` if the path is valid; otherwise, `false`.
		bool check_shader_path(
			const std::filesystem::path& path,
			const std::string& type
		);

	private:
		/// @brief Indicates whether the shader manager has been initialized.
		bool m_is_initialized;

		/// @brief Managed shaders indexed by shader type.
		std::unordered_map<ShaderOpenGLTypes, ShaderOpenGL*> m_shaders_map;
	};
}


#endif // RENDERING__SHADERS__SHADERS__SHADER_MANAGER__HPP