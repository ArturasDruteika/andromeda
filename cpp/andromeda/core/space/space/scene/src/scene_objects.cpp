#include "../include/scene_objects.hpp"


namespace andromeda::space
{
	SceneObjects::SceneObjects()
		: m_objects{}
		, m_object_transforms{}
	{
	}

	SceneObjects::~SceneObjects()
	{
		m_objects.clear();
		m_object_transforms.clear();
	}

	const std::unordered_map<int, IGeometricObject*>& SceneObjects::get_objects() const
	{
		return m_objects;
	}

	const std::unordered_map<int, ITransformable*>& SceneObjects::get_object_transforms() const
	{
		return m_object_transforms;
	}

	void SceneObjects::add_object(int id, IGeometricObject* object)
	{
		m_objects[id] = object;
	}

	void SceneObjects::remove_object(int id)
	{
		std::unordered_map<int, IGeometricObject*>::iterator it = m_objects.find(id);
		if (it != m_objects.end())
		{
			m_objects.erase(it);
		}
		m_object_transforms.erase(id);
	}

	void SceneObjects::set_object_transform(int id, ITransformable* transform)
	{
		m_object_transforms[id] = transform;
	}
}