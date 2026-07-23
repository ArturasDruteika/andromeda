#ifndef API__GRAPHICS_CONTEXT__I_GRAPHICS_CONTEXT__HPP
#define API__GRAPHICS_CONTEXT__I_GRAPHICS_CONTEXT__HPP


#include "../Window/Window/IWindow.hpp"


namespace Andromeda
{
    class IGraphicsContext
    {
    public:
        virtual ~IGraphicsContext() = default;

        virtual bool is_initialized() const = 0;
        virtual bool init(IWindow& window) = 0;
        virtual void make_current() = 0;
        virtual void present() = 0;
    };
}


#endif // API_GRAPHICS_CONTEXT__I_GRAPHICS_CONTEXT__HPP