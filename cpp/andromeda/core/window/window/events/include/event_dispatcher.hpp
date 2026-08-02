#ifndef WINDOW__EVENT_DISPATCHER__HPP
#define WINDOW__EVENT_DISPATCHER__HPP


#include "andromeda/window/events/i_event.hpp"


namespace andromeda::window
{
	/// @brief Dispatches events to type-specific handlers.
	///
	/// Performs runtime type checking and invokes the provided callback when the
	/// stored event matches the requested event type.
	class EventDispatcher
	{
	public:
		/// @brief Constructs an event dispatcher.
		///
		/// @param event Event to dispatch.
		EventDispatcher(IEvent& event);

		/// @brief Destroys the event dispatcher.
		~EventDispatcher();

        /// @brief Dispatches the stored event to a matching handler.
        ///
        /// If the stored event is of type `T`, the callback is invoked. If the
        /// callback returns `true`, the event is marked as handled.
        ///
        /// @tparam T Event type expected by the callback.
        /// @tparam F Callable object accepting `T&` and returning `bool`.
        /// @param func Event handler to invoke.
        /// @return `true` if the event was dispatched and handled; otherwise,
        /// `false`.
        template<typename T, typename F>
        bool dispatch(const F& func)
        {
            // Prefer dynamic_cast so we don't need GetStaticType / macros
            if (auto* e = dynamic_cast<T*>(&m_event))
            {
                bool handled = func(*e);
                if (handled)
                {
                    m_event.set_handled(true);
                }
                return handled;
            }
            return false;
        }

	private:
		/// @brief Reference to the event being dispatched.
		IEvent& m_event;
	};
}


#endif // WINDOW__EVENT_DISPATCHER__HPP