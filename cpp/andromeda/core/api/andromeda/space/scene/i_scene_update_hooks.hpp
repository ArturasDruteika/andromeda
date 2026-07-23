#ifndef API__SCENE__I_SCENE_UPDATE_HOOKS__HPP
#define API__SCENE__I_SCENE_UPDATE_HOOKS__HPP


#include "i_update_hooks.hpp"


namespace andromeda
{
	class ISceneUpdateHooks
		: public virtual IUpdateHooks
	{
	public:
		using Callback = IUpdateHooks::Callback;
		using Handle = IUpdateHooks::Handle;

		~ISceneUpdateHooks() override = default;
	};
}


#endif // API__SCENE__I_SCENE_UPDATE_HOOKS__HPP