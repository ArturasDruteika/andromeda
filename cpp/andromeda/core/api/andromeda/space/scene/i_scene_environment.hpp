#pragma once


#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda
{
    /// @brief Defines the interface for scene environment settings.
    ///
    /// Provides access to global scene properties such as ambient lighting,
    /// background color, and environment-specific operations.
    class ISceneEnvironment
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ISceneEnvironment() = default;

        // Getters

        /// @brief Retrieves the ambient light strength.
        ///
        /// @return Ambient lighting intensity.
        virtual float get_ambient_strength() const = 0;

        /// @brief Retrieves the scene background color.
        ///
        /// @return Reference to the RGBA background color.
        virtual const math::Vec4& get_background_color() const = 0;

        // Setters

        /// @brief Sets the ambient light strength.
        ///
        /// @param ambient_strength Ambient lighting intensity.
        virtual void set_ambient_strength(float ambient_strength) = 0;

        /// @brief Sets the scene background color.
        ///
        /// @param background_color RGBA background color.
        virtual void set_background_color(const math::Vec4& background_color) = 0;

        /// @brief Resizes the scene grid.
        ///
        /// @param resize_factor Factor by which to scale the grid size.
        virtual void resize_grid(float resize_factor) = 0;
    };
}
