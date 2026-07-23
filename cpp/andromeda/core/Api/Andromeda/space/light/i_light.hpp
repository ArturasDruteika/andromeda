#ifndef ANDROMEDA__LIGHT_TYPES__HPP
#define ANDROMEDA__LIGHT_TYPES__HPP


#include "Math/LinearAlgebra/include/linear_algebra_data_types.hpp"


namespace Andromeda
{
	class ILight
	{
	public:
		virtual ~ILight() = default;

		// Getters
		virtual float get_intensity() const = 0;
		virtual Math::Vec3 get_color() const = 0;
		virtual Math::Vec3 get_ambient() const = 0;
		virtual Math::Vec3 get_diffuse() const = 0;
		virtual Math::Vec3 get_specular() const = 0;
		// Setters
		virtual void set_intensity(float intensity) = 0;
		virtual void set_color(const Math::Vec3& color) = 0;
		virtual void set_ambient(const Math::Vec3& ambient) = 0;
		virtual void set_diffuse(const Math::Vec3& diffuse) = 0;
		virtual void set_specular(const Math::Vec3& specular) = 0;
	};
}


#endif // ANDROMEDA__LIGHT_TYPES__HPP