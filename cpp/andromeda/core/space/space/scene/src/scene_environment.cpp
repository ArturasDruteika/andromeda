#include "../include/scene_environment.hpp"


namespace andromeda::space
{
	SceneEnvironment::SceneEnvironment()
		: m_ambient_strength{ 0.1f }
		, m_background_color{ math::Vec4{ 0.0f, 0.0f, 0.0f, 1.0f } }
	{
	}

	SceneEnvironment::~SceneEnvironment() = default;

	float SceneEnvironment::get_ambient_strength() const
	{
		return m_ambient_strength;
	}

	const math::Vec4& SceneEnvironment::get_background_color() const
	{
		return m_background_color;
	}

	void SceneEnvironment::set_ambient_strength(float ambient_strength)
	{
		m_ambient_strength = ambient_strength;
	}

	void SceneEnvironment::set_background_color(
		const math::Vec4& background_color
	)
	{
		m_background_color = background_color;
	}

	void SceneEnvironment::resize_grid(float resize_factor)
	{
		(void)resize_factor;

		// Implementation for resizing the grid can be added here.
	}
}