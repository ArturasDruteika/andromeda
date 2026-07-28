#include "../include/camera_view.hpp"
#include "math/linear_algebra/include/linear_algebra_operations.hpp"

#include "spdlog/spdlog.h"


namespace andromeda::space
{
	CameraView::CameraView(
		const math::Vec3& position,
		const math::Vec3& target_coords
	)
		: m_position{ position }
		, m_target_coords{ target_coords }
		, m_forward{
			math::LinAlgOps::normalize(
				m_target_coords - m_position
			)
		}
		, m_right{
			math::LinAlgOps::normalize(
				math::LinAlgOps::cross(
					m_forward,
					math::Vec3(0.0f, 1.0f, 0.0f)
				)
			)
		}
		, m_up{
			math::LinAlgOps::cross(
				m_right,
				m_forward
			)
		}
		, m_view_matrix{}
	{
		calculate_view_matrix();
	}

	CameraView::~CameraView() = default;

	const math::Vec3& CameraView::get_position() const
	{
		return m_position;
	}

	const math::Vec3& CameraView::get_target_coords() const
	{
		return m_target_coords;
	}

	const math::Vec3& CameraView::get_forward() const
	{
		return m_forward;
	}

	const math::Vec3& CameraView::get_right() const
	{
		return m_right;
	}

	const math::Vec3& CameraView::get_up() const
	{
		return m_up;
	}

	const math::Mat4& CameraView::get_view_matrix() const
	{
		return m_view_matrix;
	}

	void CameraView::set_position(const math::Vec3& position)
	{
		m_position = position;
		calculate_view_matrix();
	}

	void CameraView::set_target_coords(const math::Vec3& target_coords)
	{
		m_target_coords = target_coords;
		calculate_view_matrix();
	}

	void CameraView::calculate_view_matrix()
	{
		m_forward = math::LinAlgOps::normalize(
			m_target_coords - m_position
		);

		m_right = math::LinAlgOps::normalize(
			math::LinAlgOps::cross(
				m_forward,
				math::Vec3(0.0f, 1.0f, 0.0f)
			)
		);

		m_up = math::LinAlgOps::cross(
			m_right,
			m_forward
		);

		m_view_matrix = math::LinAlgOps::look_at(
			m_position,
			m_target_coords,
			m_up
		);
	}

	void CameraView::update_view_matrix()
	{
		m_view_matrix = math::LinAlgOps::look_at(
			m_position,
			m_target_coords,
			m_up
		);
	}
}