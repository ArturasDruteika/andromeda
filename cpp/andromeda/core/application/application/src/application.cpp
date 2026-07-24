#include "../include/application.hpp"
#include "engine/engine/include/engine.hpp"

#include "spdlog/spdlog.h"


namespace andromeda::application
{
    Application::Application(GraphicsBackend graphics_backend)
        : m_initialized{ false }
        , m_graphics_backend{ graphics_backend }
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
            de_init();
        }
    }

    IRenderer* Application::get_renderer()
    {
        return m_p_renderer;
    }

    bool Application::init(unsigned int width, unsigned int height, const std::string& title)
    {
        return init_internal(width, height, title);
    }

    void Application::de_init()
    {
        if (!m_p_platform && !m_p_engine && !m_p_window && !m_p_context && !m_p_renderer)
        {
            m_initialized = false;
            return;
        }

        // Engine teardown first (it may reference renderer/resources)
        if (m_p_engine)
        {
            m_p_engine->de_init();
            m_p_engine.reset();
        }

        // platform teardown last (destroys window/context)
        if (m_p_platform)
        {
            m_p_platform->shutdown();
            m_p_platform.reset();
        }

        m_p_window = nullptr;
        m_p_context = nullptr;
        m_p_renderer = nullptr;
        m_p_scene = nullptr;

        m_initialized = false;
    }

    void Application::set_scene(IScene* p_scene)
    {
        m_p_scene = p_scene;

        // If your Engine has set_scene, call it here:
        // (You added engine::set_scene(IScene*))
        if (m_p_engine)
        {
            // engine::Engine has set_scene, but IEngine does not in your original API.
            // If you want this call through IEngine, add set_scene to IEngine too.
            // For now, dynamic_cast safely if needed:
            auto* p_engine_impl = dynamic_cast<engine::Engine*>(m_p_engine.get());
            if (p_engine_impl)
            {
                p_engine_impl->set_scene(m_p_scene);
            }
        }
    }

    int Application::run()
    {
        if (!m_initialized)
        {
            spdlog::error("Application::run() called but application is not initialized.");
            return -1;
        }

        if (!m_p_scene)
        {
            spdlog::error("Application::run() called but scene is null. Call set_scene() first.");
            return -1;
        }

        // Ensure engine sees the scene (if not already connected)
        if (m_p_engine)
        {
            engine::Engine* p_engine_impl = dynamic_cast<engine::Engine*>(m_p_engine.get());
            if (p_engine_impl)
            {
                p_engine_impl->set_scene(m_p_scene);
            }
        }

        run();
        
        return 0;
    }

    bool Application::init_platform(unsigned int width, unsigned int height, const std::string& title)
    {
        m_p_platform = create_platform(m_graphics_backend);
        if (!m_p_platform)
        {
            spdlog::error("create_platform() returned nullptr.");
            return false;
        }

        if (!m_p_platform->init(width, height, title))
        {
            spdlog::error("Failed to initialize platform.");
            return false;
        }

        return true;
    }

    bool Application::init_engine()
    {
        m_p_engine = create_engine(m_graphics_backend);
        if (!m_p_engine)
        {
            spdlog::error("create_engine() returned nullptr.");
            return false;
        }

        if (!m_p_engine->init())
        {
            spdlog::error("engine::init() failed.");
            return false;
        }

        return true;
    }

    bool Application::init_renderer(int width, int height)
    {
        // You had: pRenderer->init(width, height, false);
        m_p_renderer->init(width, height, false);
        return true;
    }

    bool Application::init_internal(unsigned int width, unsigned int height, const std::string &title)
    {
        if (m_initialized)
        {
            spdlog::warn("Application::init() called but application is already initialized.");
            return true;
        }

        if (!init_platform(width, height, title))
        {
            spdlog::error("Application::init() failed: platform init failed.");
            return false;
        }

        if (!init_engine())
        {
            spdlog::error("Application::init() failed: engine init failed.");
            de_init();
            return false;
        }

        m_p_window = m_p_platform->get_window();
        m_p_context = m_p_platform->get_graphics_context();
        m_p_renderer = m_p_engine->get_renderer();

        if (!m_p_window || !m_p_context || !m_p_renderer)
        {
            spdlog::error("Application::init() failed: window/context/renderer is null.");
            de_init();
            return false;
        }

        connect_events();

        if (!init_renderer(static_cast<int>(width), static_cast<int>(height)))
        {
            spdlog::error("Application::init() failed: renderer init failed.");
            de_init();
            return false;
        }
        m_initialized = true;
        return true;
    }

    void Application::connect_events()
    {
        // This is the thing you wanted hidden from main:
        // Window pushes IEvent -> Engine consumes it.
        m_p_window->set_event_callback([this](IEvent& e)
            {
                if (m_p_engine)
                {
                    m_p_engine->on_event(e);
                }
            });
    }

    void Application::run()
    {
        while (!m_p_window->should_close())
        {
            m_p_window->poll_events();
            if (m_p_scene)
            {
                m_p_scene->update(0.016f); // Example deltaTime (60Hz)
            }
            m_p_renderer->render_frame(*m_p_scene);
            m_p_context->present();
        }
    }
}


namespace andromeda
{
    std::unique_ptr<IApplication> create_app(const GraphicsBackend& graphics_backend)
    {
        spdlog::info(
            "CreateApplication() called with backend {}",
            graphics_backend_string(graphics_backend)
        );

        try
        {
            std::unique_ptr<IApplication> application = std::make_unique<application::Application>(graphics_backend);
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

