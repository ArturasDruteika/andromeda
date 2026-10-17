#include "glad/gl.h"
#include "andromeda/graphics_context/graphics_context_glfw.hpp"
#include "andromeda/window/window_glfw/window_glfw.hpp"

#include "spdlog/spdlog.h"

#include <string>


namespace andromeda::graphics_context
{
    GraphicsContextGLFW::GraphicsContextGLFW()
        : m_initialized{ false }
        , m_p_glfw_window{ nullptr }
    {
    }

    GraphicsContextGLFW::~GraphicsContextGLFW() = default;

    bool GraphicsContextGLFW::is_initialized() const
    {
        return m_initialized;
    }

    bool GraphicsContextGLFW::init(IWindow& window)
    {
        // We only support GLFW-based windows here
        window::WindowGLFW* p_window_glfw = dynamic_cast<window::WindowGLFW*>(&window);
        if (p_window_glfw == nullptr)
        {
            spdlog::error("Failed to initialize graphics context: incompatible window type.");
            return false;
        }

        m_p_glfw_window = static_cast<GLFWwindow*>(p_window_glfw->get_native_handle());
        if (!m_p_glfw_window)
        {
            spdlog::error("Failed to initialize graphics context: native window handle is null.");
            return false;
        }

        // Make context current BEFORE loading GLAD
        glfwMakeContextCurrent(m_p_glfw_window);

        if (glfwGetCurrentContext() == nullptr)
        {
            spdlog::error("Failed to initialize graphics context: unable to activate OpenGL context.");
            return false;
        }

        // Optional: context hints usually belong before window creation,
        // but if you want to keep them here, it's harmless for now.
        set_context_hints();

        if (!load_glad())
        {
            spdlog::error("Failed to initialize graphics context: unable to load OpenGL functions.");
            return false;
        }

        m_initialized = true;
        return true;
    }

    void GraphicsContextGLFW::make_current()
    {
        if (!m_initialized || !m_p_glfw_window)
        {
            spdlog::warn("Cannot activate graphics context: context is not initialized.");
            return;
        }

        glfwMakeContextCurrent(m_p_glfw_window);

        if (glfwGetCurrentContext() == nullptr)
        {
            spdlog::error("Failed to activate OpenGL context.");
        }
    }

    void GraphicsContextGLFW::present()
    {
        if (!m_initialized || !m_p_glfw_window)
        {
            spdlog::warn("Cannot present frame: graphics context is not initialized.");
            return;
        }

        glfwSwapBuffers(m_p_glfw_window);
    }

    void GraphicsContextGLFW::set_context_hints()
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS
#endif
    }

    bool GraphicsContextGLFW::load_glad()
    {
        int glad_version = gladLoadGL(glfwGetProcAddress);
        if (glad_version == 0)
        {
            spdlog::error("Failed to load OpenGL functions: graphics function loader initialization failed.");
            return false;
        }

        spdlog::info(
            "GLAD loaded OpenGL {}.{}",
            GLAD_VERSION_MAJOR(glad_version),
            GLAD_VERSION_MINOR(glad_version)
        );

        const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
        if (version)
        {
            spdlog::info("OpenGL version string: {}", std::string(version));
        }
        else
        {
            spdlog::warn("Unable to retrieve OpenGL version information.");
        }

        return true;
    }
}