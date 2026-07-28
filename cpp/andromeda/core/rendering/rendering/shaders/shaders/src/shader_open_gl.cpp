#include "../include/shader_open_gl.hpp"


namespace andromeda::rendering
{
	ShaderOpenGL::ShaderOpenGL(
		const std::filesystem::path& vertex_code_file_path,
		const std::filesystem::path& fragment_code_file_path,
		const std::filesystem::path& geometry_shader_filepath
	)
		: ShaderSourceManagerOpenGL(
			vertex_code_file_path,
			fragment_code_file_path,
			geometry_shader_filepath,
			true
		)
	{
		ShaderProgramOpenGL::create_shader_program(
			get_vertex_code(),
			get_fragment_code(),
			get_geometry_code()
		);
	}

	void ShaderOpenGL::bind() const
	{
		ShaderProgramOpenGL::bind();
	}

	void ShaderOpenGL::unbind() const
	{
		ShaderProgramOpenGL::unbind();
	}

	template<typename T>
	void ShaderOpenGL::set_uniform(const std::string& name, const T& value) const
	{
		m_uniform_setter.set_uniform(get_program_id(), name, value);
	}

	// Explicit template instantiations for allowed types
	template void ShaderOpenGL::set_uniform<int>(const std::string&, const int&) const;
	template void ShaderOpenGL::set_uniform<float>(const std::string&, const float&) const;
	template void ShaderOpenGL::set_uniform<glm::vec3>(const std::string&, const glm::vec3&) const;
	template void ShaderOpenGL::set_uniform<glm::vec4>(const std::string&, const glm::vec4&) const;
	template void ShaderOpenGL::set_uniform<glm::mat3>(const std::string&, const glm::mat3&) const;
	template void ShaderOpenGL::set_uniform<glm::mat4>(const std::string&, const glm::mat4&) const;
	template void ShaderOpenGL::set_uniform<std::vector<float>>(const std::string&, const std::vector<float>&) const;
	template void ShaderOpenGL::set_uniform<std::vector<glm::vec3>>(const std::string&, const std::vector<glm::vec3>&) const;
	template void ShaderOpenGL::set_uniform<std::vector<glm::vec4>>(const std::string&, const std::vector<glm::vec4>&) const;
	template void ShaderOpenGL::set_uniform<std::vector<glm::mat4>>(const std::string&, const std::vector<glm::mat4>&) const;
}