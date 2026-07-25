#include "../include/materials_library.hpp"
#include "utils/file_operations/include/file_operations.hpp"
#include "utils/nlohmann_json/include/json.hpp"
#include "spdlog/spdlog.h"


namespace andromeda::space
{
	namespace
	{
		// Maps a material name to its corresponding MaterialType.
		// Throws if the name is not recognized.
		MaterialType material_type_from_string(const std::string& name)
		{
			if (name == "emerald")        return MaterialType::Emerald;
			if (name == "jade")           return MaterialType::Jade;
			if (name == "obsidian")       return MaterialType::Obsidian;
			if (name == "pearl")          return MaterialType::Pearl;
			if (name == "ruby")           return MaterialType::Ruby;
			if (name == "turquoise")      return MaterialType::Turquoise;
			if (name == "brass")          return MaterialType::Brass;
			if (name == "bronze")         return MaterialType::Bronze;
			if (name == "chrome")         return MaterialType::Chrome;
			if (name == "copper")         return MaterialType::Copper;
			if (name == "gold")           return MaterialType::Gold;
			if (name == "silver")         return MaterialType::Silver;
			if (name == "black plastic")  return MaterialType::BlackPlastic;
			if (name == "cyan plastic")   return MaterialType::CyanPlastic;
			if (name == "green plastic")  return MaterialType::GreenPlastic;
			if (name == "red plastic")    return MaterialType::RedPlastic;
			if (name == "white plastic")  return MaterialType::WhitePlastic;
			if (name == "yellow plastic") return MaterialType::YellowPlastic;
			if (name == "black rubber")   return MaterialType::BlackRubber;
			if (name == "cyan rubber")    return MaterialType::CyanRubber;
			if (name == "green rubber")   return MaterialType::GreenRubber;
			if (name == "red rubber")     return MaterialType::RedRubber;
			if (name == "white rubber")   return MaterialType::WhiteRubber;
			if (name == "yellow rubber")  return MaterialType::YellowRubber;

			throw std::runtime_error("Unknown material name: " + name);
		}
	}


	MaterialLibrary::MaterialLibrary() = default;

	MaterialLibrary::MaterialLibrary(const std::filesystem::path& file_path)
		: m_materials_config_file_path{ file_path }
	{
		load_from_file(file_path);
	}

	MaterialLibrary::~MaterialLibrary() = default;

	bool MaterialLibrary::has(const MaterialType& material_type) const
	{
		return m_materials.find(material_type) != m_materials.end();
	}

	std::size_t MaterialLibrary::get_size() const
	{
		return m_materials.size();
	}

	std::filesystem::path MaterialLibrary::get_materials_config_file_path() const
	{
		return m_materials_config_file_path;
	}

	std::unordered_map<MaterialType, Material> MaterialLibrary::get_materials() const
	{
		return m_materials;
	}

	std::vector<MaterialType> MaterialLibrary::get_all_material_types() const
	{
		std::vector<MaterialType> result;
		result.reserve(m_materials.size());

		for (const auto& [type, material] : m_materials)
		{
			result.push_back(type);
		}

		return result;
	}

	Material MaterialLibrary::get_material(const MaterialType& material_type) const
	{
		std::unordered_map<MaterialType, Material>::const_iterator it = m_materials.find(material_type);

		if (it == m_materials.end())
		{
			spdlog::error(
				"MaterialLibrary::get_material - material '{}' not found; returning default",
				static_cast<int>(material_type)
			);

			return Material{};
		}

		return it->second;
	}

	const Material* MaterialLibrary::get_material_ptr(
		const MaterialType& material_type
	) const
	{
		std::unordered_map<MaterialType, Material>::const_iterator it = m_materials.find(material_type);

		if (it == m_materials.end())
		{
			spdlog::error(
				"MaterialLibrary::get_material_ptr - material '{}' not found; returning nullptr",
				static_cast<int>(material_type)
			);

			return nullptr;
		}

		return &it->second;
	}

