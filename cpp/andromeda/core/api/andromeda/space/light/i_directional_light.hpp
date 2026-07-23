#ifndef ANDROMEDA__LIGHT__I_DIRECTIONAL_LIGHT__HPP
#define ANDROMEDA__LIGHT__I_DIRECTIONAL_LIGHT__HPP

#include "i_light.hpp"
#include "../objects/i_light_object.hpp"
#include "../transformations/i_rotatable.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"

namespace andromeda
{
    class IDirectionalLight
		: public virtual ILight
		, public virtual ILightObject
		, public virtual IRotatable
    {
    public:
        virtual ~IDirectionalLight() = default;

        // Shadow / projection parameters (commonly used for directional light shadow maps)
        virtual float get_light_orthographic_half_size() const = 0;
        virtual float get_light_near_plane() const = 0;
        virtual float get_light_far_plane() const = 0;

        virtual void set_light_orthographic_half_size(float half_size) = 0;
        virtual void set_light_near_plane(float near_plane) = 0;
        virtual void set_light_far_plane(float far_plane) = 0;

        // Direction of the light in world space (should be normalized)
        virtual const math::Vec3& get_direction() const = 0;
        virtual void set_direction(const math::Vec3& direction) = 0;
    };
}

#endif // ANDROMEDA__LIGHT__I_DIRECTIONAL_LIGHT__HPP