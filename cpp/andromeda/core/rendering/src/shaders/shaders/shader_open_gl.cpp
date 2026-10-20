#include "shaders/shaders/shader_open_gl.hpp"

#include <filesystem>
#include <string>
#include <vector>


namespace andromeda::rendering
{
    ShaderOpenGL::ShaderOpenGL(const std::filesystem::path& vertex_code_file_path,
                               const std::filesystem::path& fragment_code_file_path,
                               const std::filesystem::path& geometry_shader_filepath)
        : ShaderSourceManagerOpenGL(vertex_code_file_path,
                                    fragment_code_file_path,
                                    geometry_shader_filepath,
                                    true)
    {
        ShaderProgramOpenGL::create_shader_program(get_vertex_code(),
                                                   get_fragment_code(),
                                                   get_geometry_code());
    }

    void ShaderOpenGL::bind() const
    {
        ShaderProgramOpenGL::bind();
    }

    void ShaderOpenGL::unbind() const
    {
        ShaderProgramOpenGL::unbind();
    }
}