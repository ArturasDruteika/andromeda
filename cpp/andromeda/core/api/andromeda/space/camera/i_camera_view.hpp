#pragma once


#include "i_perspective_control.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda
{
    /// @brief Defines the interface for accessing camera view properties.
    ///
    /// Extends the perspective control interface with access to the camera's
    /// spatial information and view transformation.
    class ICameraView
        : public virtual IPerspectiveControl
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ICameraView() = default;

        // Getters

        /// @brief Retrieves the camera position.
        ///
        /// @return Reference to the camera position in world space.
        virtual const math::Vec3& get_position() const = 0;

        /// @brief Retrieves the camera target position.
        ///
        /// @return Reference to the point the camera is looking at.
        virtual const math::Vec3& get_target_coords() const = 0;

        /// @brief Retrieves the camera forward direction.
        ///
        /// @return Reference to the normalized forward vector.
        virtual const math::Vec3& get_forward() const = 0;

        /// @brief Retrieves the camera right direction.
        ///
        /// @return Reference to the normalized right vector.
        virtual const math::Vec3& get_right() const = 0;

        /// @brief Retrieves the camera up direction.
        ///
        /// @return Reference to the normalized up vector.
        virtual const math::Vec3& get_up() const = 0;

        /// @brief Retrieves the camera view matrix.
        ///
        /// @return Reference to the view transformation matrix.
        virtual const math::Mat4& get_view_matrix() const = 0;
    };
}
