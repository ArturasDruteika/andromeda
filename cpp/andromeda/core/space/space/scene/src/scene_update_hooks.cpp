#include "../include/scene_update_hooks.hpp"


namespace andromeda::space
{
	SceneUpdateHooksManager::SceneUpdateHooksManager() = default;

	SceneUpdateHooksManager::~SceneUpdateHooksManager() = default;

	SceneUpdateHooksManager::Handle SceneUpdateHooksManager::add_update_callback(Callback callback)
	{
		return m_update_hooks.add(std::move(callback));
	}

	void SceneUpdateHooksManager::remove_update_callback(Handle handle)
	{
		m_update_hooks.remove(handle);
	}

	void SceneUpdateHooksManager::clear_update_callbacks()
	{
		m_update_hooks.clear();
	}

	void SceneUpdateHooksManager::run_update_callbacks(float delta_time)
	{
		m_update_hooks.run(delta_time);
	}
}