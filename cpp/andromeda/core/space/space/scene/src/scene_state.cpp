#include "../include/scene_state.hpp"


namespace andromeda::space
{
	SceneState::SceneState() = default;

	SceneState::~SceneState() = default;

	bool SceneState::state_changed(const std::unordered_map<int, IGeometricObject*>& objects) const
	{
		// TODO: Implement state change detection logic based on nodes, not the object itself
		//for (const auto& [id, object] : objects)
		//{
		//	if (object->state_changed())
		//	{
		//		return true;
		//	}
		//}
		//return false;
		return false;
	}
}