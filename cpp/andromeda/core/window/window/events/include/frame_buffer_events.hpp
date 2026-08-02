#ifndef WINDOW__FRAMEBUFFER_EVENTS__HPP
#define WINDOW__FRAMEBUFFER_EVENTS__HPP


#include "event_base.hpp"
#include "andromeda/window/events/event_type.hpp"
#include "andromeda/window/events/i_frame_buffer_events.hpp"

#include <string>


namespace andromeda::window
{
    /// @brief Event emitted when the window size changes.
    ///
    /// Stores the updated window dimensions after a resize operation.
    class WindowResizeEvent
        : public EventBase
        , public virtual IWindowResizeEvent
    {
    public:
        /// @brief Constructs a window resize event.
        ///
        /// @param width New window width in pixels.
        /// @param height New window height in pixels.
        WindowResizeEvent(int width, int height);

        /// @brief Destroys the window resize event.
        ~WindowResizeEvent() override;

        /// @brief Retrieves the window width.
        ///
        /// @return Window width in pixels.
        int get_width() const override;

        /// @brief Retrieves the window height.
        ///
        /// @return Window height in pixels.
        int get_height() const override;

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
        /// @brief Updated window width.
        int m_width;

        /// @brief Updated window height.
        int m_height;
    };

    /// @brief Event emitted when the window is requested to close.
    class WindowCloseEvent
        : public EventBase
        , public virtual IWindowCloseEvent
    {
    public:
        /// @brief Constructs a window close event.
        WindowCloseEvent();

        /// @brief Destroys the window close event.
        ~WindowCloseEvent() override;

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
    };

    /// @brief Event emitted when the framebuffer size changes.
    ///
    /// Stores the updated framebuffer dimensions, which may differ from the
    /// window size on high-DPI displays.
    class FramebufferResizeEvent
        : public EventBase
        , public virtual IFramebufferResizeEvent
    {
    public:
        /// @brief Constructs a framebuffer resize event.
        ///
        /// @param width New framebuffer width in pixels.
        /// @param height New framebuffer height in pixels.
        FramebufferResizeEvent(int width, int height);

        /// @brief Destroys the framebuffer resize event.
        ~FramebufferResizeEvent() override;

        /// @brief Retrieves the framebuffer width.
        ///
        /// @return Framebuffer width in pixels.
        int get_width() const override;

        /// @brief Retrieves the framebuffer height.
        ///
        /// @return Framebuffer height in pixels.
        int get_height() const override;

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
        /// @brief Updated framebuffer width.
        int m_width;

        /// @brief Updated framebuffer height.
        int m_height;
    };
}


#endif // WINDOW__FRAMEBUFFER_EVENTS__HPP