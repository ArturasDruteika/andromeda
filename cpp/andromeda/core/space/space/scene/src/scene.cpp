#include "../include/scene.hpp"


namespace andromeda::space
{
	Scene::Scene()
		: CameraHandler{}
		, SceneEnvironment{}
		, SceneState{}
		, m_scene_center{ math::Vec3{ 0.0f } }
	{
	}

	Scene::~Scene()
	{
		clear_scene();
	}

	const math::Vec3& Scene::get_scene_center() const
	{
		return m_scene_center;
	}

	void Scene::clear_scene()
	{
		m_objects.clear();
		m_object_transforms.clear();
		m_directional_lights.clear();
		m_point_lights.clear();
		m_light_objects.clear();
	}

	void Scene::reset_scene_state()
	{
	}

	void Scene::update(float delta_time)
	{
		run_update_callbacks(delta_time);
	}

}