#pragma once


#include "i_event.hpp"


namespace andromeda
{
    /// @brief Defines the interface for a window resize event.
    ///
    /// Generated when the dimensions of the application window change.
    class IWindowResizeEvent
        : public virtual IEvent
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IWindowResizeEvent() = default;

        /// @brief Retrieves the new window width.
        ///
        /// @return Window width in pixels.
        virtual int get_width() const = 0;

        /// @brief Retrieves the new window height.
        ///
        /// @return Window height in pixels.
        virtual int get_height() const = 0;
    };

    /// @brief Defines the interface for a window close event.
    ///
    /// Generated when the application window is requested to close.
    class IWindowCloseEvent
        : public virtual IEvent
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IWindowCloseEvent() = default;
    };

    /// @brief Defines the interface for a framebuffer resize event.
    ///
    /// Generated when the framebuffer dimensions change. The framebuffer size
    /// may differ from the window size on high-DPI displays.
    class IFramebufferResizeEvent
        : public virtual IEvent
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IFramebufferResizeEvent() = default;

        /// @brief Retrieves the new framebuffer width.
        ///
        /// @return Framebuffer width in pixels.
        virtual int get_width() const = 0;

        /// @brief Retrieves the new framebuffer height.
        ///
        /// @return Framebuffer height in pixels.
        virtual int get_height() const = 0;
    };
}
