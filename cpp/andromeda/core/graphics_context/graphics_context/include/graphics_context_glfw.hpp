#ifndef CONTEXT__GLFW_CONTEXT__HPP
#define CONTEXT__GLFW_CONTEXT__HPP


#include "andromeda/graphics_context/i_graphics_context.hpp"
#include "andromeda/window/window/i_window.hpp"

#include "GLFW/glfw3.h"


namespace andromeda::graphics_context
{
    /// @brief GLFW implementation of a graphics context.
    ///
    /// Manages the creation and lifetime of an OpenGL context associated with
    /// a GLFW window, including context activation and buffer presentation.
    class GraphicsContextGLFW
        : public IGraphicsContext
    {
    public:
        /// @brief Constructs an uninitialized graphics context.
        GraphicsContextGLFW();

        /// @brief Destroys the graphics context.
        ~GraphicsContextGLFW() override;

        GraphicsContextGLFW(const GraphicsContextGLFW& other) = delete;
        GraphicsContextGLFW& operator=(const GraphicsContextGLFW& other) = delete;
        GraphicsContextGLFW(GraphicsContextGLFW&& other) noexcept = delete;
        GraphicsContextGLFW& operator=(const GraphicsContextGLFW&& other) noexcept = delete;

        // Getters

        /// @brief Checks whether the graphics context has been initialized.
        ///
        /// @return `true` if the context is initialized; otherwise, `false`.
        bool is_initialized() const override;

        /// @brief Initializes the graphics context for the specified window.
        ///
        /// @param window Window to associate with the graphics context.
        /// @return `true` if initialization succeeded; otherwise, `false`.
        bool init(IWindow& window) override;

        /// @brief Makes this graphics context current.
        void make_current() override;

        /// @brief Presents the rendered frame.
        ///
        /// Swaps the front and back buffers of the associated window.
        void present() override;

        /// @brief Configures GLFW context creation hints.
        void set_context_hints();

    private:
        /// @brief Loads OpenGL functions using GLAD.
        ///
        /// @return `true` if GLAD initialization succeeded; otherwise, `false`.
        bool load_glad();

    private:
        /// @brief Indicates whether the graphics context has been initialized.
        bool m_initialized;

        /// @brief Associated GLFW window.
        GLFWwindow* m_p_glfw_window;
    };
}


#endif // CONTEXT__GLFW_CONTEXT__HPP