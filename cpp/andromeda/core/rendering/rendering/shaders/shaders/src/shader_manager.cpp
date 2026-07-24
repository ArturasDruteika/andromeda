#include "../include/shader_manager.hpp"
#include "utils/file_operations/include/file_operations.hpp"
#include "spdlog/spdlog.h"


namespace andromeda::rendering
{
	ShaderManager::ShaderManager(bool init_shaders)
		: m_is_initialized{ false }
	{
        if (init_shaders)
        {
            init_shaders();
        }
	}

	ShaderManager::~ShaderManager()
	{
        for (auto& [type, shader] : m_shaders_map)
        {
            delete shader; // Clean up dynamically allocated ShaderOpenGL objects
        }
        m_shaders_map.clear(); // Clear the map
		spdlog::info("ShaderManager destroyed and all shaders cleaned up.");
	}

    bool ShaderManager::is_initialized() const
    {
        return m_is_initialized;
	}

    ShaderOpenGL* ShaderManager::get_shader(const ShaderOpenGLTypes& shader_type) const
    {
        std::unordered_map<ShaderOpenGLTypes, ShaderOpenGL*>::const_iterator it =
            m_shaders_map.find(shader_type);
        if (it == m_shaders_map.end() || it->second == nullptr)
        {
			spdlog::error("Shader of type {} not found in ShaderManager", static_cast<int>(shader_type));
            return nullptr;
        }

        return it->second; // assuming the map stores raw pointers
    }

    const std::unordered_map<ShaderOpenGLTypes, ShaderOpenGL*>& ShaderManager::get_shaders_map() const
    {
        return m_shaders_map;
    }

    bool ShaderManager::init_shaders()
    {
        std::vector<ShaderDefinition> shaders = {
            {
                ShaderOpenGLTypes::RenderableObjects,
                "shader_program_sources/vertex.glsl",
                "shader_program_sources/fragment.glsl"
            },
            {
                ShaderOpenGLTypes::Grid,
                "shader_program_sources/vertex_grid.glsl",
                "shader_program_sources/fragment_grid.glsl"
            },
            {
                ShaderOpenGLTypes::RenderableObjectsLuminous,
                "shader_program_sources/vertex.glsl",
                "shader_program_sources/fragment_luminous_objects.glsl"
            },
            {
                ShaderOpenGLTypes::RenderableObjectsNonLuminous,
                "shader_program_sources/vertex_illumination.glsl",
                "shader_program_sources/fragment_non_luminous_objects.glsl"
            },
            {
                ShaderOpenGLTypes::ShadowMap,
                "shader_program_sources/vertex_depth_only.glsl",
                "shader_program_sources/fragment_depth_only.glsl"
            },
            {
                ShaderOpenGLTypes::PointShadowCubeMap,
                "shader_program_sources/vertex_point_shadow.glsl",
                "shader_program_sources/fragment_point_shadow.glsl",
                "shader_program_sources/geometry_point_shadow.glsl"
            },
            {
                ShaderOpenGLTypes::Text,
                "shader_program_sources/vertex_text.glsl",
                "shader_program_sources/fragment.glsl",
            }
        };

        for (const ShaderDefinition& shader : shaders)
        {
            if (!create_shader(
                shader.type,
                shader.vertex_path,
                shader.fragment_path,
                shader.geometry_path
            ))
            {
                // If any shader fails to load/compile, return false immediately
                return false;
            }
        }

        m_is_initialized = true;
        return true;
    }

    bool ShaderManager::load_shader(
        const ShaderOpenGLTypes& shader_type,
        const std::filesystem::path& vertex_shader_path,
        const std::filesystem::path& fragment_shader_path,
        const std::filesystem::path& geometry_shader_path
    )
    {
        if (!validate_shader_paths(
            vertex_shader_path,
            fragment_shader_path,
            geometry_shader_path
        ))
        {
            return false;
        }

        if (m_shaders_map.find(shader_type) != m_shaders_map.end())
        {
            spdlog::warn(
                "Shader of type {} already exists. Overwriting.",
                static_cast<int>(shader_type)
            );
            delete m_shaders_map[shader_type];
            m_shaders_map.erase(shader_type);
        }

        if (m_shaders_map.find(shader_type) != m_shaders_map.end())
        {
            spdlog::warn(
                "Shader of type {} already exists. Overwriting.",
                static_cast<int>(shader_type)
            );
            delete m_shaders_map[shader_type];
            m_shaders_map.erase(shader_type);
        }
        return create_shader(
            shader_type,
            vertex_shader_path,
            fragment_shader_path,
            geometry_shader_path
        );
    }

    bool ShaderManager::create_shader(
        const ShaderOpenGLTypes& shader_type,
        const std::filesystem::path& vertex_shader_path,
        const std::filesystem::path& fragment_shader_path,
        const std::filesystem::path& geometry_shader_path
    )
    {
        ShaderOpenGL* shader = new ShaderOpenGL(
            vertex_shader_path,
            fragment_shader_path,
            geometry_shader_path
        );
        m_shaders_map.insert({ shader_type, shader });

		// TODO: Add error handling for shader creation
        return true;
    }

    bool ShaderManager::validate_shader_paths(
        const std::filesystem::path& vertex_path,
        const std::filesystem::path& fragment_path,
        const std::filesystem::path& geometry_path
    )
    {
        bool status = true;
        if (!vertex_path.empty())
            status = check_shader_path(vertex_path, "Vertex");
        else
            status = false;
        if (!fragment_path.empty())
            status = check_shader_path(fragment_path, "Fragment");
        else
            status = false;
        if (!geometry_path.empty())
            status = check_shader_path(geometry_path, "Geometry");
        return status;
    }

    bool ShaderManager::check_shader_path(
        const std::filesystem::path& path,
        const std::string& type
    )
    {
        if (!std::filesystem::exists(path))
        {
            spdlog::error("{} shader file does not exist: {}", type, path.string());
            return false;
        }

        if (path.extension() != ".glsl")
        {
            spdlog::error("{} shader file must have .glsl extension: {}", type, path.string());
            return false;
        }

        return true;
    }
}