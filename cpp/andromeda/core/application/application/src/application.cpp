#include "../include/application.hpp"
#include "engine/engine/include/engine.hpp"

#include "spdlog/spdlog.h"


namespace andromeda::application
{
    Application::Application(GraphicsBackend graphicsBackend)
        : m_initialized{ false }
        , m_graphicsBackend{ graphicsBackend }
        , m_p_platform{ nullptr }
        , m_p_engine{ nullptr }
        , m_p_scene{ nullptr }
        , m_p_window{ nullptr }
        , m_p_context{ nullptr }
        , m_p_renderer{ nullptr }
    {
    }

    Application::~Application()
    {
        if (m_initialized)
        {
            DeInit();
        }
    }

    IRenderer* Application::GetRenderer()
    {
        return m_p_renderer;
    }

    bool Application::Init(unsigned int width, unsigned int height, const std::string& title)
    {
        return init_internal(width, height, title);
    }

    void Application::DeInit()
    {
        if (!m_p_platform && !m_p_engine && !m_p_window && !m_p_context && !m_p_renderer)
        {
            m_initialized = false;
            return;
        }

        // Engine teardown first (it may reference renderer/resources)
        if (m_p_engine)
        {
            m_p_engine->DeInit();
            m_p_engine.reset();
        }

        // platform teardown last (destroys window/context)
        if (m_p_platform)
        {
            m_p_platform->Shutdown();
            m_p_platform.reset();
        }

        m_p_window = nullptr;
        m_p_context = nullptr;
        m_p_renderer = nullptr;
        m_p_scene = nullptr;

        m_initialized = false;
    }

    void Application::SetScene(IScene* pScene)
    {
        m_p_scene = pScene;

        // If your Engine has SetScene, call it here:
        // (You added Engine::SetScene(IScene*))
        if (m_p_engine)
        {
            // Engine::Engine has SetScene, but IEngine does not in your original API.
            // If you want this call through IEngine, add SetScene to IEngine too.
            // For now, dynamic_cast safely if needed:
            auto* pEngineImpl = dynamic_cast<Engine::Engine*>(m_p_engine.get());
            if (pEngineImpl)
            {
                pEngineImpl->SetScene(m_p_scene);
            }
        }
    }

    int Application::Run()
    {
        if (!m_initialized)
        {
            spdlog::error("Application::Run() called but application is not initialized.");
            return -1;
        }

        if (!m_p_scene)
        {
            spdlog::error("Application::Run() called but scene is null. Call SetScene() first.");
            return -1;
        }

        // Ensure engine sees the scene (if not already connected)
        if (m_p_engine)
        {
            Engine::Engine* pEngineImpl = dynamic_cast<Engine::Engine*>(m_p_engine.get());
            if (pEngineImpl)
            {
                pEngineImpl->SetScene(m_p_scene);
            }
        }

        RenderLoop();
        
        return 0;
    }

    bool Application::init_platform(unsigned int width, unsigned int height, const std::string& title)
    {
        m_p_platform = CreatePlatform(m_graphicsBackend);
        if (!m_p_platform)
        {
            spdlog::error("CreatePlatform() returned nullptr.");
            return false;
        }

        if (!m_p_platform->Init(width, height, title))
        {
            spdlog::error("Failed to initialize platform.");
            return false;
        }

        return true;
    }

    bool Application::init_engine()
    {
        m_p_engine = CreateEngine(m_graphicsBackend);
        if (!m_p_engine)
        {
            spdlog::error("CreateEngine() returned nullptr.");
            return false;
        }

        if (!m_p_engine->Init())
        {
            spdlog::error("Engine::Init() failed.");
            return false;
        }

        return true;
    }

    bool Application::init_renderer(int width, int height)
    {
        // You had: pRenderer->Init(width, height, false);
        m_p_renderer->Init(width, height, false);
        return true;
    }

    bool Application::init_internal(unsigned int width, unsigned int height, const std::string &title)
    {
        if (m_initialized)
        {
            spdlog::warn("Application::Init() called but application is already initialized.");
            return true;
        }

        if (!init_platform(width, height, title))
        {
            spdlog::error("Application::Init() failed: platform init failed.");
            return false;
        }

        if (!init_engine())
        {
            spdlog::error("Application::Init() failed: engine init failed.");
            DeInit();
            return false;
        }

        m_p_window = m_p_platform->GetWindow();
        m_p_context = m_p_platform->GetGraphicsContext();
        m_p_renderer = m_p_engine->GetRenderer();

        if (!m_p_window || !m_p_context || !m_p_renderer)
        {
            spdlog::error("Application::Init() failed: window/context/renderer is null.");
            DeInit();
            return false;
        }

        connect_events();

        if (!init_renderer(static_cast<int>(width), static_cast<int>(height)))
        {
            spdlog::error("Application::Init() failed: renderer init failed.");
            DeInit();
            return false;
        }
        m_initialized = true;
        return true;
    }

    void Application::connect_events()
    {
        // This is the thing you wanted hidden from main:
        // Window pushes IEvent -> Engine consumes it.
        m_p_window->SetEventCallback([this](IEvent& e)
            {
                if (m_p_engine)
                {
                    m_p_engine->OnEvent(e);
                }
            });
    }

    void Application::RenderLoop()
    {
        while (!m_p_window->ShouldClose())
        {
            m_p_window->PollEvents();
            if (m_p_scene)
            {
                m_p_scene->Update(0.016f); // Example deltaTime (60Hz)
            }
            m_p_renderer->RenderFrame(*m_p_scene);
            m_p_context->Present();
        }
    }
}


namespace andromeda
{
    std::unique_ptr<IApplication> CreateApp(const GraphicsBackend& graphicsBackend)
    {
        spdlog::info(
            "CreateApplication() called with backend {}",
            GraphicsBackendString(graphicsBackend)
        );

        try
        {
            std::unique_ptr<IApplication> application = std::make_unique<application::Application>(graphicsBackend);
            return application;
        }
        catch (const std::exception& ex)
        {
            spdlog::error("Exception in CreateApplication(): {}", ex.what());
        }
        catch (...)
        {
            spdlog::error("Unknown exception in CreateApplication().");
        }

        return nullptr;
    }
}

