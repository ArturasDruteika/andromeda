#include "../include/light.hpp"


namespace andromeda::space
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

	float Light::get_intensity() const
	{
		return m_intensity;
	}

	math::Vec3 Light::get_color() const
	{
		return m_color;
	}

	math::Vec3 Light::get_ambient() const
	{
		return m_ambient;
	}

	math::Vec3 Light::get_diffuse() const
	{
		return m_diffuse;
	}

	math::Vec3 Light::get_specular() const
	{
		return m_specular;
	}

	void Light::set_intensity(float intensity)
	{
		m_intensity = intensity;
	}

	void Light::set_color(const math::Vec3& color)
	{
		m_color = color;
	}

	void Light::set_ambient(const math::Vec3& ambient)
	{
		m_ambient = ambient;
	}

	void Light::set_diffuse(const math::Vec3& diffuse)
	{
		m_diffuse = diffuse;
	}

	void Light::set_specular(const math::Vec3& specular)
	{
		m_specular = specular;
	}
}