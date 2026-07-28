#ifndef SPACE__SCENE__SCENE_STATE__HPP
#define SPACE__SCENE__SCENE_STATE__HPP


#include "../../objects/include/geometric_object.hpp"
#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/scene/i_scene_state.hpp"


namespace andromeda::space
{
	class SPACE_API SceneState
		: public virtual ISceneState
	{
	public:
		SceneState();
		~SceneState() override;

		bool state_changed(const std::unordered_map<int, IGeometricObject*>& objects) const override;
	};
}


#endif // SPACE__SCENE__SCENE_STATE__HPP