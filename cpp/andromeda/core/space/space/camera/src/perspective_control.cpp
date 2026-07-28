#include "../include/perspective_control.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"
#include "math/linear_algebra/include/linear_algebra_operations.hpp"
#include "math/trigonometry/include/trigonometry.hpp"


namespace andromeda::space
{
	PerspectiveControl::PerspectiveControl()
		: m_fov_deg{ 45.0f }
		, m_near_plane{ 0.1f }
		, m_far_plane{ 1000.0f }
		, m_aspect{ 1.0f }
		, m_projection{}
	{
		update_projection();
	}

	PerspectiveControl::PerspectiveControl(
		float fov_deg,
		float near_plane,
		float far_plane,
		float aspect
	)
		: m_fov_deg{ fov_deg }
		, m_near_plane{ near_plane }
		, m_far_plane{ far_plane }
		, m_aspect{ aspect }
		, m_projection{}
	{
		update_projection();
	}

	PerspectiveControl::~PerspectiveControl() = default;

	float PerspectiveControl::get_field_of_view_degrees() const
	{
		return m_fov_deg;
	}

	float PerspectiveControl::get_near_plane() const
	{
		return m_near_plane;
	}

	float PerspectiveControl::get_far_plane() const
	{
		return m_far_plane;
	}

	float PerspectiveControl::get_aspect() const
	{
		return m_aspect;
	}

	const math::Mat4& PerspectiveControl::get_projection() const
	{
		return m_projection;
	}

	void PerspectiveControl::set_field_of_view_degrees(
		float fov_deg,
		bool update_projection
	)
	{
		m_fov_deg = fov_deg;

		if (update_projection)
		{
			this->update_projection();
		}
	}

	void PerspectiveControl::set_near_plane(
		float near_plane,
		bool update_projection
	)
	{
		m_near_plane = near_plane;

		if (update_projection)
		{
			this->update_projection();
		}
	}

	void PerspectiveControl::set_far_plane(
		float far_plane,
		bool update_projection
	)
	{
		m_far_plane = far_plane;

		if (update_projection)
		{
			this->update_projection();
		}
	}

	void PerspectiveControl::set_aspect(
		float aspect,
		bool update_projection
	)
	{
		m_aspect = aspect;

		if (update_projection)
		{
			this->update_projection();
		}
	}

	void PerspectiveControl::update_projection()
	{
		m_projection = math::LinAlgOps::perspective(
			math::Trigonometry::deg_2_rad(m_fov_deg),
			m_aspect,
			m_near_plane,
			m_far_plane
		);
	}
}