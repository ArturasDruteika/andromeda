#ifndef WINDOW__KEY_EVENTS__HPP
#define WINDOW__KEY_EVENTS__HPP


#include "event_base.hpp"
#include "andromeda/window/events/event_type.hpp"
#include "andromeda/window/mouse_and_key_codes/key_codes.hpp"
#include "andromeda/window/events/i_key_events.hpp"
#include "pch.hpp"


namespace andromeda::window
{
    class KeyEvent
        : public EventBase
        , public virtual IKeyEvent
    {
    public:
        explicit KeyEvent(KeyCode keycode);
        ~KeyEvent() override;

        bool is_in_category(EventCategory category) const override;
        int get_category_flags() const override;

        KeyCode get_key_code() const override;

    protected:
        KeyCode m_key_code;
    };

    class KeyPressedEvent
        : public KeyEvent
        , public virtual IKeyPressedEvent
    {
    public:
        KeyPressedEvent(KeyCode keycode, bool is_repeat);
        ~KeyPressedEvent() override;

        bool is_repeat() const override;

        EventType get_event_type() const override;
        std::string get_name() const override;
        std::string to_string() const override;

    private:
        bool m_is_repeat;
    };

    class KeyReleasedEvent
        : public KeyEvent
        , public virtual IKeyReleasedEvent
    {
    public:
        explicit KeyReleasedEvent(KeyCode keycode);
        ~KeyReleasedEvent() override;

        EventType get_event_type() const override;
        std::string get_name() const override;
        std::string to_string() const override;
    };

    class KeyTypedEvent
        : public KeyEvent
        , public virtual IKeyTypedEvent
    {
    public:
        explicit KeyTypedEvent(KeyCode keycode);
        ~KeyTypedEvent() override;

        EventType get_event_type() const override;
        std::string get_name() const override;
        std::string to_string() const override;
    };
}


#endif // WINDOW__KEY_EVENTS__HPP