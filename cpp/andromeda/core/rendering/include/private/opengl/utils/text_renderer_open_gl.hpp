#pragma once


#include "pch.hpp"
#include "glad/gl.h"


namespace andromeda::rendering
{
    /// @brief Renders simple text using OpenGL.
    ///
    /// Manages the GPU resources required for rendering text and simple debug
    /// primitives.
    class TextRendererOpenGL
    {
    public:
        /// @brief Constructs an uninitialized text renderer.
        TextRendererOpenGL();

        /// @brief Destroys the text renderer and releases its resources.
        ~TextRendererOpenGL();

        TextRendererOpenGL(const TextRendererOpenGL& other) = delete;
        TextRendererOpenGL& operator=(const TextRendererOpenGL& other) = delete;
        TextRendererOpenGL(TextRendererOpenGL&& other) noexcept;
        TextRendererOpenGL& operator=(TextRendererOpenGL&& other) noexcept;

        /// @brief Initializes the OpenGL resources required for text rendering.
        ///
        /// Creates the vertex array and vertex buffer objects used to render
        /// text geometry.
        void init();

        /// @brief Renders a text string.
        ///
        /// @param text Text to render.
        /// @param x Horizontal position.
        /// @param y Vertical position.
        /// @param scale Text scale factor.
        void render_text(const std::string& text, float x, float y, float scale = 1.0f);

        /// @brief Renders a debug quad.
        ///
        /// @param x Horizontal position.
        /// @param y Vertical position.
        /// @param w Quad width.
        /// @param h Quad height.
        void render_debug_quad(float x, float y, float w, float h);

        /// @brief Checks whether the text renderer has been initialized.
        ///
        /// @return `true` if the renderer is initialized; otherwise, `false`.
        bool is_valid() const;

    private:
        /// @brief Releases all OpenGL resources owned by the renderer.
        void destroy();

        /// @brief Transfers ownership of OpenGL resources from another renderer.
        ///
        /// @param other Renderer to move resources from.
        void move_from(TextRendererOpenGL& other) noexcept;

    private:
        /// @brief Indicates whether the renderer has been initialized.
        bool m_is_initialized;

        /// @brief OpenGL vertex array object.
        GLuint m_vao;

        /// @brief OpenGL vertex buffer object.
        GLuint m_vbo;
    };
}
