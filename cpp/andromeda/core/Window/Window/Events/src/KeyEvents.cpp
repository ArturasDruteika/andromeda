#include "../include/KeyEvents.hpp"
#include <sstream>


namespace andromeda::Window
{
    // KeyEvent

    KeyEvent::~KeyEvent() = default;

    KeyEvent::KeyEvent(andromeda::KeyCode keycode)
        : m_keyCode{ keycode }
    {
    }

    andromeda::KeyCode KeyEvent::GetKeyCode() const
    {
        return m_keyCode;
    }

    bool KeyEvent::IsInCategory(andromeda::EventCategory category)
    {
        return (GetCategoryFlags() & category) != 0;
    }

    int KeyEvent::GetCategoryFlags() const
    {
        return andromeda::EventCategoryKeyboard |
            andromeda::EventCategoryInput;
    }

    // KeyPressedEvent

    KeyPressedEvent::KeyPressedEvent(andromeda::KeyCode keycode, bool isRepeat)
        : KeyEvent{ keycode }
        , m_isRepeat{ isRepeat }
    {
    }

    KeyPressedEvent::~KeyPressedEvent() = default;

    bool KeyPressedEvent::IsRepeat() const
    {
        return m_isRepeat;
    }

    andromeda::EventType KeyPressedEvent::GetEventType() const
    {
        return andromeda::EventType::KeyPressed;
    }

    std::string KeyPressedEvent::GetName() const
    {
        return "KeyPressed";
    }

    std::string KeyPressedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << static_cast<int>(m_keyCode)
            << " repeat=" << (m_isRepeat ? "true" : "false");
        return ss.str();
    }

    // KeyReleasedEvent

    KeyReleasedEvent::KeyReleasedEvent(andromeda::KeyCode keycode)
        : KeyEvent{ keycode }
    {
    }

    KeyReleasedEvent::~KeyReleasedEvent() = default;

    andromeda::EventType KeyReleasedEvent::GetEventType() const
    {
        return andromeda::EventType::KeyReleased;
    }

    std::string KeyReleasedEvent::GetName() const
    {
        return "KeyReleased";
    }

    std::string KeyReleasedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << static_cast<int>(m_keyCode);
        return ss.str();
    }

    // KeyTypedEvent

    KeyTypedEvent::KeyTypedEvent(andromeda::KeyCode keycode)
        : KeyEvent{ keycode }
    {
    }

    KeyTypedEvent::~KeyTypedEvent() = default;

    andromeda::EventType KeyTypedEvent::GetEventType() const
    {
        return andromeda::EventType::KeyTyped;
    }

    std::string KeyTypedEvent::GetName() const
    {
        return "KeyTyped";
    }

    std::string KeyTypedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << static_cast<int>(m_keyCode);
        return ss.str();
    }
}
