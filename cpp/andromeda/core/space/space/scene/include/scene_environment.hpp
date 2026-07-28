#ifndef SPACE__SCENE__SCENE_API__SCENE__HPP
#define SPACE__SCENE__SCENE_API__SCENE__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/scene/i_scene_environment.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda::space
{
	class SPACE_API SceneEnvironment
		: public virtual ISceneEnvironment
	{
	public:
		SceneEnvironment();
		~SceneEnvironment() override;

		// Getters
		float get_ambient_strength() const override;
		const math::Vec4& get_background_color() const override;
		// Setters
		void set_ambient_strength(float ambient_strength) override;
		void set_background_color(const math::Vec4& background_color) override;

		void resize_grid(float resize_factor) override;

	protected:
		float m_ambient_strength;
		math::Vec4 m_background_color;
	};
}


#endif // SPACE__SCENE__SCENE_API__SCENE__HPP