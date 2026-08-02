#ifndef API__WINDOW__EVENTS__EVENTS_TYPE__HPP
#define API__WINDOW__EVENTS__EVENTS_TYPE__HPP


namespace andromeda
{
	constexpr int bit(int x) noexcept
	{
		return 1 << x;
	}

    /// @brief Enumerates the supported event types.
    enum class EventType
    {
        /// @brief No event.
        None = 0,

        /// @brief Window close event.
        WindowClose,

        /// @brief Window resize event.
        WindowResize,

        /// @brief Window focus gained event.
        WindowFocus,

        /// @brief Window focus lost event.
        WindowLostFocus,

        /// @brief Window moved event.
        WindowMoved,

        /// @brief Application tick event.
        AppTick,

        /// @brief Application update event.
        AppUpdate,

        /// @brief Application render event.
        AppRender,

        /// @brief Keyboard key pressed event.
        KeyPressed,

        /// @brief Keyboard key released event.
        KeyReleased,

        /// @brief Character input event.
        KeyTyped,

        /// @brief Mouse button pressed event.
        MouseButtonPressed,

        /// @brief Mouse button released event.
        MouseButtonReleased,

        /// @brief Mouse moved event.
        MouseMoved,

        /// @brief Mouse wheel scrolled event.
        MouseScrolled
    };

    /// @brief Bitmask describing event categories.
    ///
    /// Event categories allow events to be grouped by functionality and tested
    /// using bitwise operations.
    enum EventCategory
    {
        /// @brief No category.
        None = 0,

        /// @brief Application-related events.
        EventCategoryApplication = bit(0),

        /// @brief Input-related events.
        EventCategoryInput = bit(1),

        /// @brief Keyboard events.
        EventCategoryKeyboard = bit(2),

        /// @brief Mouse events.
        EventCategoryMouse = bit(3),

        /// @brief Mouse button events.
        EventCategoryMouseButton = bit(4)
    };
}


#endif // API__WINDOW__EVENTS__EVENTS_TYPE__HPP