	bool MaterialLibrary::load_from_file(
		const std::filesystem::path& file_path
	)
	{
		std::string file_content;

		try
		{
			file_content = andromeda::utils::FileOperations::load_file_as_string(file_path);
		}
		catch (const std::exception& exception)
		{
			spdlog::error(
				"MaterialLibrary::load_from_file - failed to load file \"{}\": {}",
				file_path.string(),
				exception.what()
			);

			return false;
		}

		nlohmann::json json;

		try
		{
			json = nlohmann::json::parse(file_content);
		}
		catch (const nlohmann::json::parse_error& exception)
		{
			spdlog::error(
				"MaterialLibrary::load_from_file - JSON parse error in \"{}\": {}",
				file_path.string(),
				exception.what()
			);

			return false;
		}

		if (!json.is_array())
		{
			spdlog::error(
				"MaterialLibrary::load_from_file - content is not a JSON array: \"{}\"",
				file_path.string()
			);

			return false;
		}

		std::unordered_map<MaterialType, Material> loaded_materials;

		for (const nlohmann::json& entry : json)
		{
			try
			{
				const std::string name = entry.at("name").get<std::string>();
				const nlohmann::json& ambient = entry.at("ambient");
				const nlohmann::json& diffuse = entry.at("diffuse");
				const nlohmann::json& specular = entry.at("specular");
				const float shininess = entry.at("shininess").get<float>();

				Material material;
				material.set_shininess(shininess);
				material.set_name(name);

				material.set_ambient(
					math::Vec3{
						ambient.at(0).get<float>(),
						ambient.at(1).get<float>(),
						ambient.at(2).get<float>()
					}
				);

				material.set_diffuse(
					math::Vec3{
						diffuse.at(0).get<float>(),
						diffuse.at(1).get<float>(),
						diffuse.at(2).get<float>()
					}
				);

				material.set_specular(
					math::Vec3{
						specular.at(0).get<float>(),
						specular.at(1).get<float>(),
						specular.at(2).get<float>()
					}
				);

				const MaterialType type =
					material_type_from_string(name);

				loaded_materials[type] = std::move(material);
			}
			catch (const std::exception& exception)
			{
				spdlog::warn(
					"MaterialLibrary::load_from_file - skipping invalid material entry in \"{}\": {}",
					file_path.string(),
					exception.what()
				);
			}
		}

		m_materials = std::move(loaded_materials);
		m_materials_config_file_path = file_path;

		return true;
	}

	bool MaterialLibrary::save_to_file(
		const std::filesystem::path& file_path
	) const
	{
		spdlog::info(
			"Saving {} materials to \"{}\"",
			m_materials.size(),
			file_path.string()
		);

		nlohmann::json json = nlohmann::json::array();

		for (const auto& [type, material] : m_materials)
		{
			nlohmann::json entry;

			const math::Vec3& ambient = material.get_ambient();
			const math::Vec3& diffuse = material.get_diffuse();
			const math::Vec3& specular = material.get_specular();

			entry["name"] = material.get_name();

			entry["ambient"] = {
				ambient[0],
				ambient[1],
				ambient[2]
			};

			entry["diffuse"] = {
				diffuse[0],
				diffuse[1],
				diffuse[2]
			};

			entry["specular"] = {
				specular[0],
				specular[1],
				specular[2]
			};

			entry["shininess"] = material.get_shininess();

			json.push_back(std::move(entry));
		}

		std::ofstream output_file(file_path);

		if (!output_file.is_open())
		{
			spdlog::error(
				"MaterialLibrary::save_to_file - failed to open \"{}\" for writing",
				file_path.string()
			);

			return false;
		}

		output_file
			<< std::fixed
			<< std::setprecision(4)
			<< std::setw(4)
			<< json
			<< '\n';

		if (!output_file.good())
		{
			spdlog::error(
				"MaterialLibrary::save_to_file - error occurred while writing to \"{}\"",
				file_path.string()
			);

			return false;
		}

		spdlog::info(
			"Successfully wrote material data to \"{}\"",
			file_path.string()
		);

		return true;
	}
}