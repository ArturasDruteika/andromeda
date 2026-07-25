#include "../include/camera_controller.hpp"
#include "math/linear_algebra/include/linear_algebra_operations.hpp"


namespace andromeda::space
{
	CameraController::CameraController(
		const math::Vec3& position,
		const math::Vec3& target_coords
	)
		: CameraView(position, target_coords)
		, m_distance{ math::LinAlgOps::length(position - target_coords) }
		, m_orientation{ math::Quaternion(1.0f, 0.0f, 0.0f, 0.0f) }
	{
	}

	CameraController::~CameraController() = default;

	void CameraController::rotate(float yaw, float pitch, float roll)
	{
		// Get camera local axes.
		math::Vec3 right = math::QuaternionOps::rotate(
			m_orientation,
			math::Vec3(1.0f, 0.0f, 0.0f)
		);

		math::Vec3 up = math::QuaternionOps::rotate(
			m_orientation,
			math::Vec3(0.0f, 1.0f, 0.0f)
		);

		math::Vec3 forward = math::QuaternionOps::rotate(
			m_orientation,
			math::Vec3(0.0f, 0.0f, -1.0f)
		);

		if (roll != 0.0f)
		{
			// Roll: rotate around forward.
			math::Quaternion q_roll =
				math::QuaternionOps::angle_axis(roll, forward);

			m_orientation = math::QuaternionOps::normalize(
				math::QuaternionOps::multiply(
					q_roll,
					m_orientation
				)
			);
		}
		else
		{
			// Yaw: rotate around up.
			math::Quaternion q_yaw =
				math::QuaternionOps::angle_axis(-yaw, up);

			// Pitch: rotate around right.
			math::Quaternion q_pitch =
				math::QuaternionOps::angle_axis(-pitch, right);

			m_orientation = math::QuaternionOps::normalize(
				math::QuaternionOps::multiply(
					math::QuaternionOps::multiply(
						q_yaw,
						q_pitch
					),
					m_orientation
				)
			);
		}

		update_direction();
	}

	void CameraController::zoom(float delta_distance)
	{
		// Exponential zoom.
		float zoom_factor = std::exp(delta_distance * 0.1f);

		m_distance *= zoom_factor;
		m_distance = math::LinAlgOps::clamp(
			m_distance,
			0.01f,
			1e6f
		);

		update_direction();
	}

	// void CameraController::set_on_distance_change(
	//     OnDistanceChange callback
	// )
	// {
	//     // TODO: Implement observer pattern if needed.
	// }

	void CameraController::update_direction()
	{
		// Forward is -Z in local space (OpenGL convention).
		math::Vec3 local_offset(0.0f, 0.0f, m_distance);

		math::Vec3 offset = math::QuaternionOps::rotate(
			m_orientation,
			local_offset
		);

		m_position = m_target_coords + offset;

		m_up = math::QuaternionOps::rotate(
			m_orientation,
			math::Vec3(0.0f, 1.0f, 0.0f)
		);

		calculate_view_matrix();
	}
}