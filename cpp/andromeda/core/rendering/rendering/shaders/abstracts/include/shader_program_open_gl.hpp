#ifndef RENDERING__SHADERS__ABSTRACTS__SHADER_PROGRAM_OPEN_GL__HPP
#define RENDERING__SHADERS__ABSTRACTS__SHADER_PROGRAM_OPEN_GL__HPP


#include "pch.hpp"


namespace andromeda::rendering
{
	class ShaderProgramOpenGL
	{
	public:
		ShaderProgramOpenGL();
		~ShaderProgramOpenGL();

		// Getters
		unsigned int get_program_id() const;

		void bind() const;
		void unbind() const;

	protected:
		void create_shader_program(
			const std::string& vertex_code,
			const std::string& fragment_code,
			const std::string& geometry_code = {}
		);

	protected:
		unsigned int m_program_id;
	};
}


#endif // RENDERING__SHADERS__ABSTRACTS__SHADER_PROGRAM_OPEN_GL__HPP