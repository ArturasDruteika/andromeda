#pragma once


#include <cstdint>
#include <functional>


namespace andromeda
{
    /// @brief Defines the interface for update callback management.
    ///
    /// An update hook manager stores callbacks that are invoked during an
    /// update cycle. Each callback receives the elapsed time since the previous
    /// update.
    class IUpdateHooks
    {
    public:
        /// @brief Callback function type.
        ///
        /// The callback receives the elapsed time since the previous update,
        /// expressed in seconds.
        using Callback = std::function<void(float)>;

        /// @brief Identifies a registered callback.
        struct Handle
        {
            /// @brief Unique callback identifier.
            std::uint64_t id = 0;
        };

    public:
        /// @brief Virtual destructor.
        virtual ~IUpdateHooks() = default;

        /// @brief Registers an update callback.
        ///
        /// @param callback Callback to invoke during updates.
        /// @return Handle that can be used to remove the callback later.
        virtual Handle add(Callback callback) = 0;

        /// @brief Unregisters an update callback.
        ///
        /// @param handle Handle returned when the callback was registered.
        virtual void remove(Handle handle) = 0;

        /// @brief Removes all registered callbacks.
        virtual void clear() = 0;

        /// @brief Executes all registered callbacks.
        ///
        /// @param delta_time Elapsed time since the previous update, in seconds.
        virtual void run(float delta_time) = 0;
    };
}
