#include "../include/shader_compiler_open_gl.hpp"
#include "glad/gl.h"
#include "spdlog/spdlog.h"


namespace andromeda::rendering
{
	ShaderCompilerOpenGL::ShaderCompilerOpenGL() = default;

	ShaderCompilerOpenGL::~ShaderCompilerOpenGL() = default;

	unsigned int ShaderCompilerOpenGL::compile(unsigned int type, const std::string& source)
	{
		unsigned int shader = glCreateShader(type);
		const char* shader_source_ptr = source.c_str();
		glShaderSource(shader, 1, &shader_source_ptr, nullptr);
		glCompileShader(shader);
		check_compile_errors(shader, type);
		return shader;
	}

	unsigned int ShaderCompilerOpenGL::link(
		unsigned int vertex_shader,
		unsigned int fragment_shader,
		unsigned int geometry_shader
	)
	{
		unsigned int program = glCreateProgram();

		if (vertex_shader)
			glAttachShader(program, vertex_shader);
		if (fragment_shader)
			glAttachShader(program, fragment_shader);
		if (geometry_shader)
			glAttachShader(program, geometry_shader);

		glLinkProgram(program);

		if (!check_link_errors(program))
		{
			glDeleteProgram(program);
			return 0;
		}

		// Optionally detach after a successful link
		if (vertex_shader)
			glDetachShader(program, vertex_shader);
		if (fragment_shader)
			glDetachShader(program, fragment_shader);
		if (geometry_shader)
			glDetachShader(program, geometry_shader);

		return program;
	}

	bool ShaderCompilerOpenGL::check_compile_errors(unsigned int shader, int type)
	{
		int success;
		int length;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(shader, length, nullptr, message);
			std::string shader_type_str = (type == GL_VERTEX_SHADER ? "vertex" : "fragment");
			spdlog::error("Shader compilation error ({}): {}", shader_type_str, message);
			glDeleteShader(shader);
			return false;
		}
		return true;
	}

	bool ShaderCompilerOpenGL::check_link_errors(unsigned int program)
	{
		int success;
		glGetProgramiv(program, GL_LINK_STATUS, &success);

		if (!success)
		{
			int length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
			char* message = static_cast<char*>(alloca(length * sizeof(char)));
			glGetProgramInfoLog(program, length, nullptr, message);
			spdlog::error("Shader program linking error: {}", message);
			glDeleteProgram(program);
			return false;
		}
		return true;
	}
}