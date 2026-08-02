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
	/// @brief Manages the scene graph and registered scene objects.
	///
	/// Owns the root scene node and is responsible for attaching nodes,
	/// registering objects, and maintaining the scene's object and lighting
	/// collections.
	class SPACE_API SceneNodeManager
		: public virtual ISceneNodeManager
		, public SceneObjects
		, public SceneLighting
	{
	public:
		/// @brief Constructs a scene node manager.
		SceneNodeManager();

		/// @brief Destroys the scene node manager.
		~SceneNodeManager() override;

		/// @brief Attaches a scene node to the scene graph.
		///
		/// @param node Node to attach.
		void attach_node(std::unique_ptr<ISceneNode> node) override;

		/// @brief Attaches a concrete scene node to the scene graph.
		///
		/// @param node Node to attach.
		void attach_node(std::unique_ptr<SceneNode> node);

		/// @brief Registers a geometric object with the scene.
		///
		/// @param id Object identifier.
		/// @param object Pointer to the geometric object.
		void add_object(int id, IGeometricObject* object) override;

		/// @brief Removes a geometric object from the scene.
		///
		/// @param id Identifier of the object to remove.
		void remove_object(int id) override;

	protected:
		/// @brief Registers a scene node.
		///
		/// @param node Node to register.
		void register_node(SceneNode& node);

		/// @brief Recursively registers a scene node and its descendants.
		///
		/// @param node Root node of the subtree to register.
		void register_node_recursive(SceneNode& node);

	private:
		/// @brief Root node of the scene graph.
		std::unique_ptr<SceneNode> m_root_node;
	};
}


#endif // SPACE__SCENE__SCENE_NODE_MANAGER__HPP