#include "../include/scene_lighting.hpp"


namespace andromeda::space
{
	SceneLighting::SceneLighting()
		: m_directional_lights{}
		, m_point_lights{}
		, m_light_objects{}
	{
	}

	SceneLighting::~SceneLighting()
	{
		m_directional_lights.clear();
		m_point_lights.clear();
		m_light_objects.clear();
	}

	const std::unordered_map<int, const IDirectionalLight*>& SceneLighting::get_directional_lights() const
	{
		return m_directional_lights;
	}

	const std::unordered_map<int, const IPointLight*>& SceneLighting::get_point_lights() const
	{
		return m_point_lights;
	}

	const std::unordered_map<int, const ILightObject*>& SceneLighting::get_light_objects() const
	{
		return m_light_objects;
	}

	void SceneLighting::add_light_object(int id, const ILightObject* p_light_object)
	{
		m_light_objects[id] = p_light_object;
		if (p_light_object->get_light_type() == LightType::Directional)
		{
			const IDirectionalLight* directional_light = dynamic_cast<const IDirectionalLight*>(p_light_object);
			if (directional_light)
			{
				m_directional_lights[id] = directional_light;
			}
		}
		else if (p_light_object->get_light_type() == LightType::Point)
		{
			const IPointLight* point_light = dynamic_cast<const IPointLight*>(p_light_object);
			if (point_light)
			{
				m_point_lights[id] = point_light;
			}
		}
	}

	void SceneLighting::remove_light_object(int id)
	{
		std::unordered_map<int, const ILightObject*>::iterator light_object_it = m_light_objects.find(id);
		if (light_object_it != m_light_objects.end())
		{
			const ILightObject* light_object = light_object_it->second;
			if (light_object->get_light_type() == LightType::Directional)
			{
				std::unordered_map<int, const IDirectionalLight*>::iterator directional_light_it =
					m_directional_lights.find(id);
				if (directional_light_it != m_directional_lights.end())
				{
					m_directional_lights.erase(directional_light_it);
				}
			}
			else if (light_object->get_light_type() == LightType::Point)
			{
				std::unordered_map<int, const IPointLight*>::iterator point_light_it =
					m_point_lights.find(id);
				if (point_light_it != m_point_lights.end())
				{
					m_point_lights.erase(point_light_it);
				}
			}
			m_light_objects.erase(light_object_it);
		}
	}
}