#include "../include/shader_source_manager_open_gl.hpp"

#include "utils/file_operations/include/file_operations.hpp"
#include "spdlog/spdlog.h"


namespace andromeda::rendering
{
	ShaderSourceManagerOpenGL::ShaderSourceManagerOpenGL(
		const std::filesystem::path& vertex_shader_filepath,
		const std::filesystem::path& fragment_shader_filepath,
		const std::filesystem::path& geometry_shader_filepath,
		bool load
	)
		: m_vertex_shader_path{ vertex_shader_filepath }
		, m_fragment_shader_path{ fragment_shader_filepath }
		, m_geometry_shader_path{ geometry_shader_filepath }
	{
		if (load)
		{
			load_shader_from_file(ShaderType::Vertex, vertex_shader_filepath);
			load_shader_from_file(ShaderType::Fragment, fragment_shader_filepath);

			if (!geometry_shader_filepath.empty())
			{
				load_shader_from_file(ShaderType::Geometry, geometry_shader_filepath);
			}
		}
	}

	ShaderSourceManagerOpenGL::~ShaderSourceManagerOpenGL() = default;

	const std::filesystem::path& ShaderSourceManagerOpenGL::get_vertex_shader_path() const
	{
		return m_vertex_shader_path;
	}

	const std::filesystem::path& ShaderSourceManagerOpenGL::get_fragment_shader_path() const
	{
		return m_fragment_shader_path;
	}

	const std::filesystem::path& ShaderSourceManagerOpenGL::get_geometry_shader_path() const
	{
		return m_geometry_shader_path;
	}

	const std::string& ShaderSourceManagerOpenGL::get_vertex_code() const
	{
		return m_vertex_code;
	}

	const std::string& ShaderSourceManagerOpenGL::get_fragment_code() const
	{
		return m_fragment_code;
	}

	const std::string& ShaderSourceManagerOpenGL::get_geometry_code() const
	{
		return m_geometry_code;
	}

	void ShaderSourceManagerOpenGL::load_shader_from_file(
		const ShaderType& shader_type,
		const std::filesystem::path& filepath
	)
	{
		std::error_code ec;

		if (filepath.empty()
			|| !std::filesystem::exists(filepath, ec)
			|| !std::filesystem::is_regular_file(filepath, ec))
		{
			spdlog::error(
				"Shader file not found or not a regular file: {}",
				filepath.string()
			);

			throw std::runtime_error("Shader file not found: " + filepath.string());
		}

		const std::string code = utils::FileOperations::load_file_as_string(filepath);

		switch (shader_type)
		{
		case ShaderType::Vertex:
		{
			m_vertex_code = code;
			break;
		}

		case ShaderType::Fragment:
		{
			m_fragment_code = code;
			break;
		}

		case ShaderType::Geometry:
		{
			m_geometry_code = code;
			break;
		}

		default:
		{
			throw std::runtime_error(
				"Unsupported shader type for loading from file."
			);
		}
		}
	}
}