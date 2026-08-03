#pragma once


#include "event_base.hpp"
#include "andromeda/window/events/event_type.hpp"
#include "andromeda/window/mouse_and_key_codes/mouse_codes.hpp"
#include "andromeda/window/events/i_mouse_events.hpp"
#include "pch.hpp"


namespace andromeda::window
{
    /// @brief Event emitted when the mouse cursor moves.
    ///
    /// Stores the current cursor position within the window.
    class MouseMovedEvent
        : public EventBase
        , public virtual IMouseMovedEvent
    {
    public:
        /// @brief Constructs a mouse movement event.
        ///
        /// @param x Mouse cursor X-coordinate.
        /// @param y Mouse cursor Y-coordinate.
        MouseMovedEvent(float x, float y);

        /// @brief Destroys the mouse movement event.
        ~MouseMovedEvent() override = default;

        /// @brief Retrieves the cursor X-coordinate.
        ///
        /// @return Cursor X-coordinate.
        float get_x() const override;

        /// @brief Retrieves the cursor Y-coordinate.
        ///
        /// @return Cursor Y-coordinate.
        float get_y() const override;

        /// @brief Checks whether the event belongs to a category.
        ///
        /// @param category Event category to test.
        /// @return `true` if the event belongs to the category; otherwise, `false`.
        bool is_in_category(EventCategory category) const override;

        /// @brief Retrieves the event category flags.
        ///
        /// @return Bitmask representing the event categories.
        int get_category_flags() const override;

        /// @brief Retrieves the event name.
        ///
        /// @return Event name.
        std::string get_name() const override;

        /// @brief Converts the event to a human-readable string.
        ///
        /// @return String representation of the event.
        std::string to_string() const override;

        /// @brief Retrieves the event type.
        ///
        /// @return Event type identifier.
        EventType get_event_type() const override;

    private:
        /// @brief Cursor X-coordinate.
        float m_x;

        /// @brief Cursor Y-coordinate.
        float m_y;
    };

    /// @brief Event emitted when the mouse wheel is scrolled.
    ///
    /// Stores horizontal and vertical scroll offsets.
    class MouseScrolledEvent
        : public EventBase
        , public virtual IMouseScrolledEvent
    {
    public:
        /// @brief Constructs a mouse scroll event.
        ///
        /// @param x_offset Horizontal scroll offset.
        /// @param y_offset Vertical scroll offset.
        MouseScrolledEvent(float x_offset, float y_offset);

        /// @brief Destroys the mouse scroll event.
        ~MouseScrolledEvent() override = default;

        /// @brief Retrieves the horizontal scroll offset.
        ///
        /// @return Horizontal scroll offset.
        float get_x_offset() const override;

        /// @brief Retrieves the vertical scroll offset.
        ///
        /// @return Vertical scroll offset.
        float get_y_offset() const override;

        /// @brief Checks whether the event belongs to a category.
        ///
        /// @param category Event category to test.
        /// @return `true` if the event belongs to the category; otherwise, `false`.
        bool is_in_category(EventCategory category) const override;

        /// @brief Retrieves the event category flags.
        ///
        /// @return Bitmask representing the event categories.
        int get_category_flags() const override;

        /// @brief Retrieves the event name.
        ///
        /// @return Event name.
        std::string get_name() const override;

        /// @brief Converts the event to a human-readable string.
        ///
        /// @return String representation of the event.
        std::string to_string() const override;

        /// @brief Retrieves the event type.
        ///
        /// @return Event type identifier.
        EventType get_event_type() const override;

    private:
        /// @brief Horizontal scroll offset.
        float m_x_offset;

        /// @brief Vertical scroll offset.
        float m_y_offset;
    };

    /// @brief Base class for mouse button events.
    ///
    /// Stores the mouse button associated with the event and provides common
    /// mouse button event category information.
    class MouseButtonEvent
        : public EventBase
        , public virtual IMouseButtonEvent
    {
    public:
        /// @brief Constructs a mouse button event.
        ///
        /// @param button Mouse button associated with the event.
        explicit MouseButtonEvent(MouseCode button);

        /// @brief Destroys the mouse button event.
        ~MouseButtonEvent() override = default;

        /// @brief Retrieves the mouse button.
        ///
        /// @return Mouse button code.
        MouseCode get_mouse_button() const override;

        /// @brief Checks whether the event belongs to a category.
        ///
        /// @param category Event category to test.
        /// @return `true` if the event belongs to the category; otherwise, `false`.
        bool is_in_category(EventCategory category) const override;

        /// @brief Retrieves the event category flags.
        ///
        /// @return Bitmask representing the event categories.
        int get_category_flags() const override;

    protected:
        /// @brief Mouse button associated with the event.
        MouseCode m_button;
    };

    /// @brief Event emitted when a mouse button is pressed.
    class MouseButtonPressedEvent
        : public MouseButtonEvent
        , public virtual IMouseButtonPressedEvent
    {
    public:
        /// @brief Constructs a mouse button press event.
        ///
        /// @param button Mouse button that was pressed.
        explicit MouseButtonPressedEvent(MouseCode button);

        /// @brief Destroys the mouse button press event.
        ~MouseButtonPressedEvent() override = default;

        /// @brief Retrieves the event name.
        ///
        /// @return Event name.
        std::string get_name() const override;

        /// @brief Converts the event to a human-readable string.
        ///
        /// @return String representation of the event.
        std::string to_string() const override;

        /// @brief Retrieves the event type.
        ///
        /// @return Event type identifier.
        EventType get_event_type() const override;
    };

    /// @brief Event emitted when a mouse button is released.
    class MouseButtonReleasedEvent
        : public MouseButtonEvent
        , public virtual IMouseButtonReleasedEvent
    {
    public:
        /// @brief Constructs a mouse button release event.
        ///
        /// @param button Mouse button that was released.
        explicit MouseButtonReleasedEvent(MouseCode button);

        /// @brief Destroys the mouse button release event.
        ~MouseButtonReleasedEvent() override = default;

        /// @brief Retrieves the event name.
        ///
        /// @return Event name.
        std::string get_name() const override;

        /// @brief Converts the event to a human-readable string.
        ///
        /// @return String representation of the event.
        std::string to_string() const override;

        /// @brief Retrieves the event type.
        ///
        /// @return Event type identifier.
        EventType get_event_type() const override;
    };
}
