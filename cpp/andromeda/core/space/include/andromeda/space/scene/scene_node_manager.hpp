#pragma once


#include "andromeda/space/macro_export/macro_export.hpp"
#include "../scene_graph/scene_node.hpp"
#include "scene_lighting.hpp"
#include "scene_objects.hpp"
#include "andromeda/space/scene/i_scene_node_manager.hpp"
#include "andromeda/space/light/i_point_light.hpp"
#include "andromeda/space/transformations/i_transformable.hpp"

#include <memory>
#include <unordered_map>
#include <utility>


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

		/// @brief Synchronizes positional lights with their scene node transforms.
		///
		/// Point lights attached through a LightComponent take their position
		/// from the owning node, so moving the node moves the light.
		void sync_light_transforms();

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

		/// @brief Point lights paired with the transform of their owning node.
		std::unordered_map<int, std::pair<IPointLight*, const ITransformable*>> m_point_light_transforms;
	};
}
