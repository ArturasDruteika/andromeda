#include "../include/Rotatable.hpp"
#include "math/linear_algebra/include/quaternions.hpp"


namespace andromeda
{
    Rotatable::Rotatable()
        : m_stateChanged{ false }
        , m_rotation{ 0.0f }
        , m_rotationMatrix{}
        , m_orientation(math::Quaternion::Identity())
    {
        UpdateRotationDerivedData();
    }

    Rotatable::~Rotatable() = default;

    bool Rotatable::StateChanged() const
    {
        return m_stateChanged;
    }

    const math::Vec3& Rotatable::GetRotation() const
    {
        return m_rotation;
    }

    const math::Mat4& Rotatable::GetRotationMatrix() const
    {
        return m_rotationMatrix;
    }

    const math::Quaternion& Rotatable::GetOrientation() const
    {
        return m_orientation;
    }

    void Rotatable::ResetState()
    {
        m_stateChanged = false;
    }

    void Rotatable::SetRotation(const math::Vec3& rotation)
    {
        // rotation is Euler XYZ in radians
        m_orientation = math::QuaternionOps::FromEulerXYZ(rotation[0], rotation[1], rotation[2]);
        m_orientation = math::QuaternionOps::Normalize(m_orientation);

        UpdateRotationDerivedData();
        m_stateChanged = true;
    }

    void Rotatable::Rotate(const math::Vec3& rotation)
    {
        // rotation is Euler delta XYZ in radians
        const math::Quaternion delta = math::QuaternionOps::FromEulerXYZ(rotation[0], rotation[1], rotation[2]);

        Rotate(delta);
    }

    void Rotatable::Rotate(const math::Quaternion& delta)
    {
        // Apply delta in local space: new = delta * current
        m_orientation = math::QuaternionOps::Multiply(delta, m_orientation);
        m_orientation = math::QuaternionOps::Normalize(m_orientation);

        UpdateRotationDerivedData();
        m_stateChanged = true;
    }

    void Rotatable::RotateX(float angle)
    {
        Rotate(math::QuaternionOps::AngleAxis(angle, math::Vec3(1.0f, 0.0f, 0.0f)));
    }

    void Rotatable::RotateY(float angle)
    {
        Rotate(math::QuaternionOps::AngleAxis(angle, math::Vec3(0.0f, 1.0f, 0.0f)));
    }

    void Rotatable::RotateZ(float angle)
    {
        Rotate(math::QuaternionOps::AngleAxis(angle, math::Vec3(0.0f, 0.0f, 1.0f)));
    }

    void Rotatable::UpdateRotationDerivedData()
    {
        // Euler is derived for UI/debug only
        m_rotation = math::QuaternionOps::ToEulerXYZ(m_orientation);

        // Rotation matrix derived from quaternion
        m_rotationMatrix = math::QuaternionOps::ToMat4(m_orientation);
    }
}
