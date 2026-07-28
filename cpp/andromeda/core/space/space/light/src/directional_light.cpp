#include "../include/directional_light.hpp"
#include "math/linear_algebra/include/linear_algebra_operations.hpp"


namespace andromeda::space
{
	DirectionalLight::DirectionalLight(
		const math::Vec3& direction,
		const math::Vec3& color,
		float intensity,
		const math::Vec3& ambient,
		const math::Vec3& diffuse,
		const math::Vec3& specular,
		float orthographic_half_size,
		float near_plane,
		float far_plane
	)
		: Light{
			color,
			intensity,
			ambient,
			diffuse,
			specular
		}
		, LightObject{ LightType::Directional }
		, m_orthographic_half_size{ orthographic_half_size }
		, m_near_plane{ near_plane }
		, m_far_plane{ far_plane }
		, m_direction{ math::LinAlgOps::normalize(direction) }
	{
	}

	DirectionalLight::~DirectionalLight() = default;

	float DirectionalLight::get_light_orthographic_half_size() const
	{
		return m_orthographic_half_size;
	}

	float DirectionalLight::get_light_near_plane() const
	{
		return m_near_plane;
	}

	float DirectionalLight::get_light_far_plane() const
	{
		return m_far_plane;
	}

	const math::Vec3& DirectionalLight::get_direction() const
	{
		return m_direction;
	}

	void DirectionalLight::set_light_orthographic_half_size(float half_size)
	{
		if (half_size > 0.0f)
		{
			m_orthographic_half_size = half_size;
		}
	}

	void DirectionalLight::set_light_near_plane(float near_plane)
	{
		if (near_plane > 0.0f)
		{
			m_near_plane = near_plane;
		}
	}

	void DirectionalLight::set_light_far_plane(float far_plane)
	{
		if (far_plane > m_near_plane)
		{
			m_far_plane = far_plane;
		}
	}

	void DirectionalLight::set_direction(const math::Vec3& direction)
	{
		m_direction = math::LinAlgOps::normalize(direction);
	}
}