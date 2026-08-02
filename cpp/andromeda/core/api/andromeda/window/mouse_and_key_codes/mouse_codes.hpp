#ifndef API__WINDOW__EVENTS__MOUSE_CODES__HPP
#define API__WINDOW__EVENTS__MOUSE_CODES__HPP


#include "pch.hpp"


namespace andromeda
{
    /// @brief Type used to represent mouse button codes.
    ///
    /// Mouse button codes correspond to the values defined by GLFW and
    /// identify mouse buttons reported by the windowing system.
    using MouseCode = uint16_t;

    /// @brief Mouse button codes.
    ///
    /// The values match the GLFW mouse button definitions from `glfw3.h` to
    /// allow direct interoperability with GLFW input events.
    enum : MouseCode
    {
        // From glfw3.h
        Button0 = 0,
        Button1 = 1,
        Button2 = 2,
        Button3 = 3,
        Button4 = 4,
        Button5 = 5,
        Button6 = 6,
        Button7 = 7,

        ButtonLast = Button7,
        ButtonLeft = Button0,
        ButtonRight = Button1,
        ButtonMiddle = Button2
    };
}


#endif // API__WINDOW__EVENTS__MOUSE_CODES__HPP