#ifndef SPACE__SCENE__SCENE_NODE_MANAGER__HPP
#define SPACE__SCENE__SCENE_NODE_MANAGER__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "../../scene_graph/include/scene_node.hpp"
#include "scene_lighting.hpp"
#include "scene_objects.hpp"
#include "andromeda/space/scene/i_scene_node_manager.hpp"
#include "pch.hpp"

#include <memory>


namespace andromeda::space
{
	class SPACE_API SceneNodeManager
		: public virtual ISceneNodeManager
		, public SceneObjects
		, public SceneLighting
	{
	public:
		SceneNodeManager();
		~SceneNodeManager() override;

		void attach_node(std::unique_ptr<ISceneNode> node) override;

		// Convenience overload for concrete nodes.
		void attach_node(std::unique_ptr<SceneNode> node);

		void add_object(int id, IGeometricObject* object) override;
		void remove_object(int id) override;

	protected:
		void register_node(SceneNode& node);
		void register_node_recursive(SceneNode& node);

	private:
		std::unique_ptr<SceneNode> m_root_node;
	};
}


#endif // SPACE__SCENE__SCENE_NODE_MANAGER__HPP