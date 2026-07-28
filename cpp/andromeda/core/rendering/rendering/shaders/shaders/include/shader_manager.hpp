#ifndef RENDERING__SHADERS__SHADERS__SHADER_MANAGER__HPP
#define RENDERING__SHADERS__SHADERS__SHADER_MANAGER__HPP


#include "shader_open_gl.hpp"
#include "../../support/include/shader_open_gl_types.hpp"
#include "pch.hpp"


namespace andromeda::rendering
{
	class ShaderManager
	{
	public:
		ShaderManager(bool init_shaders);
		~ShaderManager();

		// Getters
		bool is_initialized() const;
		ShaderOpenGL* get_shader(const ShaderOpenGLTypes& shader_type) const;
		const std::unordered_map<ShaderOpenGLTypes, ShaderOpenGL*>& get_shaders_map() const;

		bool init_shaders();

		bool load_shader(
			const ShaderOpenGLTypes& shader_type,
			const std::filesystem::path& vertex_shader_path,
			const std::filesystem::path& fragment_shader_path,
			const std::filesystem::path& geometry_shader_path
		);

	private:
		bool create_shader(
			const ShaderOpenGLTypes& shader_type,
			const std::filesystem::path& vertex_shader_path,
			const std::filesystem::path& fragment_shader_path,
			const std::filesystem::path& geometry_shader_path
		);

		bool validate_shader_paths(
			const std::filesystem::path& vertex_path,
			const std::filesystem::path& fragment_path,
			const std::filesystem::path& geometry_path
		);

		bool check_shader_path(
			const std::filesystem::path& path,
			const std::string& type
		);

	private:
		bool m_is_initialized;
		std::unordered_map<ShaderOpenGLTypes, ShaderOpenGL*> m_shaders_map;
	};
}


#endif // RENDERING__SHADERS__SHADERS__SHADER_MANAGER__HPP