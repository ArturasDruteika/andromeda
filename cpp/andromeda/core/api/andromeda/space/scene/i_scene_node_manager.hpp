#ifndef API__SCENE__I_SCENE_NODE_MANAGER__HPP
#define API__SCENE__I_SCENE_NODE_MANAGER__HPP


#include "andromeda/space/scene/i_scene_lighting.hpp"
#include "andromeda/space/scene/i_scene_objects.hpp"
#include "andromeda/space/scene_graph/i_scene_node.hpp"

#include <memory>


namespace andromeda
{
	class ISceneNodeManager
		: public virtual ISceneObjects
		, public virtual ISceneLighting
	{
	public:
		virtual ~ISceneNodeManager() = default;

		virtual void attach_node(std::unique_ptr<ISceneNode> node) = 0;
	};
}


#endif // API__SCENE__I_SCENE_NODE_MANAGER__HPP