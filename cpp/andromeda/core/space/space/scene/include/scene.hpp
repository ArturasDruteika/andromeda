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
	class SPACE_API Scene
		: public IScene
		, public CameraHandler
		, public SceneEnvironment
		, public SceneState
		, public SceneNodeManager
		, public SceneUpdateHooksManager
	{
	public:
		Scene();
		~Scene() override;

		// Getters
		const math::Vec3& get_scene_center() const override;

		void clear_scene() override;
		void reset_scene_state() override;
		void update(float delta_time) override;

	private:
		math::Vec3 m_scene_center;
	};
}


#endif // API_SCENE__I_SCENE__HPP