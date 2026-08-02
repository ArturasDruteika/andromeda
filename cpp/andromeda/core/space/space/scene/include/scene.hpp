#ifndef SPACE__SCENE__SCENE__HPP
#define SPACE__SCENE__SCENE__HPP


#include "camera_handler.hpp"
#include "scene_environment.hpp"
#include "scene_lighting.hpp"
#include "scene_objects.hpp"
#include "scene_state.hpp"
#include "scene_node_manager.hpp"
#include "scene_update_hooks.hpp"
#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/scene/i_scene.hpp"
#include "pch.hpp"

#include <functional>


namespace andromeda::space
{
	/// @brief Represents the complete scene managed by the engine.
	///
	/// Combines camera management, scene environment, scene graph, object and
	/// lighting management, state tracking, and update callbacks into a single
	/// scene implementation.
	class SPACE_API Scene
		: public IScene
		, public CameraHandler
		, public SceneEnvironment
		, public SceneState
		, public SceneNodeManager
		, public SceneUpdateHooksManager
	{
	public:
		/// @brief Constructs a scene.
		Scene();

		/// @brief Destroys the scene.
		~Scene() override;

		// Getters

		/// @brief Retrieves the center point of the scene.
		///
		/// @return Scene center in world space.
		const math::Vec3& get_scene_center() const override;

		/// @brief Removes all objects and resets the scene.
		void clear_scene() override;

		/// @brief Resets the tracked scene state.
		void reset_scene_state() override;

		/// @brief Updates the scene.
		///
		/// Executes registered update callbacks and updates scene state.
		///
		/// @param delta_time Time elapsed since the previous update, in seconds.
		void update(float delta_time) override;

	private:
		/// @brief Center point of the scene in world space.
		math::Vec3 m_scene_center;
	};
}


#endif // API_SCENE__I_SCENE__HPP