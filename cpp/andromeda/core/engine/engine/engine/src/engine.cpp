#include "../include/Engine.hpp"
#include "rendering/renderers/renderers/include/renderer_open_gl.hpp"
#include "andromeda/window/events/event_type.hpp"
#include "andromeda/window/mouse_and_key_codes/mouse_codes.hpp"
#include "andromeda/window/mouse_and_key_codes/key_codes.hpp"
#include "andromeda/window/events/i_frame_buffer_events.hpp"
#include "andromeda/window/events/i_key_events.hpp"
#include "andromeda/window/events/i_mouse_events.hpp"
#include "andromeda/space/camera/i_camera_controller.hpp"

#include "spdlog/spdlog.h"


namespace andromeda::engine
{
    static constexpr float DEFAULT_MOUSE_YAW_SENSITIVITY = 0.005f;
    static constexpr float DEFAULT_MOUSE_PITCH_SENSITIVITY = 0.005f;
    static constexpr float DEFAULT_MOUSE_ROLL_SENSITIVITY = 0.005f;
    static constexpr float DEFAULT_SCROLL_ZOOM_SENSITIVITY = 0.25f;

    Engine::Engine(const GraphicsBackend& graphics_backend)
        : m_initialized{ false }
        , m_graphics_backend{ graphics_backend }
        , m_renderer{ nullptr }
        , m_p_scene{ nullptr }
        , m_is_left_mouse_down{ false }
        , m_is_ctrl_down{ false }
        , m_has_last_mouse_pos{ false }
        , m_last_mouse_x{ 0.0f }
        , m_last_mouse_y{ 0.0f }
        , m_mouse_yaw_sensitivity{ DEFAULT_MOUSE_YAW_SENSITIVITY }
        , m_mouse_pitch_sensitivity{ DEFAULT_MOUSE_PITCH_SENSITIVITY }
        , m_mouse_roll_sensitivity{ DEFAULT_MOUSE_ROLL_SENSITIVITY }
        , m_scroll_zoom_sensitivity{ DEFAULT_SCROLL_ZOOM_SENSITIVITY }
    {
        spdlog::info(
            "Engine constructed with graphics backend {}",
            graphics_backend_string(m_graphics_backend)
        );
    }

    Engine::~Engine()
    {
        if (m_initialized)
        {
            try
            {
                spdlog::info("Engine destructor: deinitializing engine.");
                de_init();
            }
            catch (const std::exception& ex)
            {
                spdlog::error("Exception in Engine::~Engine during de_init: {}", ex.what());
            }
            catch (...)
            {
                spdlog::error("Unknown exception in Engine::~Engine during de_init.");
            }
        }
        else
        {
            spdlog::info("Engine destructor: engine was not initialized, nothing to deinitialize.");
        }
    }

    bool Engine::is_initialized() const
    {
        return m_initialized;
    }

    GraphicsBackend Engine::get_graphics_backend() const
    {
        return m_graphics_backend;
    }

    IRenderer* Engine::get_renderer() const
    {
        if (!m_renderer)
        {
            spdlog::warn("Engine::get_renderer() called but renderer is nullptr.");
        }
        return m_renderer.get();
    }

    bool Engine::init()
    {
        if (m_initialized)
        {
            spdlog::warn("Engine::init() called, but engine is already initialized.");
            return true;
        }

        spdlog::info(
            "Engine::init() starting for backend {}",
            graphics_backend_string(m_graphics_backend)
        );

        try
        {
            create_renderer();
            if (!m_renderer)
            {
                spdlog::error("Engine::init() failed: renderer creation returned nullptr.");
                return false;
            }
        }
        catch (const std::exception& ex)
        {
            spdlog::error("Exception during Engine::init(): {}", ex.what());
            try
            {
                destroy_renderer();
            }
            catch (...)
            {
                spdlog::error("Exception during cleanup in Engine::init().");
            }
            return false;
        }
        catch (...)
        {
            spdlog::error("Unknown exception during Engine::init().");
            try
            {
                destroy_renderer();
            }
            catch (...)
            {
                spdlog::error("Exception during cleanup in Engine::init() after unknown error.");
            }
            return false;
        }

        m_initialized = true;
        spdlog::info("Engine::init() succeeded.");
        return true;
    }

    void Engine::de_init()
    {
        if (!m_initialized)
        {
            spdlog::warn("Engine::de_init() called but engine is not initialized.");
            return;
        }

        spdlog::info("Engine::de_init() starting.");

        try
        {
            destroy_renderer();
        }
        catch (const std::exception& ex)
        {
            spdlog::error("Exception in Engine::de_init() while destroying renderer: {}", ex.what());
        }
        catch (...)
        {
            spdlog::error("Unknown exception in Engine::de_init() while destroying renderer.");
        }

        m_initialized = false;
        spdlog::info("Engine::de_init() finished. Engine is now deinitialized.");
    }

