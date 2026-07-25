#include "../include/platform.hpp"
#include "graphics_context/include/graphics_context_glfw.hpp"
#include "window/window_glfw/include/window_glfw.hpp"
#include "window/events/include/event_dispatcher.hpp"
#include "window/events/include/frame_buffer_events.hpp"

#include "spdlog/spdlog.h"


namespace andromeda::platform
{
    Platform::Platform(const GraphicsBackend& graphics_backend)
        : m_initialized{ false }
        , m_graphics_backend{ graphics_backend }
    {
    }

    Platform::~Platform()
    {
        shutdown();
    }

    bool Platform::is_initialized() const
    {
        return m_initialized;
    }

    GraphicsBackend Platform::get_graphics_backend() const
    {
        return m_graphics_backend;
    }

    bool Platform::init(int width, int height, const std::string& title)
    {
        if (m_initialized)
        {
            spdlog::warn("Platform::init() called but platform is already initialized.");
            return true;
        }

        spdlog::info(
            "Platform::init() starting for backend {}",
            graphics_backend_string(m_graphics_backend)
        );

        // GLFW init is shared for now (OpenGL / Vulkan both need it in your current setup)
        if (!glfwInit())
        {
            spdlog::error("Platform::init() - Failed to initialize GLFW.");
            return false;
        }

        try
        {
            create_window(width, height, title);
            if (!m_p_window)
            {
                spdlog::error("Platform::init() failed: window creation returned nullptr.");
                glfwTerminate();
                return false;
            }

            create_graphics_context();
            if (!m_p_graphics_context)
            {
                spdlog::error("Platform::init() failed: graphics context creation returned nullptr.");
                m_p_window.reset();
                glfwTerminate();
                return false;
            }

            m_p_graphics_context->init(*m_p_window);
            m_p_graphics_context->make_current();

            m_p_window->set_event_callback(
                [this](IEvent& e)
                {
                    // Option A: just pass to engine / application
                    // m_Engine->on_event(e);

                    // Option B: handle some platform-level stuff here
                    window::EventDispatcher dispatcher(e);

                    dispatcher.dispatch<window::WindowCloseEvent>(
                        [this](window::WindowCloseEvent& evt)
                        {
                            // maybe tell engine to stop, etc.
                            return true;
                        });

                    // You can still forward to engine:
                    // m_Engine->on_event(e);
                }
            );

            m_initialized = true;
            spdlog::info("Platform::init() succeeded.");
            return true;
        }
        catch (const std::exception& ex)
        {
            spdlog::error("Exception during Platform::init(): {}", ex.what());
        }
        catch (...)
        {
            spdlog::error("Unknown exception during Platform::init().");
        }

        // Clean up on failure
        m_p_graphics_context.reset();
        m_p_window.reset();
        glfwTerminate();
        return false;
    }

    void Platform::shutdown()
    {
        if (!m_initialized)
        {
            return;
        }

        spdlog::info("Platform::shutdown() starting.");

        // Destroy window and context; GLFWWindow internally destroys GLFWwindow.
        if (m_p_graphics_context)
        {
            // no explicit de_init on context for now; RAII via destructor
            m_p_graphics_context.reset();
        }

        if (m_p_window)
        {
            m_p_window.reset();
        }

        glfwTerminate();

        m_initialized = false;
        spdlog::info("platform shutdown completed.");
    }

    IGraphicsContext* Platform::get_graphics_context() const
    {
        if (!m_p_graphics_context)
        {
            spdlog::warn("Platform::get_graphics_context() called but graphics context is nullptr.");
        }
        return m_p_graphics_context.get();
    }

    IWindow* Platform::get_window() const
    {
        if (!m_p_window)
        {
            spdlog::warn("Platform::get_window() called but window is nullptr.");
        }
        return m_p_window.get();
    }

    void Platform::create_window(int width, int height, const std::string& title)
    {
        spdlog::info(
            "Platform::create_window() for backend {}",
            graphics_backend_string(m_graphics_backend)
        );

        try
        {
            switch (m_graphics_backend)
            {
            case GraphicsBackend::OpenGL:
            case GraphicsBackend::Vulkan:
                // For now both use GLFWWindow
                m_p_window = std::make_unique<window::WindowGLFW>(width, height, title, true);
                if (!m_p_window)
                {
                    spdlog::error("Platform::create_window() - WindowGLFW creation returned nullptr.");
                }
                break;

            case GraphicsBackend::None:
            default:
                spdlog::error(
                    "Platform::create_window(): Unsupported graphics backend {}.",
                    graphics_backend_string(m_graphics_backend)
                );
                m_p_window.reset();
                break;
            }
        }
        catch (const std::exception& ex)
        {
            spdlog::error("Exception in Platform::create_window(): {}", ex.what());
            m_p_window.reset();
        }
        catch (...)
        {
            spdlog::error("Unknown exception in Platform::create_window().");
            m_p_window.reset();
        }
    }

    void Platform::create_graphics_context()
    {
        spdlog::info(
            "Platform::create_graphics_context() for backend {}",
            graphics_backend_string(m_graphics_backend)
        );

        try
        {
            switch (m_graphics_backend)
            {
            case GraphicsBackend::OpenGL:
                m_p_graphics_context = std::make_unique<graphics_context::GraphicsContextGLFW>();
                spdlog::info("Platform::create_graphics_context() created OpenGL (GLFW) graphics context.");
                break;

            case GraphicsBackend::Vulkan:
                spdlog::warn("Platform::create_graphics_context(): Vulkan backend not implemented yet.");
                m_p_graphics_context.reset();
                break;

            case GraphicsBackend::None:
            default:
                spdlog::error(
                    "Platform::create_graphics_context(): Unsupported graphics backend {}.",
                    graphics_backend_string(m_graphics_backend)
                );
                m_p_graphics_context.reset();
                break;
            }
        }
        catch (const std::exception& ex)
        {
            spdlog::error("Exception in Platform::create_graphics_context(): {}", ex.what());
            m_p_graphics_context.reset();
        }
        catch (...)
        {
            spdlog::error("Unknown exception in Platform::create_graphics_context().");
            m_p_graphics_context.reset();
        }
    }
}

namespace andromeda
{
    std::unique_ptr<IPlatform> create_platform(const GraphicsBackend& graphics_backend)
    {
        spdlog::info(
            "create_platform() called with backend {}",
            graphics_backend_string(graphics_backend)
        );

        try
        {
            std::unique_ptr<IPlatform> platform = std::make_unique<platform::Platform>(graphics_backend);
            return platform;
        }
        catch (const std::exception& ex)
        {
            spdlog::error("Exception in create_platform(): {}", ex.what());
        }
        catch (...)
        {
            spdlog::error("Unknown exception in create_platform().");
        }

        return nullptr;
    }
}