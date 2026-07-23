#ifndef API__WINDOW__EVENTS__I_EVENT_HPP
#define API__WINDOW__EVENTS__I_EVENT_HPP


#include "event_type.hpp"
#include <string>


namespace Andromeda
{
	class IEvent
	{
	public:
		virtual ~IEvent() = default;

		virtual bool is_handled() const = 0;
		virtual void set_handled(bool handled) = 0;
		virtual bool is_in_category(EventCategory category) = 0;
		virtual int get_category_flags() const = 0;
		virtual std::string get_name() const = 0;
		virtual std::string to_string() const = 0;
		virtual EventType get_event_type() const = 0;
	};
}


#endif // API__WINDOW__EVENTS__I_EVENT_HPP