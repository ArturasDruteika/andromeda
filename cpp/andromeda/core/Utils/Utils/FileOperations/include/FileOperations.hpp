#ifndef UTILS__FILE_OPERATIONS__HPP
#define UTILS__FILE_OPERATIONS__HPP


#include "../../PrecompiledHeaders/include/pch.hpp"


namespace andromeda
{
	namespace Utils
	{
		class FileOperations
		{
		public:
			static std::string LoadFileAsString(const std::string& filePath);
			static std::string LoadFileAsString(const std::filesystem::path& filePath);
		};
	}
}



#endif // UTILS__FILE_OPERATIONS__HPP