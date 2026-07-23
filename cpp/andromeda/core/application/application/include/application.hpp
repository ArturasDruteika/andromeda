#ifndef APPLICATION__APPLICATION__HPP
#define APPLICATION__APPLICATION__HPP


#include "andromeda/components/graphics_backend.hpp"
#include "andromeda/application/i_application.hpp"
#include "andromeda/engine/i_engine.hpp"
#include "andromeda/platform/i_platform.hpp"
#include "andromeda/space/scene/i_scene.hpp"
#include "pch.hpp"


namespace andromeda::application
{
    class Application
        : public virtual IApplication
    {
    public:
        explicit Application(GraphicsBackend graphicsBackend);
        ~Application() override;

        Application(const Application& other) = delete;
        Application& operator=(const Application& other) = delete;

        Application(Application&& other) noexcept = delete;
        Application& operator=(Application&& other) noexcept = delete;

        // Getters
        IRenderer* GetRenderer() override;

        bool Init(
            unsigned int width, 
            unsigned int height, 
            const std::string& title
        ) override;
        void DeInit() override;

        void SetScene(IScene* pScene) override;

        // Returns 0 on clean exit, non-zero on error
        int Run() override;

    private:
        bool init_platform(
            unsigned int width, 
            unsigned int height, 
            const std::string& title
        );
        bool init_engine();
        bool init_renderer(int width, int height);
        bool init_internal(
            unsigned int width, 
            unsigned int height, 
            const std::string& title
        );
        void connect_events();
        void RenderLoop();

    private:
        bool m_initialized;
        GraphicsBackend m_graphicsBackend;

        std::unique_ptr<IPlatform> m_p_platform;
        std::unique_ptr<IEngine> m_p_engine;

        IScene* m_p_scene;
        IWindow* m_p_window;
        IGraphicsContext* m_p_context;
        IRenderer* m_p_renderer;
    };
}

#endif // APPLICATION__APPLICATION__HPP
