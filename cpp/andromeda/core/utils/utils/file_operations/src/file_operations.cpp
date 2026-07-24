#include "../include/file_operations.hpp"


namespace andromeda::utils
{
	std::string FileOperations::load_file_as_string(const std::string& file_path)
	{
		std::ifstream file(file_path);
		if (!file.is_open())
		{
			throw std::runtime_error("Failed to open file: " + file_path);
		}

		std::stringstream shader_stream;
		shader_stream << file.rdbuf();
		return shader_stream.str();
	}

	std::string FileOperations::load_file_as_string(const std::filesystem::path& file_path)
	{
		std::ifstream file(file_path);
		if (!file.is_open())
		{
			throw std::runtime_error("Failed to open file: " + file_path.string());
		}

		std::stringstream shader_stream;
		shader_stream << file.rdbuf();
		return shader_stream.str();
	}
}