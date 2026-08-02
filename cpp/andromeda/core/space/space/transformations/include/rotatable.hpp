#pragma once


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/transformations/i_rotatable.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"
#include "math/linear_algebra/include/quaternions.hpp"


namespace andromeda
{
    /// @brief Provides rotation functionality for transformable objects.
    ///
    /// Stores object orientation as a quaternion while exposing Euler angles
    /// and a rotation matrix for convenience.
    class SPACE_API Rotatable
        : public virtual IRotatable
    {
    public:
        /// @brief Constructs a rotatable object.
        Rotatable();

        /// @brief Destroys the rotatable object.
        ~Rotatable() override;

        // Getters

        /// @brief Checks whether the rotation state has changed.
        ///
        /// @return `true` if the rotation has changed since the last reset;
        /// otherwise, `false`.
        bool state_changed() const override;

        /// @brief Retrieves the current Euler rotation.
        ///
        /// @return Rotation expressed as Euler angles in radians.
        const math::Vec3& get_rotation() const override;

        /// @brief Retrieves the rotation matrix.
        ///
        /// @return Rotation matrix derived from the current orientation.
        const math::Mat4& get_rotation_matrix() const override;

        /// @brief Retrieves the current orientation.
        ///
        /// @return Orientation quaternion.
        const math::Quaternion& get_orientation() const override;

        // Setters

        /// @brief Resets the rotation state change flag.
        void reset_state() override;

        /// @brief Sets the rotation using Euler angles.
        ///
        /// @param rotation Rotation expressed as Euler angles in radians.
        void set_rotation(const math::Vec3& rotation) override;

        /// @brief Applies an incremental Euler rotation.
        ///
        /// @param rotation Rotation offset expressed as Euler angles in radians.
        void rotate(const math::Vec3& rotation) override;

        /// @brief Applies an incremental quaternion rotation.
        ///
        /// @param delta Rotation offset represented as a quaternion.
        void rotate(const math::Quaternion& delta) override;

        /// @brief Rotates around the X axis.
        ///
        /// @param angle Rotation angle in radians.
        void rotate_x(float angle) override;

        /// @brief Rotates around the Y axis.
        ///
        /// @param angle Rotation angle in radians.
        void rotate_y(float angle) override;

        /// @brief Rotates around the Z axis.
        ///
        /// @param angle Rotation angle in radians.
        void rotate_z(float angle) override;

    protected:
        /// @brief Updates cached rotation data derived from the orientation.
        ///
        /// Recomputes the Euler angles and rotation matrix from the current
        /// orientation quaternion.
        void update_rotation_derived_data();

    private:
        /// @brief Indicates whether the rotation state has changed.
        bool m_state_changed;

        /// @brief Cached Euler rotation in radians.
        math::Vec3 m_rotation;

        /// @brief Cached rotation matrix.
        math::Mat4 m_rotation_matrix;

        /// @brief Orientation stored as a quaternion.
        math::Quaternion m_orientation;
    };
}
