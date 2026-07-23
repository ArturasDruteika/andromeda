#ifndef PLATFORM__PLATFORM__PLATFORM__HPP
#define PLATFORM__PLATFORM__PLATFORM__HPP

#include "../../MacroExports/include/MacroExports.hpp"
#include "pch.hpp"
#include "andromeda/Components/GraphicsBackend.hpp"
#include "andromeda/GraphicsContext/IGraphicsContext.hpp"
#include "andromeda/Platform/IPlatform.hpp"
#include "andromeda/window/window/i_window.hpp"


namespace andromeda::Platform
{
    class PLATFORM_API Platform
        : public IPlatform
    {
    public:
        Platform(const GraphicsBackend& graphicsBackend);
        ~Platform() override;

        bool IsInitialized() const override;
        GraphicsBackend GetGraphicsBackend() const override;
        bool Init(int width, int height, const std::string& title) override;
        void Shutdown() override;

        IGraphicsContext* GetGraphicsContext() const override;
        IWindow* GetWindow() const override;

    private:
        void CreateWindow(int width, int height, const std::string& title);
        void CreateGraphicsContext();

    private:
        bool m_initialized;
        GraphicsBackend m_graphicsBackend;
        std::unique_ptr<IGraphicsContext> m_pGraphicsContext;
        std::unique_ptr<IWindow> m_pWindow;
    };
}


#endif // PLATFORM__PLATFORM__PLATFORM__HPP