    void Engine::set_scene(IScene* p_scene)
    {
        m_p_scene = p_scene;
    }

    static ICameraController* get_active_camera_controller_from_scene(IScene* p_scene)
    {
        if (!p_scene)
        {
            return nullptr;
        }

        // Assumption: IScene::get_active_camera() exists and returns an ICamera* (or something base).
        // If your actual API differs, adjust this part.
        ICamera* p_camera_base = p_scene->get_active_camera();
        if (!p_camera_base)
        {
            return nullptr;
        }

        // We need rotate/zoom, so cast to ICameraController.
        return dynamic_cast<ICameraController*>(p_camera_base);
    }

    void Engine::on_event(IEvent& event)
    {
        switch (event.get_event_type())
        {
            case EventType::MouseScrolled:
            {
                handle_mouse_scrolled(event);
                break;
            }

            case EventType::MouseButtonPressed:
            {
                handle_mouse_button_pressed(event);
                break;
            }

            case EventType::MouseButtonReleased:
            {
                handle_mouse_button_released(event);
                break;
            }

            case EventType::KeyPressed:
            {
                handle_key_pressed(event);
                break;
            }

            case EventType::KeyReleased:
            {
                handle_key_released(event);
                break;
            }

            case EventType::MouseMoved:
            {
                handle_mouse_moved(event);
                break;
            }

            case EventType::WindowResize:
            {
                handle_window_resize(event);
                break;
            }

            case EventType::WindowClose:
            {
                handle_window_close(event);
                break;
            }

            default:
            {
                break;
            }
        }
    }

    void Engine::create_renderer()
    {
        spdlog::info(
            "Engine::create_renderer() for backend {}",
            graphics_backend_string(m_graphics_backend)
        );

        try
        {
            switch (m_graphics_backend)
            {
            case GraphicsBackend::OpenGL:
            {
                m_renderer = std::make_unique<Rendering::RendererOpenGL>();
                spdlog::info("Engine::create_renderer() created OpenGL renderer.");
                break;
            }

            case GraphicsBackend::Vulkan:
            {
                spdlog::warn("Engine::create_renderer(): Vulkan backend not implemented yet.");
                m_renderer.reset();
                break;
            }

            case GraphicsBackend::None:
            default:
            {
                spdlog::error(
                    "Engine::create_renderer(): Unknown graphics backend {}.",
                    graphics_backend_string(m_graphics_backend)
                );
                m_renderer.reset();
                break;
            }
            }
        }
        catch (const std::exception& ex)
        {
            spdlog::error("Exception in Engine::create_renderer(): {}", ex.what());
            m_renderer.reset();
        }
        catch (...)
        {
            spdlog::error("Unknown exception in Engine::create_renderer().");
            m_renderer.reset();
        }
    }

    void Engine::destroy_renderer()
    {
        if (!m_renderer)
        {
            spdlog::warn("Engine::destroy_renderer() called but renderer is already nullptr.");
            return;
        }

        spdlog::info("Engine::destroy_renderer() starting.");

        try
        {
            m_renderer->de_init();
        }
        catch (const std::exception& ex)
        {
            spdlog::error("Exception in Engine::destroy_renderer() during renderer->de_init(): {}", ex.what());
        }
        catch (...)
        {
            spdlog::error("Unknown exception in Engine::destroy_renderer() during renderer->de_init().");
        }

        m_renderer.reset();
        spdlog::info("Engine::destroy_renderer() finished, renderer reset to nullptr.");
    }

    void Engine::handle_mouse_scrolled(IEvent& event)
    {
        IMouseScrolledEvent* p_event = dynamic_cast<IMouseScrolledEvent*>(&event);
        if (!p_event)
        {
            return;
        }

        ICameraController* p_camera = get_active_camera_controller_from_scene(m_p_scene);
        if (!p_camera)
        {
            return;
        }

        const float zoom_delta = -p_event->get_y_offset() * m_scroll_zoom_sensitivity;
        p_camera->zoom(zoom_delta);
    }

    void Engine::handle_mouse_button_pressed(IEvent& event)
    {
        IMouseButtonPressedEvent* p_event = dynamic_cast<IMouseButtonPressedEvent*>(&event);
        if (!p_event)
        {
            return;
        }

        if (p_event->get_mouse_button() == ButtonLeft)
        {
            m_is_left_mouse_down = true;
            m_has_last_mouse_pos = false;
        }
    }

