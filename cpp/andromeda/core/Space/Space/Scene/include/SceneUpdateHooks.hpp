#pragma once


#include "../../MacroExports/include/MacroExports.hpp"
#include "../../UpdateHooks/include/UpdateHooks.hpp"
#include "andromeda/space/scene/i_scene_update_hooks.hpp"
#include "pch.hpp"


namespace andromeda::Space
{
	class SPACE_API SceneUpdateHooksManager
	{
	public:
		using Callback = ISceneUpdateHooks::Callback;
		using Handle = ISceneUpdateHooks::Handle;

		SceneUpdateHooksManager();
		virtual ~SceneUpdateHooksManager();

		Handle AddUpdateCallback(Callback callback);
		void RemoveUpdateCallback(Handle handle);
		void ClearUpdateCallbacks();

	protected:
		void RunUpdateCallbacks(float deltaTime);

	private:
		UpdateHooks m_updateHooks;
	};
}
