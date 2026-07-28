#include "../include/event_dispatcher.hpp"


namespace andromeda::window
{
	EventDispatcher::EventDispatcher(IEvent& event)
		: m_event{ event }
	{
	}

	EventDispatcher::~EventDispatcher() = default;
}