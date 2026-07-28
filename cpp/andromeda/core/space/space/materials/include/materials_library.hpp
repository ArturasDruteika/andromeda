#ifndef SPACE__MATERIALS_LIBRARY__HPP
#define SPACE__MATERIALS_LIBRARY__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "../../materials/include/material_types.hpp"
#include "materials.hpp"
#include "pch.hpp"


namespace andromeda::space
{
	class SPACE_API MaterialLibrary
	{
	public:
		MaterialLibrary();
		explicit MaterialLibrary(const std::filesystem::path& file_path);
		~MaterialLibrary();

		// Getters
		bool has(const MaterialType& material_type) const;
		std::size_t get_size() const;
		std::filesystem::path get_materials_config_file_path() const;
		std::unordered_map<MaterialType, Material> get_materials() const;
		std::vector<MaterialType> get_all_material_types() const;
		Material get_material(const MaterialType& material_type) const;
		const Material* get_material_ptr(const MaterialType& material_type) const;

		bool load_from_file(const std::filesystem::path& file_path);
		bool save_to_file(const std::filesystem::path& file_path) const;

		// TODO: Consider adding ability to add, remove, and update materials in the config.

	private:
		std::filesystem::path m_materials_config_file_path;
		std::unordered_map<MaterialType, Material> m_materials;
	};
}


#endif // SPACE__MATERIALS_LIBRARY__HPP