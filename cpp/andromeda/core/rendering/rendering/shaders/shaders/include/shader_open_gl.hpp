#ifndef RENDERING__SHADERS__SHADERS__SHADER_OPEN_GL__HPP
#define RENDERING__SHADERS__SHADERS__SHADER_OPEN_GL__HPP


#include "../../abstracts/include/shader_program_open_gl.hpp"
#include "../../abstracts/include/shader_source_manager_open_gl.hpp"
#include "../../support/include/uniform_setter_open_gl.hpp"
#include "../../interfaces/include/i_shader.hpp"


namespace andromeda::rendering
{
	/// @brief Represents an OpenGL shader program.
	///
	/// Combines shader source management, shader program creation, and uniform
	/// updates into a single rendering shader object.
	class ShaderOpenGL
		: public ShaderProgramOpenGL
		, public ShaderSourceManagerOpenGL
		, public IShader
	{
	public:
		/// @brief Constructs an OpenGL shader.
		///
		/// @param vertex_code_file_path Path to the vertex shader source file.
		/// @param fragment_code_file_path Path to the fragment shader source file.
		/// @param geometry_shader_filepath Optional path to the geometry shader source file.
		ShaderOpenGL(
			const std::filesystem::path& vertex_code_file_path,
			const std::filesystem::path& fragment_code_file_path,
			const std::filesystem::path& geometry_shader_filepath = {}
		);

		/// @brief Destroys the shader.
		~ShaderOpenGL() = default;

		/// @brief Binds the shader program.
		void bind() const override;

		/// @brief Unbinds the shader program.
		void unbind() const override;

		// Uniform setters

		/// @brief Sets the value of a shader uniform.
		///
		/// @tparam T Uniform value type.
		/// @param name Uniform name.
		/// @param value Uniform value.
		template<typename T>
		void set_uniform(const std::string& name, const T& value) const;

	private:
		/// @brief Helper object used to update shader uniforms.
		UniformSetterOpenGL m_uniform_setter;
	};
}


#endif // RENDERING__SHADERS__SHADERS__SHADER_OPEN_GL__HPP