#ifndef RENDERING__SHADERS__SUPPORT__SHADER_COMPILER_OPEN_GL__HPP
#define RENDERING__SHADERS__SUPPORT__SHADER_COMPILER_OPEN_GL__HPP


#include "pch.hpp"


namespace andromeda::rendering
{
	class ShaderCompilerOpenGL
	{
	public:
		ShaderCompilerOpenGL();
		~ShaderCompilerOpenGL();

		unsigned int compile(unsigned int type, const std::string& source);

		unsigned int link(
			unsigned int vertex_shader,
			unsigned int fragment_shader,
			unsigned int geometry_shader = 0
		);

	private:
		bool check_compile_errors(unsigned int shader, int type);
		bool check_link_errors(unsigned int program);
	};
}


#endif // RENDERING__SHADERS__SUPPORT__SHADER_COMPILER_OPEN_GL__HPP