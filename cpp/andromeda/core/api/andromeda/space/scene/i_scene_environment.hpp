#ifndef API__SCENE__I_SCENE_API__SCENE__HPP
#define API__SCENE__I_SCENE_API__SCENE__HPP


#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda
{
	class ISceneEnvironment
	{
	public:
		virtual ~ISceneEnvironment() = default;

		// Getters
		virtual float get_ambient_strength() const = 0;
		virtual const math::Vec4& get_background_color() const = 0;
		// Setters
		virtual void set_ambient_strength(float ambient_strength) = 0;
		virtual void set_background_color(const math::Vec4& background_color) = 0;

		virtual void resize_grid(float resize_factor) = 0;
	};
}


#endif // API__SCENE__I_SCENE_API__SCENE__HPP