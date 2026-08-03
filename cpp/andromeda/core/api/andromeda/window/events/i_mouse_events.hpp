#pragma once


#include "i_event.hpp"
#include "../mouse_and_key_codes/mouse_codes.hpp"


namespace andromeda
{
    /// @brief Defines the interface for a mouse movement event.
    ///
    /// Generated when the mouse cursor moves within the application window.
    class IMouseMovedEvent
        : public virtual IEvent
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IMouseMovedEvent() = default;

        /// @brief Retrieves the mouse X position.
        ///
        /// @return Cursor X coordinate.
        virtual float get_x() const = 0;

        /// @brief Retrieves the mouse Y position.
        ///
        /// @return Cursor Y coordinate.
        virtual float get_y() const = 0;
    };

    /// @brief Defines the interface for a mouse scroll event.
    ///
    /// Generated when the mouse wheel or scroll device is used.
    class IMouseScrolledEvent
        : public virtual IEvent
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IMouseScrolledEvent() = default;

        /// @brief Retrieves the vertical scroll offset.
        ///
        /// @return Vertical scroll offset.
        virtual float get_y_offset() const = 0;

        /// @brief Retrieves the horizontal scroll offset.
        ///
        /// @return Horizontal scroll offset.
        virtual float get_x_offset() const = 0;
    };

    /// @brief Defines the base interface for mouse button events.
    ///
    /// Provides access to the mouse button associated with the event.
    class IMouseButtonEvent
        : public virtual IEvent
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IMouseButtonEvent() = default;

        /// @brief Retrieves the mouse button associated with the event.
        ///
        /// @return Mouse button code.
        virtual MouseCode get_mouse_button() const = 0;
    };

    /// @brief Defines the interface for a mouse button pressed event.
    ///
    /// Generated when a mouse button is pressed.
    class IMouseButtonPressedEvent
        : public virtual IMouseButtonEvent
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IMouseButtonPressedEvent() = default;
    };

    /// @brief Defines the interface for a mouse button released event.
    ///
    /// Generated when a mouse button is released.
    class IMouseButtonReleasedEvent
        : public virtual IMouseButtonEvent
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IMouseButtonReleasedEvent() = default;
    };
}
