#pragma once


#include "../../macro_exports/include/macro_exports.hpp"
#include "../../update_hooks/include/update_hooks.hpp"
#include "andromeda/space/scene/i_scene_update_hooks.hpp"
#include "pch.hpp"


namespace andromeda::space
{
	class SPACE_API SceneUpdateHooksManager
	{
	public:
		using Callback = ISceneUpdateHooks::Callback;
		using Handle = ISceneUpdateHooks::Handle;

		SceneUpdateHooksManager();
		virtual ~SceneUpdateHooksManager();

		Handle add_update_callback(Callback callback);
		void remove_update_callback(Handle handle);
		void clear_update_callbacks();

	protected:
		void run_update_callbacks(float delta_time);

	private:
		UpdateHooks m_update_hooks;
	};
}