    void Engine::handle_mouse_button_released(IEvent& event)
    {
        IMouseButtonReleasedEvent* p_event = dynamic_cast<IMouseButtonReleasedEvent*>(&event);
        if (!p_event)
        {
            return;
        }

        if (p_event->get_mouse_button() == ButtonLeft)
        {
            m_is_left_mouse_down = false;
            m_has_last_mouse_pos = false;
        }
    }

    void Engine::handle_key_pressed(IEvent& event)
    {
        IKeyPressedEvent* p_event = dynamic_cast<IKeyPressedEvent*>(&event);
        if (!p_event)
        {
            return;
        }

        const KeyCode key = p_event->get_key_code();
        if (key == LeftControl || key == RightControl)
        {
            m_is_ctrl_down = true;
        }
    }

    void Engine::handle_key_released(IEvent& event)
    {
        IKeyReleasedEvent* p_event = dynamic_cast<IKeyReleasedEvent*>(&event);
        if (!p_event)
        {
            return;
        }

        const KeyCode key = p_event->get_key_code();
        if (key == LeftControl || key == RightControl)
        {
            m_is_ctrl_down = false;
        }
    }

    void Engine::handle_mouse_moved(IEvent& event)
    {
        IMouseMovedEvent* p_event = dynamic_cast<IMouseMovedEvent*>(&event);
        if (!p_event)
        {
            return;
        }

        ICameraController* p_camera = get_active_camera_controller_from_scene(m_p_scene);
        if (!p_camera)
        {
            return;
        }

        const float x = p_event->get_x();
        const float y = p_event->get_y();

        if (!m_is_left_mouse_down)
        {
            m_last_mouse_x = x;
            m_last_mouse_y = y;
            m_has_last_mouse_pos = true;
            return;
        }

        if (!m_has_last_mouse_pos)
        {
            m_last_mouse_x = x;
            m_last_mouse_y = y;
            m_has_last_mouse_pos = true;
            return;
        }

        const float dx = x - m_last_mouse_x;
        const float dy = y - m_last_mouse_y;

        m_last_mouse_x = x;
        m_last_mouse_y = y;

        if (m_is_ctrl_down)
        {
            const float roll = dx * m_mouse_roll_sensitivity;
            p_camera->rotate(0.0f, 0.0f, roll);
        }
        else
        {
            const float yaw = dx * m_mouse_yaw_sensitivity;
            const float pitch = dy * m_mouse_pitch_sensitivity;
            p_camera->rotate(yaw, pitch, 0.0f);
        }
    }

    void Engine::handle_window_resize(IEvent& event)
    {
        IWindowResizeEvent* p_event = dynamic_cast<IWindowResizeEvent*>(&event);
        if (!p_event)
        {
            return;
        }

        // If you want: update camera aspect or renderer viewport.
        // Renderer likely should react to framebuffer size, but window size can also be used.
        if (m_renderer)
        {
            float aspect = static_cast<float>(p_event->get_width()) / static_cast<float>(p_event->get_height());
            m_p_scene->get_active_camera()->set_aspect(aspect);
            m_renderer->resize(p_event->get_width(), p_event->get_height());
        }
    }

    void Engine::handle_framebuffer_resize(IEvent& event)
    {
        IFramebufferResizeEvent* p_event = dynamic_cast<IFramebufferResizeEvent*>(&event);
        if (!p_event)
        {
            return;
        }

        // Most correct place to resize GL viewport and projection aspects.
        if (m_renderer)
        {
            m_renderer->resize(p_event->get_width(), p_event->get_height());
        }

        // Optional: if your camera projection is owned by the scene active camera,
        // you can update aspect here too (depends on your API).
    }

    void Engine::handle_window_close(IEvent& event)
    {
        IWindowCloseEvent* p_event = dynamic_cast<IWindowCloseEvent*>(&event);
        if (!p_event)
        {
            return;
        }

        // Usually you don't "close" here; platform/Window sets ShouldClose().
        // But you may still want to mark handled or run shutdown logic.
        event.set_handled(true);
    }

}

namespace andromeda
{
    std::unique_ptr<IEngine> create_engine(const GraphicsBackend& graphics_backend)
    {
        spdlog::info(
            "create_engine() called with backend {}",
            GraphicsBackendString(graphics_backend)
        );

        try
        {
            std::unique_ptr<IEngine> engine = std::make_unique<engine::Engine>(graphics_backend);
            return engine;
        }
        catch (const std::exception& ex)
        {
            spdlog::error("Exception in create_engine(): {}", ex.what());
        }
        catch (...)
        {
            spdlog::error("Unknown exception in create_engine().");
        }

        return nullptr;
    }
}
