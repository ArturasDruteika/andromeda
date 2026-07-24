#include "../include/rotatable.hpp"
#include "math/linear_algebra/include/quaternions.hpp"


namespace andromeda
{
    Rotatable::Rotatable()
        : m_state_changed{ false }
        , m_rotation{ 0.0f }
        , m_rotation_matrix{}
        , m_orientation(math::Quaternion::identity())
    {
        update_rotation_derived_data();
    }

    Rotatable::~Rotatable() = default;

    bool Rotatable::state_changed() const
    {
        return m_state_changed;
    }

    const math::Vec3& Rotatable::get_rotation() const
    {
        return m_rotation;
    }

    const math::Mat4& Rotatable::get_rotation_matrix() const
    {
        return m_rotation_matrix;
    }

    const math::Quaternion& Rotatable::get_orientation() const
    {
        return m_orientation;
    }

    void Rotatable::reset_state()
    {
        m_state_changed = false;
    }

    void Rotatable::set_rotation(const math::Vec3& rotation)
    {
        // rotation is Euler XYZ in radians
        m_orientation = math::QuaternionOps::from_euler_xyz(rotation[0], rotation[1], rotation[2]);
        m_orientation = math::QuaternionOps::normalize(m_orientation);

        update_rotation_derived_data();
        m_state_changed = true;
    }

    void Rotatable::rotate(const math::Vec3& rotation)
    {
        // rotation is Euler delta XYZ in radians
        const math::Quaternion delta =
            math::QuaternionOps::from_euler_xyz(rotation[0], rotation[1], rotation[2]);

        rotate(delta);
    }

    void Rotatable::rotate(const math::Quaternion& delta)
    {
        // Apply delta in local space: new = delta * current
        m_orientation = math::QuaternionOps::multiply(delta, m_orientation);
        m_orientation = math::QuaternionOps::normalize(m_orientation);

        update_rotation_derived_data();
        m_state_changed = true;
    }

    void Rotatable::rotate_x(float angle)
    {
        rotate(math::QuaternionOps::angle_axis(angle, math::Vec3(1.0f, 0.0f, 0.0f)));
    }

    void Rotatable::rotate_y(float angle)
    {
        rotate(math::QuaternionOps::angle_axis(angle, math::Vec3(0.0f, 1.0f, 0.0f)));
    }

    void Rotatable::rotate_z(float angle)
    {
        rotate(math::QuaternionOps::angle_axis(angle, math::Vec3(0.0f, 0.0f, 1.0f)));
    }

    void Rotatable::update_rotation_derived_data()
    {
        // Euler is derived for UI/debug only
        m_rotation = math::QuaternionOps::to_euler_xyz(m_orientation);

        // Rotation matrix derived from quaternion
        m_rotation_matrix = math::QuaternionOps::to_mat4(m_orientation);
    }
}