#pragma once


#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda
{
    /// @brief Defines the interface for a scalable object.
    ///
    /// Provides access to an object's scale and scale transformation matrix,
    /// along with operations for modifying its scale.
    class IScalable
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IScalable() = default;

        // Getters

        /// @brief Checks whether the scale state has changed.
        ///
        /// @return `true` if the scale has changed since the last reset;
        /// otherwise, `false`.
        virtual bool state_changed() const = 0;

        /// @brief Retrieves the current scale.
        ///
        /// @return Reference to the scale vector.
        virtual const math::Vec3& get_scale() const = 0;

        /// @brief Retrieves the scale transformation matrix.
        ///
        /// @return Reference to the scale transformation matrix.
        virtual const math::Mat4& get_scale_matrix() const = 0;

        // Setters

        /// @brief Resets the scale change state.
        virtual void reset_state() = 0;

        /// @brief Sets the object scale.
        ///
        /// @param scale New scale vector.
        virtual void set_scale(const math::Vec3& scale) = 0;

        /// @brief Applies a non-uniform scale.
        ///
        /// @param scale Scale factor for each axis.
        virtual void scale(const math::Vec3& scale) = 0;

        /// @brief Applies a uniform scale.
        ///
        /// @param uniform_scale Uniform scale factor.
        virtual void scale(float uniform_scale) = 0;
    };
}
