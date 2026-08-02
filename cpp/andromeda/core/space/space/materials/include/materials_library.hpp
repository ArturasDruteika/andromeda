#pragma once


#include "../../macro_exports/include/macro_exports.hpp"
#include "../../materials/include/material_types.hpp"
#include "materials.hpp"
#include "pch.hpp"


namespace andromeda::space
{
	/// @brief Manages a collection of predefined materials.
	///
	/// Provides functionality for loading, saving, querying, and retrieving
	/// materials indexed by their material type.
	class SPACE_API MaterialLibrary
	{
	public:
		/// @brief Constructs an empty material library.
		MaterialLibrary();

		/// @brief Constructs a material library and loads it from a file.
		///
		/// @param file_path Path to the material configuration file.
		explicit MaterialLibrary(const std::filesystem::path& file_path);

		/// @brief Destroys the material library.
		~MaterialLibrary();

		// Getters

		/// @brief Checks whether a material exists in the library.
		///
		/// @param material_type Material type to query.
		/// @return `true` if the material exists; otherwise, `false`.
		bool has(const MaterialType& material_type) const;

		/// @brief Retrieves the number of stored materials.
		///
		/// @return Number of materials in the library.
		std::size_t get_size() const;

		/// @brief Retrieves the material configuration file path.
		///
		/// @return Path to the material configuration file.
		std::filesystem::path get_materials_config_file_path() const;

		/// @brief Retrieves all stored materials.
		///
		/// @return Map of material types to material instances.
		std::unordered_map<MaterialType, Material> get_materials() const;

		/// @brief Retrieves all available material types.
		///
		/// @return Collection of material types.
		std::vector<MaterialType> get_all_material_types() const;

		/// @brief Retrieves a material by type.
		///
		/// @param material_type Material type.
		/// @return Copy of the requested material.
		Material get_material(const MaterialType& material_type) const;

		/// @brief Retrieves a pointer to a material by type.
		///
		/// @param material_type Material type.
		/// @return Pointer to the material, or `nullptr` if it does not exist.
		const Material* get_material_ptr(const MaterialType& material_type) const;

		/// @brief Loads materials from a configuration file.
		///
		/// @param file_path Path to the material configuration file.
		/// @return `true` if loading succeeded; otherwise, `false`.
		bool load_from_file(const std::filesystem::path& file_path);

		/// @brief Saves materials to a configuration file.
		///
		/// @param file_path Destination configuration file path.
		/// @return `true` if saving succeeded; otherwise, `false`.
		bool save_to_file(const std::filesystem::path& file_path) const;

		// TODO: Consider adding ability to add, remove, and update materials in the config.

	private:
		/// @brief Path to the material configuration file.
		std::filesystem::path m_materials_config_file_path;

		/// @brief Collection of materials indexed by material type.
		std::unordered_map<MaterialType, Material> m_materials;
	};
}
