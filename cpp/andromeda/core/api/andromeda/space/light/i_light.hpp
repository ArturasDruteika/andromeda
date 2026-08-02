#pragma once


#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda
{
    /// @brief Defines the common interface for light sources.
    ///
    /// Provides access to the lighting properties shared by all light types,
    /// including intensity, color, and the ambient, diffuse, and specular
    /// components used by lighting calculations.
    class ILight
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ILight() = default;

        // Getters

        /// @brief Retrieves the light intensity.
        ///
        /// @return Intensity multiplier of the light source.
        virtual float get_intensity() const = 0;

        /// @brief Retrieves the light color.
        ///
        /// @return RGB color of the light.
        virtual math::Vec3 get_color() const = 0;

        /// @brief Retrieves the ambient lighting component.
        ///
        /// @return Ambient RGB component.
        virtual math::Vec3 get_ambient() const = 0;

        /// @brief Retrieves the diffuse lighting component.
        ///
        /// @return Diffuse RGB component.
        virtual math::Vec3 get_diffuse() const = 0;

        /// @brief Retrieves the specular lighting component.
        ///
        /// @return Specular RGB component.
        virtual math::Vec3 get_specular() const = 0;

        // Setters

        /// @brief Sets the light intensity.
        ///
        /// @param intensity Intensity multiplier of the light source.
        virtual void set_intensity(float intensity) = 0;

        /// @brief Sets the light color.
        ///
        /// @param color RGB color of the light.
        virtual void set_color(const math::Vec3& color) = 0;

        /// @brief Sets the ambient lighting component.
        ///
        /// @param ambient Ambient RGB component.
        virtual void set_ambient(const math::Vec3& ambient) = 0;

        /// @brief Sets the diffuse lighting component.
        ///
        /// @param diffuse Diffuse RGB component.
        virtual void set_diffuse(const math::Vec3& diffuse) = 0;

        /// @brief Sets the specular lighting component.
        ///
        /// @param specular Specular RGB component.
        virtual void set_specular(const math::Vec3& specular) = 0;
    };
}
