#ifndef UTILS__FILE_OPERATIONS__HPP
#define UTILS__FILE_OPERATIONS__HPP


#include "../../precompiled_headers/include/pch.hpp"


namespace andromeda::utils
{
	/// @brief Provides utility functions for reading files from disk.
	///
	/// Supports loading the contents of a file into a string using either a
	/// string path or a filesystem path.
	class FileOperations
	{
	public:
		/// @brief Loads the contents of a file into a string.
		///
		/// @param file_path Path to the file.
		/// @return File contents as a string.
		static std::string load_file_as_string(const std::string& file_path);

		/// @brief Loads the contents of a file into a string.
		///
		/// @param file_path Filesystem path to the file.
		/// @return File contents as a string.
		static std::string load_file_as_string(const std::filesystem::path& file_path);
	};
}


#endif // UTILS__FILE_OPERATIONS__HPP