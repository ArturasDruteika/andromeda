#ifndef API__SCENE__I_SCENE__HPP
#define API__SCENE__I_SCENE__HPP


#include "i_camera_handler.hpp"
#include "i_scene_environment.hpp"
#include "i_scene_node_manager.hpp"
#include "i_scene_state.hpp"


namespace Andromeda
{
	class IScene
		: public virtual ICameraHandler
		, public virtual ISceneEnvironment
		, public virtual ISceneNodeManager
		, public virtual ISceneState
	{
	public:
		virtual ~IScene() = default;

		virtual const Math::Vec3& get_scene_center() const = 0;

		virtual void clear_scene() = 0;
		virtual void reset_scene_state() = 0;
		virtual void update(float delta_time) = 0;
	};
}


#endif // API_SCENE__I_SCENE__HPP