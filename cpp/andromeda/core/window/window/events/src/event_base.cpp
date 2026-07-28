#include "../include/event_base.hpp"


namespace andromeda::window
{
	EventBase::EventBase()
		: m_handled{ false }
	{
	}

	EventBase::~EventBase() = default;

	bool EventBase::is_handled() const
	{
		return m_handled;
	}

	void EventBase::set_handled(bool handled)
	{
		m_handled = handled;
	}
}