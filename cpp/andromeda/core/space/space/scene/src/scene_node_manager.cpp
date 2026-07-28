#include "../include/scene_node_manager.hpp"
#include "../../transformations/include/transformable.hpp"
#include "../../scene_graph/include/object_component.hpp"
#include "../../scene_graph/include/light_component.hpp"


namespace andromeda::space
{
	SceneNodeManager::SceneNodeManager()
		: m_root_node{ std::make_unique<SceneNode>(std::make_unique<Transformable>()) }
	{
	}

	SceneNodeManager::~SceneNodeManager() = default;

	void SceneNodeManager::attach_node(std::unique_ptr<ISceneNode> node)
	{
		SceneNode* concrete_node = dynamic_cast<SceneNode*>(node.get());
		if (!concrete_node)
		{
			return;
		}
		attach_node(std::unique_ptr<SceneNode>(static_cast<SceneNode*>(node.release())));
	}

	void SceneNodeManager::attach_node(std::unique_ptr<SceneNode> node)
	{
		if (!node)
		{
			return;
		}

		SceneNode* node_ptr = node.get();
		m_root_node->attach_child(std::move(node));

		if (node_ptr)
		{
			register_node_recursive(*node_ptr);
		}
	}

	void SceneNodeManager::add_object(int id, IGeometricObject* object)
	{
		SceneObjects::add_object(id, object);
		if (dynamic_cast<ILightObject*>(object))
		{
			const ILightObject* light_object = dynamic_cast<const ILightObject*>(object);
			add_light_object(id, light_object);
		}
	}

	void SceneNodeManager::remove_object(int id)
	{
		std::unordered_map<int, IGeometricObject*>::const_iterator it = m_objects.find(id);
		if (it != m_objects.end())
		{
			if (dynamic_cast<const ILightObject*>(it->second))
			{
				remove_light_object(id);
			}
		}
		SceneObjects::remove_object(id);
	}

	void SceneNodeManager::register_node(SceneNode& node)
	{
		node.for_each_component(
			[this, &node](ISceneComponent& component)
			{
				ObjectComponent* obj_component = dynamic_cast<ObjectComponent*>(&component);
				if (!obj_component)
				{
					LightComponent* light_component = dynamic_cast<LightComponent*>(&component);
					if (!light_component)
					{
						return;
					}

					const ILightObject* light_object = light_component->get_light_object();
					if (!light_object)
					{
						return;
					}

					add_light_object(light_component->get_id(), light_object);
					return;
				}

				IGeometricObject* object = obj_component->get_object();
				if (!object)
				{
					return;
				}

				add_object(obj_component->get_id(), object);
				set_object_transform(obj_component->get_id(), &node.get_transform());
			});
	}

	void SceneNodeManager::register_node_recursive(SceneNode& node)
	{
		register_node(node);

		node.for_each_child(
			[this](ISceneNode& child)
			{
				SceneNode* child_node = dynamic_cast<SceneNode*>(&child);
				if (child_node)
				{
					register_node_recursive(*child_node);
				}
			});
	}
}