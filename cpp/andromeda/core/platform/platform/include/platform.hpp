#ifndef PLATFORM__PLATFORM__PLATFORM__HPP
#define PLATFORM__PLATFORM__PLATFORM__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "pch.hpp"
#include "andromeda/components/graphics_backend.hpp"
#include "andromeda/graphics_context/i_graphics_context.hpp"
#include "andromeda/platform/i_platform.hpp"
#include "andromeda/window/window/i_window.hpp"


namespace andromeda::platform
{
    class PLATFORM_API Platform
        : public IPlatform
    {
    public:
        Platform(const GraphicsBackend& graphics_backend);
        ~Platform() override;

        bool is_initialized() const override;
        GraphicsBackend get_graphics_backend() const override;
        bool init(int width, int height, const std::string& title) override;
        void shutdown() override;

        IGraphicsContext* get_graphics_context() const override;
        IWindow* get_window() const override;

    private:
        void create_window(int width, int height, const std::string& title);
        void create_graphics_context();

    private:
        bool m_initialized;
        GraphicsBackend m_graphics_backend;
        std::unique_ptr<IGraphicsContext> m_p_graphics_context;
        std::unique_ptr<IWindow> m_p_window;
    };
}


#endif // PLATFORM__PLATFORM__PLATFORM__HPP
