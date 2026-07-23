#ifndef ANDROMEDA__LIGHT__POINT_LIGHT__HPP
#define ANDROMEDA__LIGHT__POINT_LIGHT__HPP


#include "i_light.hpp"
#include "../objects/i_light_object.hpp"
#include "Math/LinearAlgebra/include/linear_algebra_data_types.hpp"


namespace Andromeda
{
	class IPointLight
		: public virtual ILight
		, public virtual ILightObject
	{
	public:
		virtual ~IPointLight() = default;

		// Getters
		virtual float get_attenuation_constant() const = 0;
		virtual float get_attenuation_linear() const = 0;
		virtual float get_attenuation_quadratic() const = 0;
		virtual float get_shadow_near_plane() const = 0;
		virtual float get_shadow_far_plane() const = 0;
		virtual const Math::Vec3& get_position() const = 0;
		// Setters
		virtual void set_attenuation_constant(float attenuation_constant) = 0;
		virtual void set_attenuation_linear(float attenuation_linear) = 0;
		virtual void set_attenuation_quadratic(float attenuation_quadratic) = 0;
		virtual void set_shadow_near_plane(float shadow_near_plane) = 0;
		virtual void set_shadow_far_plane(float shadow_far_plane) = 0;
		virtual void set_position(const Math::Vec3& position) = 0;
	};
}


#endif // ANDROMEDA__LIGHT__POINT_LIGHT__HPP