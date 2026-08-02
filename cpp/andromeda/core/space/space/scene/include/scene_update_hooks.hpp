#pragma once


#include "../../macro_exports/include/macro_exports.hpp"
#include "../../update_hooks/include/update_hooks.hpp"
#include "andromeda/space/scene/i_scene_update_hooks.hpp"
#include "pch.hpp"


namespace andromeda::space
{
	/// @brief Manages scene update callback functions.
	///
	/// Provides registration, removal, and execution of callbacks that are
	/// invoked during scene updates.
	class SPACE_API SceneUpdateHooksManager
	{
	public:
		/// @brief Callback function type invoked during scene updates.
		using Callback = ISceneUpdateHooks::Callback;

		/// @brief Handle used to identify a registered callback.
		using Handle = ISceneUpdateHooks::Handle;

		/// @brief Constructs a scene update hook manager.
		SceneUpdateHooksManager();

		/// @brief Destroys the scene update hook manager.
		virtual ~SceneUpdateHooksManager();

		/// @brief Registers a scene update callback.
		///
		/// @param callback Callback function to register.
		/// @return Handle that can be used to remove the callback.
		Handle add_update_callback(Callback callback);

		/// @brief Removes a previously registered callback.
		///
		/// @param handle Handle identifying the callback.
		void remove_update_callback(Handle handle);

		/// @brief Removes all registered callbacks.
		void clear_update_callbacks();

	protected:
		/// @brief Executes all registered update callbacks.
		///
		/// @param delta_time Time elapsed since the previous update, in seconds.
		void run_update_callbacks(float delta_time);

	private:
		/// @brief Container storing registered update callbacks.
		UpdateHooks m_update_hooks;
	};
}