#include "../include/materials.hpp"
#include "spdlog/spdlog.h"


namespace andromeda::space
{
	Material::Material()
		: m_shininess{ 0.6f }
		, m_name{ "emerald" }
		, m_ambient{ 0.0215f, 0.1745f, 0.0215f }
		, m_diffuse{ 0.07568f, 0.61424f, 0.07568f }
		, m_specular{ 0.633f, 0.727811f, 0.633f }
	{
	}

	Material::~Material() = default;

	float Material::get_shininess() const
	{
		return m_shininess;
	}

	const std::string& Material::get_name() const
	{
		return m_name;
	}

	const math::Vec3& Material::get_ambient() const
	{
		return m_ambient;
	}

	const math::Vec3& Material::get_diffuse() const
	{
		return m_diffuse;
	}

	const math::Vec3& Material::get_specular() const
	{
		return m_specular;
	}

	void Material::set_shininess(float shininess)
	{
		m_shininess = shininess;
	}

	void Material::set_name(const std::string& name)
	{
		m_name = name;
	}

	void Material::set_ambient(const math::Vec3& ambient)
	{
		if (!validate_vec3_components(ambient))
		{
			spdlog::error(
				"Ambient vector components must be within the range [0.0f, 1.0f]."
			);
			return;
		}

		m_ambient = ambient;
	}

	void Material::set_diffuse(const math::Vec3& diffuse)
	{
		if (!validate_vec3_components(diffuse))
		{
			spdlog::error(
				"Diffuse vector components must be within the range [0.0f, 1.0f]."
			);
			return;
		}

		m_diffuse = diffuse;
	}

	void Material::set_specular(const math::Vec3& specular)
	{
		if (!validate_vec3_components(specular))
		{
			spdlog::error(
				"Specular vector components must be within the range [0.0f, 1.0f]."
			);
			return;
		}

		m_specular = specular;
	}

	bool Material::validate_vec3_components(const math::Vec3& vector)
	{
		return vector[0] >= 0.0f && vector[0] <= 1.0f
			&& vector[1] >= 0.0f && vector[1] <= 1.0f
			&& vector[2] >= 0.0f && vector[2] <= 1.0f;
	}
}