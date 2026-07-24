#ifndef UTILS__FILE_OPERATIONS__HPP
#define UTILS__FILE_OPERATIONS__HPP


#include "../../precompiled_headers/include/pch.hpp"


namespace andromeda::utils
{
	class FileOperations
	{
	public:
		static std::string load_file_as_string(const std::string& file_path);
		static std::string load_file_as_string(const std::filesystem::path& file_path);
	};
}


#endif // UTILS__FILE_OPERATIONS__HPP