#include "andromeda/space/scene/scene_node_manager.hpp"
#include "andromeda/space/transformations/transformable.hpp"
#include "andromeda/space/scene_graph/object_component.hpp"
#include "andromeda/space/scene_graph/light_component.hpp"

#include <memory>
#include <utility>
#include <unordered_map>


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

	void SceneNodeManager::sync_light_transforms()
	{
		for (const auto& [id, binding] : m_point_light_transforms)
		{
			// Skip lights that were removed from the scene since registration
			if (m_point_lights.find(id) == m_point_lights.end())
			{
				continue;
			}

			IPointLight* point_light = binding.first;
			const ITransformable* transform = binding.second;
			if (!point_light || !transform)
			{
				continue;
			}

			point_light->set_position(transform->get_position());
		}
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

					ILightObject* light_object = light_component->get_light_object();
					if (!light_object)
					{
						return;
					}

					add_light_object(light_component->get_id(), light_object);

					IPointLight* point_light = dynamic_cast<IPointLight*>(light_object);
					if (point_light)
					{
						m_point_light_transforms[light_component->get_id()] =
							std::make_pair(point_light, &node.get_transform());
						point_light->set_position(node.get_transform().get_position());
					}
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