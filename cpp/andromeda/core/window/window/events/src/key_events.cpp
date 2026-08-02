#include "../include/key_events.hpp"
#include <sstream>


namespace andromeda::window
{
    // KeyEvent

    KeyEvent::~KeyEvent() = default;

    KeyEvent::KeyEvent(KeyCode keycode)
        : m_key_code{ keycode }
    {
    }

    KeyCode KeyEvent::get_key_code() const
    {
        return m_key_code;
    }

    bool KeyEvent::is_in_category(EventCategory category) const
    {
        return (get_category_flags() & category) != 0;
    }

    int KeyEvent::get_category_flags() const
    {
        return EventCategoryKeyboard |
            EventCategoryInput;
    }

    // KeyPressedEvent

    KeyPressedEvent::KeyPressedEvent(KeyCode keycode, bool is_repeat)
        : KeyEvent{ keycode }
        , m_is_repeat{ is_repeat }
    {
    }

    KeyPressedEvent::~KeyPressedEvent() = default;

    bool KeyPressedEvent::is_repeat() const
    {
        return m_is_repeat;
    }

    EventType KeyPressedEvent::get_event_type() const
    {
        return EventType::KeyPressed;
    }

    std::string KeyPressedEvent::get_name() const
    {
        return "KeyPressed";
    }

    std::string KeyPressedEvent::to_string() const
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << static_cast<int>(m_key_code)
            << " repeat=" << (m_is_repeat ? "true" : "false");
        return ss.str();
    }

    // KeyReleasedEvent

    KeyReleasedEvent::KeyReleasedEvent(KeyCode keycode)
        : KeyEvent{ keycode }
    {
    }

    KeyReleasedEvent::~KeyReleasedEvent() = default;

    EventType KeyReleasedEvent::get_event_type() const
    {
        return EventType::KeyReleased;
    }

    std::string KeyReleasedEvent::get_name() const
    {
        return "KeyReleased";
    }

    std::string KeyReleasedEvent::to_string() const
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << static_cast<int>(m_key_code);
        return ss.str();
    }

    // KeyTypedEvent

    KeyTypedEvent::KeyTypedEvent(KeyCode keycode)
        : KeyEvent{ keycode }
    {
    }

    KeyTypedEvent::~KeyTypedEvent() = default;

    EventType KeyTypedEvent::get_event_type() const
    {
        return EventType::KeyTyped;
    }

    std::string KeyTypedEvent::get_name() const
    {
        return "KeyTyped";
    }

    std::string KeyTypedEvent::to_string() const
    {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << static_cast<int>(m_key_code);
        return ss.str();
    }
}