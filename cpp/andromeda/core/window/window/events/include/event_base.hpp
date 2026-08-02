#ifndef WINDOW__EVENT_BASE__HPP
#define WINDOW__EVENT_BASE__HPP


#include "andromeda/window/events/i_event.hpp"


namespace andromeda::window
{
    /// @brief Base implementation of an event.
    ///
    /// Provides common functionality for tracking whether an event has been
    /// handled by the event processing system.
    class EventBase
        : public virtual IEvent
    {
    public:
        /// @brief Constructs an event.
        EventBase();

        /// @brief Destroys the event.
        ~EventBase() override;

        /// @brief Checks whether the event has been handled.
        ///
        /// @return `true` if the event has been handled; otherwise, `false`.
        bool is_handled() const override;

        /// @brief Marks the event as handled or unhandled.
        ///
        /// @param handled `true` if the event has been handled; otherwise, `false`.
        void set_handled(bool handled) override;

    private:
        /// @brief Indicates whether the event has been handled.
        bool m_handled;
    };
}

#endif // WINDOW__EVENT_BASE__HPP