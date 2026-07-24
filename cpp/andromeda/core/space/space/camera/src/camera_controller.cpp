#include "../include/CameraController.hpp"
#include "math/linear_algebra/include/linear_algebra_operations.hpp"


namespace andromeda::Space
{
	CameraController::CameraController(const math::Vec3& position, const math::Vec3& targetCoords)
		: CameraView(position, targetCoords)
		, m_distance{ math::LinAlgOps::Length(position - targetCoords) }
		, m_orientation{ math::Quaternion(1.0f, 0.0f, 0.0f, 0.0f) }
	{
	}

    CameraController::~CameraController() = default;

    void CameraController::Rotate(float yaw, float pitch, float roll)
    {
        // Get camera local axis
        math::Vec3 right = math::QuaternionOps::Rotate(m_orientation, math::Vec3(1, 0, 0));
        math::Vec3 up = math::QuaternionOps::Rotate(m_orientation, math::Vec3(0, 1, 0));
        math::Vec3 forward = math::QuaternionOps::Rotate(m_orientation, math::Vec3(0, 0, -1));

        if (roll != 0.0f)
        {
            // Roll: rotate around forward
            math::Quaternion qRoll = math::QuaternionOps::AngleAxis(roll, forward);
            m_orientation = math::QuaternionOps::Normalize(math::QuaternionOps::Multiply(qRoll, m_orientation));
        }
        else
        {
            // Yaw: rotate around up
            math::Quaternion qYaw = math::QuaternionOps::AngleAxis(-yaw, up);
            // Pitch: rotate around right
            math::Quaternion qPitch = math::QuaternionOps::AngleAxis(-pitch, right);
            m_orientation = math::QuaternionOps::Normalize(
                math::QuaternionOps::Multiply(
                    math::QuaternionOps::Multiply(qYaw, qPitch), m_orientation)
            );
        }

        UpdateDirection();
    }

    void CameraController::Zoom(float deltaDistance)
    {
        float previousDistance = m_distance;

        // Exponential zoom
        float zoomFactor = std::exp(deltaDistance * 0.1f);
        m_distance *= zoomFactor;
        m_distance = math::LinAlgOps::Clamp(m_distance, 0.01f, 1e6f);

        UpdateDirection();
    }

  //  void CameraController::SetOnDistanceChange(OnDistanceChange callback)
  //  {
		//// TODO: Implement observer pattern if needed
  //  }

    void CameraController::UpdateDirection()
    {
        // Forward is -Z in local space (OpenGL convention)
        math::Vec3 localOffset(0.0f, 0.0f, m_distance);

        math::Vec3 offset = math::QuaternionOps::Rotate(m_orientation, localOffset);
        m_position = m_targetCoords + offset;

        m_up = math::QuaternionOps::Rotate(m_orientation, math::Vec3(0.0f, 1.0f, 0.0f));

        CalculateViewMatrix();
    }
}
