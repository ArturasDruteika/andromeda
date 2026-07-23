#ifndef SPACE__SCENE__SCENE_API__SCENE__HPP
#define SPACE__SCENE__SCENE_API__SCENE__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "andromeda/space/scene/i_scene_environment.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda::Space
{
	class SPACE_API SceneEnvironment
		: public virtual ISceneEnvironment
	{
	public:
		SceneEnvironment();
		~SceneEnvironment() override;

		// Getters
		float GetAmbientStrength() const override;
		const math::Vec4& GetBackgroundColor() const override;
		// Setters
		void SetAmbientStrength(float ambientStrength) override;
		void SetBackgroundColor(const math::Vec4& backroundColor) override;

		void ResizeGrid(float resizeFactor) override;

	protected:
		float m_ambientStrength;
		math::Vec4 m_backgroundColor;
	};
}


#endif // SPACE__SCENE__SCENE_API__SCENE__HPP