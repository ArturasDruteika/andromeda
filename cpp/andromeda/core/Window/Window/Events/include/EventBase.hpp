#ifndef WINDOW__EVENT_BASE__HPP
#define WINDOW__EVENT_BASE__HPP


#include "Andromeda/window/events/i_event.hpp"


namespace Andromeda::Window
{
    class EventBase
        : public virtual IEvent
    {
    public:
        EventBase();
        ~EventBase() override;

        bool IsHandled() const override;
        void SetHandled(bool handled) override;

    private:
        bool m_handled;
    };
}


#endif // WINDOW__EVENT_BASE__HPP