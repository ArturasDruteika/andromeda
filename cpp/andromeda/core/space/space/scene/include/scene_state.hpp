#pragma once


#include "../../objects/include/geometric_object.hpp"
#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/scene/i_scene_state.hpp"


namespace andromeda::space
{
	/// @brief Tracks whether the scene has changed.
	///
	/// Provides functionality for determining whether any scene object has
	/// changed state and therefore requires the scene to be updated or
	/// re-rendered.
	class SPACE_API SceneState
		: public virtual ISceneState
	{
	public:
		/// @brief Constructs a scene state tracker.
		SceneState();

		/// @brief Destroys the scene state tracker.
		~SceneState() override;

		/// @brief Checks whether the scene state has changed.
		///
		/// @param objects Collection of scene objects to inspect.
		/// @return `true` if any object has changed state; otherwise, `false`.
		bool state_changed(const std::unordered_map<int, IGeometricObject*>& objects) const override;
	};
}
