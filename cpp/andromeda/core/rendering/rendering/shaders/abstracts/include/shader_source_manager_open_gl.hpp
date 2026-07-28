#ifndef RENDERING__SHADERS__ABSTRACTS__SHADER_SOURCE_MANAGER_OPEN_GL__HPP
#define RENDERING__SHADERS__ABSTRACTS__SHADER_SOURCE_MANAGER_OPEN_GL__HPP


#include "pch.hpp"
#include "../../support/include/shader_types.hpp"


namespace andromeda::rendering
{
	class ShaderSourceManagerOpenGL
	{
	public:
		ShaderSourceManagerOpenGL(
			const std::filesystem::path& vertex_shader_filepath,
			const std::filesystem::path& fragment_shader_filepath,
			const std::filesystem::path& geometry_shader_filepath = {},
			bool load = true
		);
		~ShaderSourceManagerOpenGL();

		// Getters
		const std::filesystem::path& get_vertex_shader_path() const;
		const std::filesystem::path& get_fragment_shader_path() const;
		const std::filesystem::path& get_geometry_shader_path() const;

		const std::string& get_vertex_code() const;
		const std::string& get_fragment_code() const;
		const std::string& get_geometry_code() const;

		void load_shader_from_file(
			const ShaderType& shader_type,
			const std::filesystem::path& filepath
		);

	protected:
		std::filesystem::path m_vertex_shader_path;
		std::filesystem::path m_fragment_shader_path;
		std::filesystem::path m_geometry_shader_path;

		std::string m_vertex_code;
		std::string m_fragment_code;
		std::string m_geometry_code;
	};
}


#endif // RENDERING__SHADERS__ABSTRACTS__SHADER_SOURCE_MANAGER_OPEN_GL__HPP