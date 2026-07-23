#include "../include/Light.hpp"


namespace andromeda::Space
{
	Light::Light(
		const math::Vec3& color, 
		float intensity, 
		const math::Vec3& ambient, 
		const math::Vec3& diffuse,
		const math::Vec3& specular
	)
		: m_intensity{ intensity }
		, m_color{ color }
		, m_ambient{ ambient }
		, m_diffuse{ diffuse }
		, m_specular{ specular }
	{
	}

	Light::~Light() = default;

	float Light::GetIntensity() const
	{
		return m_intensity;
	}

	math::Vec3 Light::GetColor() const
	{
		return m_color;
	}

	math::Vec3 Light::GeAmbient() const
	{
		return m_ambient;
	}

	math::Vec3 Light::GetDiffuse() const
	{
		return m_diffuse;
	}

	math::Vec3 Light::GetSpecular() const
	{
		return m_specular;
	}

	void Light::SetIntensity(float intensity)
	{
		m_intensity = intensity;
	}

	void Light::SetColor(const math::Vec3& color)
	{
		m_color = color;
	}

	void Light::SetAmbient(const math::Vec3& ambient)
	{
		m_ambient = ambient;
	}

	void Light::SetDiffuse(const math::Vec3& diffuse)
	{
		m_diffuse = diffuse;
	}

	void Light::SetSpecular(const math::Vec3& specular)
	{
		m_specular = specular;
	}
}
