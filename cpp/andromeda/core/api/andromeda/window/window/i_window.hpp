#ifndef API__WINDOW__I_WINDOW__HPP
#define API__WINDOW__I_WINDOW__HPP


#include "../events/i_event.hpp"
#include <functional>
#include <string>


namespace andromeda
{
    /// @brief Defines the interface for an application window.
    ///
    /// A window provides access to platform-specific window functionality,
    /// including event polling, window properties, and the native window
    /// handle required by graphics APIs.
    class IWindow
    {
    public:
        /// @brief Event callback function type.
        ///
        /// The callback is invoked whenever a window or input event is
        /// generated.
        using EventCallbackFn = std::function<void(IEvent&)>;

        /// @brief Virtual destructor.
        virtual ~IWindow() = default;

        // Getters

        /// @brief Checks whether the window has been initialized.
        ///
        /// @return `true` if the window is initialized; otherwise, `false`.
        virtual bool is_initialized() const = 0;

        /// @brief Retrieves the window width.
        ///
        /// @return Width of the window in pixels.
        virtual unsigned int get_width() const = 0;

        /// @brief Retrieves the window height.
        ///
        /// @return Height of the window in pixels.
        virtual unsigned int get_height() const = 0;

        /// @brief Retrieves the window title.
        ///
        /// @return Window title.
        virtual std::string get_title() const = 0;

        /// @brief Sets the window title.
        ///
        /// @param title New window title.
        virtual void set_title(const std::string& title) = 0;

        /// @brief Processes pending window and input events.
        virtual void poll_events() = 0;

        /// @brief Checks whether the window should close.
        ///
        /// @return `true` if the window has received a close request;
        /// otherwise, `false`.
        virtual bool should_close() const = 0;

        /// @brief Retrieves the native window handle.
        ///
        /// The returned handle is platform-specific and can be used with
        /// graphics APIs such as OpenGL or Vulkan.
        ///
        /// @return Pointer to the native window handle.
        virtual void* get_native_handle() const = 0;

        /// @brief Sets the event callback.
        ///
        /// The callback is invoked for all window and input events generated
        /// by the window.
        ///
        /// @param callback Event callback function.
        virtual void set_event_callback(const EventCallbackFn& callback) = 0;
    };
}


#endif // API__WINDOW__I_WINDOW__HPP