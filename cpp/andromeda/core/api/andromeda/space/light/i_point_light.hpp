#ifndef ANDROMEDA__LIGHT__POINT_LIGHT__HPP
#define ANDROMEDA__LIGHT__POINT_LIGHT__HPP


#include "i_light.hpp"
#include "../objects/i_light_object.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda
{
    /// @brief Defines the interface for a point light.
    ///
    /// A point light emits light uniformly in all directions from a single
    /// position in world space. It provides attenuation parameters for light
    /// falloff and shadow mapping configuration.
    class IPointLight
        : public virtual ILight
        , public virtual ILightObject
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IPointLight() = default;

        // Getters

        /// @brief Retrieves the constant attenuation factor.
        ///
        /// @return Constant attenuation coefficient.
        virtual float get_attenuation_constant() const = 0;

        /// @brief Retrieves the linear attenuation factor.
        ///
        /// @return Linear attenuation coefficient.
        virtual float get_attenuation_linear() const = 0;

        /// @brief Retrieves the quadratic attenuation factor.
        ///
        /// @return Quadratic attenuation coefficient.
        virtual float get_attenuation_quadratic() const = 0;

        /// @brief Retrieves the near clipping plane used for shadow mapping.
        ///
        /// @return Shadow near clipping plane distance.
        virtual float get_shadow_near_plane() const = 0;

        /// @brief Retrieves the far clipping plane used for shadow mapping.
        ///
        /// @return Shadow far clipping plane distance.
        virtual float get_shadow_far_plane() const = 0;

        /// @brief Retrieves the light position in world space.
        ///
        /// @return Reference to the light position.
        virtual const math::Vec3& get_position() const = 0;

        // Setters

        /// @brief Sets the constant attenuation factor.
        ///
        /// @param attenuation_constant Constant attenuation coefficient.
        virtual void set_attenuation_constant(float attenuation_constant) = 0;

        /// @brief Sets the linear attenuation factor.
        ///
        /// @param attenuation_linear Linear attenuation coefficient.
        virtual void set_attenuation_linear(float attenuation_linear) = 0;

        /// @brief Sets the quadratic attenuation factor.
        ///
        /// @param attenuation_quadratic Quadratic attenuation coefficient.
        virtual void set_attenuation_quadratic(float attenuation_quadratic) = 0;

        /// @brief Sets the near clipping plane used for shadow mapping.
        ///
        /// @param shadow_near_plane Shadow near clipping plane distance.
        virtual void set_shadow_near_plane(float shadow_near_plane) = 0;

        /// @brief Sets the far clipping plane used for shadow mapping.
        ///
        /// @param shadow_far_plane Shadow far clipping plane distance.
        virtual void set_shadow_far_plane(float shadow_far_plane) = 0;

        /// @brief Sets the light position in world space.
        ///
        /// @param position Light position.
        virtual void set_position(const math::Vec3& position) = 0;
    };
}


#endif // ANDROMEDA__LIGHT__POINT_LIGHT__HPP