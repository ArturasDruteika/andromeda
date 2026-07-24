#include "../include/shader_program_open_gl.hpp"
#include "../../support/include/shader_compiler_open_gl.hpp"

#include <glad/gl.h>
#include <spdlog/spdlog.h>


namespace andromeda::rendering
{
	ShaderProgramOpenGL::ShaderProgramOpenGL()
		: m_program_id{ 0 }
	{
	}

	ShaderProgramOpenGL::~ShaderProgramOpenGL()
	{
		if (m_program_id != 0)
		{
			glDeleteProgram(m_program_id);
			m_program_id = 0;
		}
	}

	void ShaderProgramOpenGL::create_shader_program(
		const std::string& vertex_code,
		const std::string& fragment_code,
		const std::string& geometry_code
	)
	{
		ShaderCompilerOpenGL compiler;

		// Compile shaders
		unsigned int vertex_shader =
			compiler.compile(GL_VERTEX_SHADER, vertex_code);

		unsigned int fragment_shader =
			compiler.compile(GL_FRAGMENT_SHADER, fragment_code);

		unsigned int geometry_shader = 0;
		if (!geometry_code.empty())
		{
			geometry_shader =
				compiler.compile(GL_GEOMETRY_SHADER, geometry_code);
		}

		// Link program
		m_program_id = compiler.link(
			vertex_shader,
			fragment_shader,
			geometry_shader
		);

		// Delete shader objects after linking
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		if (geometry_shader != 0)
		{
			glDeleteShader(geometry_shader);
		}
	}

	void ShaderProgramOpenGL::bind() const
	{
		glUseProgram(m_program_id);
	}

	void ShaderProgramOpenGL::unbind() const
	{
		glUseProgram(0);
	}

	unsigned int ShaderProgramOpenGL::get_program_id() const
	{
		return m_program_id;
	}
}