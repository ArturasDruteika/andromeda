#include "../include/EventDispatcher.hpp"


namespace andromeda::Window
{
	EventDispatcher::EventDispatcher(IEvent& event)
		: m_event{ event }
	{
	}

	EventDispatcher::~EventDispatcher() = default;
}
