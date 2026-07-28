#ifndef RENDERING__OPENGL__SUPPORT__TEXT_RENDERER_OPEN_GL__HPP
#define RENDERING__OPENGL__SUPPORT__TEXT_RENDERER_OPEN_GL__HPP


#include "pch.hpp"
#include "glad/gl.h"


namespace andromeda::rendering
{
    class TextRendererOpenGL
    {
    public:
        TextRendererOpenGL();
        ~TextRendererOpenGL();

        TextRendererOpenGL(const TextRendererOpenGL& other) = delete;
        TextRendererOpenGL& operator=(const TextRendererOpenGL& other) = delete;
        TextRendererOpenGL(TextRendererOpenGL&& other) noexcept;
        TextRendererOpenGL& operator=(TextRendererOpenGL&& other) noexcept;

        // Initializes VAO/VBO for text vertices (vec2 positions).
        // Caller is responsible for binding a suitable shader and setting uniforms.
        void init();

        // x, y are passed directly to stb_easy_font and then scaled on CPU.
        // The coordinate system is whatever your text shader expects (typically screen space).
        void render_text(const std::string& text, float x, float y, float scale = 1.0f);
        void render_debug_quad(float x, float y, float w, float h);

        bool is_valid() const;

    private:
        void destroy();
        void move_from(TextRendererOpenGL& other) noexcept;

    private:
        bool m_is_initialized;
        GLuint m_vao;
        GLuint m_vbo;
    };
}


#endif // RENDERING__OPENGL__SUPPORT__TEXT_RENDERER_OPEN_GL__HPP