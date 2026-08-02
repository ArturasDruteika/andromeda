#ifndef ANDROMEDA__LIGHT__I_DIRECTIONAL_LIGHT__HPP
#define ANDROMEDA__LIGHT__I_DIRECTIONAL_LIGHT__HPP


#include "i_light.hpp"
#include "../objects/i_light_object.hpp"
#include "../transformations/i_rotatable.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda
{
    /// @brief Defines the interface for a directional light.
    ///
    /// A directional light represents a light source with parallel rays,
    /// typically used to simulate sunlight. It provides controls for light
    /// direction and the orthographic projection parameters used for shadow
    /// mapping.
    class IDirectionalLight
        : public virtual ILight
        , public virtual ILightObject
        , public virtual IRotatable
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IDirectionalLight() = default;

        // Getters

        /// @brief Retrieves the half-size of the orthographic projection.
        ///
        /// @return Half-size of the light's orthographic projection volume.
        virtual float get_light_orthographic_half_size() const = 0;

        /// @brief Retrieves the near clipping plane of the light projection.
        ///
        /// @return Near clipping plane distance.
        virtual float get_light_near_plane() const = 0;

        /// @brief Retrieves the far clipping plane of the light projection.
        ///
        /// @return Far clipping plane distance.
        virtual float get_light_far_plane() const = 0;

        /// @brief Retrieves the light direction in world space.
        ///
        /// The returned vector should be normalized.
        ///
        /// @return Reference to the light direction vector.
        virtual const math::Vec3& get_direction() const = 0;

        // Setters

        /// @brief Sets the half-size of the orthographic projection.
        ///
        /// @param half_size Half-size of the orthographic projection volume.
        virtual void set_light_orthographic_half_size(float half_size) = 0;

        /// @brief Sets the near clipping plane of the light projection.
        ///
        /// @param near_plane Near clipping plane distance.
        virtual void set_light_near_plane(float near_plane) = 0;

        /// @brief Sets the far clipping plane of the light projection.
        ///
        /// @param far_plane Far clipping plane distance.
        virtual void set_light_far_plane(float far_plane) = 0;

        /// @brief Sets the light direction in world space.
        ///
        /// The provided direction should be normalized.
        ///
        /// @param direction Direction vector.
        virtual void set_direction(const math::Vec3& direction) = 0;
    };
}


#endif // ANDROMEDA__LIGHT__I_DIRECTIONAL_LIGHT__HPP