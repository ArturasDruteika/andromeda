#pragma once


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/scene/i_scene_update_hooks.hpp"
#include "pch.hpp"


namespace andromeda::space
{
    /// @brief Manages a collection of scene update callbacks.
    ///
    /// Allows callbacks to be registered, removed, cleared, and executed during
    /// scene updates.
    class SPACE_API UpdateHooks
        : public virtual ISceneUpdateHooks
    {
    public:
        /// @brief Constructs an update hook manager.
        UpdateHooks();

        /// @brief Destroys the update hook manager.
        ~UpdateHooks() override;

        /// @brief Registers an update callback.
        ///
        /// @param callback Callback function to register.
        /// @return Handle that uniquely identifies the registered callback.
        ISceneUpdateHooks::Handle add(ISceneUpdateHooks::Callback callback) override;

        /// @brief Removes a previously registered callback.
        ///
        /// @param handle Handle identifying the callback to remove.
        void remove(ISceneUpdateHooks::Handle handle) override;

        /// @brief Removes all registered callbacks.
        void clear() override;

        /// @brief Executes all registered callbacks.
        ///
        /// @param delta_time Time elapsed since the previous update, in seconds.
        void run(float delta_time) override;

    private:
        /// @brief Represents a registered update callback.
        struct Entry
        {
            /// @brief Unique identifier of the callback.
            std::uint64_t id = 0;

            /// @brief Callback function.
            ISceneUpdateHooks::Callback fn;
        };

    private:
        /// @brief Identifier assigned to the next registered callback.
        std::uint64_t m_next_id;

        /// @brief Collection of registered update callbacks.
        std::vector<Entry> m_entries;
    };
}
