#include "../include/camera_controller.hpp"
#include "math/linear_algebra/include/linear_algebra_operations.hpp"
#include "spdlog/spdlog.h"


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
		if (yaw != 0.0f)
		{
			// Yaw around the camera's current local up axis.
			math::Vec3 up = math::QuaternionOps::rotate(
				m_orientation,
				math::Vec3(0.0f, 1.0f, 0.0f)
			);

			math::Quaternion q_yaw =
				math::QuaternionOps::angle_axis(-yaw, up);

			m_orientation = math::QuaternionOps::multiply(
				q_yaw,
				m_orientation
			);

			m_orientation =
				math::QuaternionOps::normalize(m_orientation);
		}

		if (pitch != 0.0f)
		{
			// Recalculate right after yaw so pitch uses the new local axis.
			math::Vec3 right = math::QuaternionOps::rotate(
				m_orientation,
				math::Vec3(1.0f, 0.0f, 0.0f)
			);

			math::Quaternion q_pitch =
				math::QuaternionOps::angle_axis(-pitch, right);

			m_orientation = math::QuaternionOps::multiply(
				q_pitch,
				m_orientation
			);

			m_orientation =
				math::QuaternionOps::normalize(m_orientation);
		}

		if (roll != 0.0f)
		{
			// Recalculate forward after yaw and pitch.
			math::Vec3 forward = math::QuaternionOps::rotate(
				m_orientation,
				math::Vec3(0.0f, 0.0f, -1.0f)
			);

			math::Quaternion q_roll =
				math::QuaternionOps::angle_axis(roll, forward);

			m_orientation = math::QuaternionOps::multiply(
				q_roll,
				m_orientation
			);

			m_orientation =
				math::QuaternionOps::normalize(m_orientation);
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
		// Derive all three camera axes from the orientation.
		m_forward = math::LinAlgOps::normalize(
			math::QuaternionOps::rotate(
				m_orientation,
				math::Vec3(0.0f, 0.0f, -1.0f)
			)
		);

		m_right = math::LinAlgOps::normalize(
			math::QuaternionOps::rotate(
				m_orientation,
				math::Vec3(1.0f, 0.0f, 0.0f)
			)
		);

		m_up = math::LinAlgOps::normalize(
			math::QuaternionOps::rotate(
				m_orientation,
				math::Vec3(0.0f, 1.0f, 0.0f)
			)
		);

		// Keep the camera orbiting around the target.
		m_position = m_target_coords - m_forward * m_distance;

		// Do not recalculate the axes using world up here.
		update_view_matrix();
	}
}