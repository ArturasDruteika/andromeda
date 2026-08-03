#pragma once


#include "math/linear_algebra/include/linear_algebra_data_types.hpp"
#include "math/linear_algebra/include/quaternions.hpp"


namespace andromeda
{
    /// @brief Defines the interface for a rotatable object.
    ///
    /// Provides access to an object's orientation, rotation matrix, and Euler
    /// angles, along with operations for modifying its rotation.
    class IRotatable
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IRotatable() = default;

        // Getters

        /// @brief Checks whether the rotation state has changed.
        ///
        /// @return `true` if the rotation has changed since the last reset;
        /// otherwise, `false`.
        virtual bool state_changed() const = 0;

        /// @brief Retrieves the current rotation as Euler angles.
        ///
        /// @return Reference to the rotation vector.
        virtual const math::Vec3& get_rotation() const = 0;

        /// @brief Retrieves the rotation matrix.
        ///
        /// @return Reference to the rotation transformation matrix.
        virtual const math::Mat4& get_rotation_matrix() const = 0;

        /// @brief Retrieves the object orientation.
        ///
        /// @return Reference to the orientation quaternion.
        virtual const math::Quaternion& get_orientation() const = 0;

        // Setters

        /// @brief Resets the rotation change state.
        virtual void reset_state() = 0;

        /// @brief Sets the rotation using Euler angles.
        ///
        /// @param rotation Rotation expressed as Euler angles.
        virtual void set_rotation(const math::Vec3& rotation) = 0;

        /// @brief Applies a rotation using Euler angles.
        ///
        /// @param rotation Rotation offset expressed as Euler angles.
        virtual void rotate(const math::Vec3& rotation) = 0;

        /// @brief Applies a rotation using a quaternion.
        ///
        /// @param delta Rotation quaternion to apply.
        virtual void rotate(const math::Quaternion& delta) = 0;

        /// @brief Rotates around the X axis.
        ///
        /// @param angle Rotation angle.
        virtual void rotate_x(float angle) = 0;

        /// @brief Rotates around the Y axis.
        ///
        /// @param angle Rotation angle.
        virtual void rotate_y(float angle) = 0;

        /// @brief Rotates around the Z axis.
        ///
        /// @param angle Rotation angle.
        virtual void rotate_z(float angle) = 0;
    };
}
