#pragma once


#include "math/linear_algebra/include/linear_algebra_data_types.hpp"
#include <string>


namespace andromeda
{
    /// @brief Defines the interface for a material.
    ///
    /// A material describes the surface properties of a renderable object,
    /// including its name, shininess, and the ambient, diffuse, and specular
    /// components used by lighting calculations.
    class IMaterial
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IMaterial() = default;

        // Getters

        /// @brief Retrieves the material shininess.
        ///
        /// @return Shininess exponent used for specular highlights.
        virtual float get_shininess() const = 0;

        /// @brief Retrieves the material name.
        ///
        /// @return Reference to the material name.
        virtual const std::string& get_name() const = 0;

        /// @brief Retrieves the ambient material component.
        ///
        /// @return Reference to the ambient RGB component.
        virtual const math::Vec3& get_ambient() const = 0;

        /// @brief Retrieves the diffuse material component.
        ///
        /// @return Reference to the diffuse RGB component.
        virtual const math::Vec3& get_diffuse() const = 0;

        /// @brief Retrieves the specular material component.
        ///
        /// @return Reference to the specular RGB component.
        virtual const math::Vec3& get_specular() const = 0;

        // Setters

        /// @brief Sets the material shininess.
        ///
        /// @param shininess Shininess exponent used for specular highlights.
        virtual void set_shininess(float shininess) = 0;

        /// @brief Sets the material name.
        ///
        /// @param name Material name.
        virtual void set_name(const std::string& name) = 0;

        /// @brief Sets the ambient material component.
        ///
        /// @param ambient Ambient RGB component.
        virtual void set_ambient(const math::Vec3& ambient) = 0;

        /// @brief Sets the diffuse material component.
        ///
        /// @param diffuse Diffuse RGB component.
        virtual void set_diffuse(const math::Vec3& diffuse) = 0;

        /// @brief Sets the specular material component.
        ///
        /// @param specular Specular RGB component.
        virtual void set_specular(const math::Vec3& specular) = 0;
    };
}
