#pragma once


#include "i_update_hooks.hpp"


namespace andromeda
{
    /// @brief Defines the interface for scene update hooks.
    ///
    /// Extends the generic update hook interface for scene-specific update
    /// notifications. Callback registration and management are inherited from
    /// `IUpdateHooks`.
    class ISceneUpdateHooks
        : public virtual IUpdateHooks
    {
    public:
        /// @brief Callback function type.
        using Callback = IUpdateHooks::Callback;

        /// @brief Callback registration handle type.
        using Handle = IUpdateHooks::Handle;

        /// @brief Virtual destructor.
        ~ISceneUpdateHooks() override = default;
    };
}
