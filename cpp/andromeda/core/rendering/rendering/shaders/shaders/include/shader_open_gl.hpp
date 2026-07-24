#ifndef RENDERING__SHADERS__SHADERS__SHADER_OPEN_GL__HPP
#define RENDERING__SHADERS__SHADERS__SHADER_OPEN_GL__HPP


#include "../../abstracts/include/shader_program_open_gl.hpp"
#include "../../abstracts/include/shader_source_manager_open_gl.hpp"
#include "../../support/include/uniform_setter_open_gl.hpp"
#include "../../interfaces/include/i_shader.hpp"


namespace andromeda::rendering
{
	class ShaderOpenGL
		: public ShaderProgramOpenGL
		, public ShaderSourceManagerOpenGL
		, public IShader
	{
	public:
		ShaderOpenGL(
			const std::filesystem::path& vertex_code_file_path,
			const std::filesystem::path& fragment_code_file_path,
			const std::filesystem::path& geometry_shader_filepath = {}
		);
		~ShaderOpenGL() = default;

		void bind() const override;
		void unbind() const override;

		// Uniform setters
		template<typename T>
		void set_uniform(const std::string& name, const T& value) const;

	private:
		UniformSetterOpenGL m_uniform_setter;
	};
}


#endif // RENDERING__SHADERS__SHADERS__SHADER_OPEN_GL__HPP