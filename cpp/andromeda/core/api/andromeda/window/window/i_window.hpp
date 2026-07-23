#ifndef API__WINDOW__I_WINDOW__HPP
#define API__WINDOW__I_WINDOW__HPP


#include "../events/i_event.hpp"
#include <functional>
#include <string>


namespace Andromeda
{
    class IWindow
    {
    public:
        using EventCallbackFn = std::function<void(IEvent&)>;

        virtual ~IWindow() = default;

		virtual bool is_initialized() const = 0;
        virtual unsigned int get_width() const = 0;
        virtual unsigned int get_height() const = 0;
		virtual std::string get_title() const = 0;
        virtual void set_title(const std::string& title) = 0;
        virtual void poll_events() = 0;
        virtual bool should_close() const = 0;
        virtual void* get_native_handle() const = 0;  // For GL, Vulkan, DirectX
        virtual void set_event_callback(const EventCallbackFn& callback) = 0;
    };
}


#endif // API_WINDOW__I_WINDOW__HPP