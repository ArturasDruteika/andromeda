#pragma once


#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda
{
    /// @brief Defines the interface for controlling a camera's perspective.
    ///
    /// Provides access to perspective projection parameters and the projection
    /// matrix, along with methods for updating those parameters.
    class IPerspectiveControl
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IPerspectiveControl() = default;

        // Getters

        /// @brief Retrieves the vertical field of view.
        ///
        /// @return Field of view in degrees.
        virtual float get_field_of_view_degrees() const = 0;

        /// @brief Retrieves the near clipping plane distance.
        ///
        /// @return Near clipping plane distance.
        virtual float get_near_plane() const = 0;

        /// @brief Retrieves the far clipping plane distance.
        ///
        /// @return Far clipping plane distance.
        virtual float get_far_plane() const = 0;

        /// @brief Retrieves the viewport aspect ratio.
        ///
        /// @return Width-to-height aspect ratio.
        virtual float get_aspect() const = 0;

        /// @brief Retrieves the projection matrix.
        ///
        /// @return Reference to the projection matrix.
        virtual const math::Mat4& get_projection() const = 0;

        // Setters

        /// @brief Sets the vertical field of view.
        ///
        /// @param fov_deg Field of view in degrees.
        /// @param update_projection If `true`, updates the projection matrix
        ///                          immediately.
        virtual void set_field_of_view_degrees(float fov_deg, bool update_projection = true) = 0;

        /// @brief Sets the near clipping plane distance.
        ///
        /// @param near_plane Near clipping plane distance.
        /// @param update_projection If `true`, updates the projection matrix
        ///                          immediately.
        virtual void set_near_plane(float near_plane, bool update_projection = true) = 0;

        /// @brief Sets the far clipping plane distance.
        ///
        /// @param far_plane Far clipping plane distance.
        /// @param update_projection If `true`, updates the projection matrix
        ///                          immediately.
        virtual void set_far_plane(float far_plane, bool update_projection = true) = 0;

        /// @brief Sets the viewport aspect ratio.
        ///
        /// @param aspect Width-to-height aspect ratio.
        /// @param update_projection If `true`, updates the projection matrix
        ///                          immediately.
        virtual void set_aspect(float aspect, bool update_projection = true) = 0;

        // Update

        /// @brief Recomputes the projection matrix.
        ///
        /// Applies the current perspective parameters to generate a new
        /// projection matrix.
        virtual void update_projection() = 0;
    };
}
