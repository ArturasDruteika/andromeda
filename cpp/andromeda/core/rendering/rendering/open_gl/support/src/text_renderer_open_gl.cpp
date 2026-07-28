#include "../include/text_renderer_open_gl.hpp"

#define STB_EASY_FONT_IMPLEMENTATION
#include "utils/stb/include/stb_easy_font.h"
#include "pch.hpp"

#include "spdlog/spdlog.h"
#include "glad/gl.h"


namespace andromeda::rendering
{
    TextRendererOpenGL::TextRendererOpenGL()
        : m_vao{ 0 }
        , m_vbo{ 0 }
        , m_is_initialized{ false }
    {
    }

    TextRendererOpenGL::~TextRendererOpenGL()
    {
        destroy();
    }

    TextRendererOpenGL::TextRendererOpenGL(TextRendererOpenGL&& other) noexcept
        : m_vao{ 0 }
        , m_vbo{ 0 }
        , m_is_initialized{ false }
    {
        move_from(other);
    }

    TextRendererOpenGL& TextRendererOpenGL::operator=(TextRendererOpenGL&& other) noexcept
    {
        if (this != &other)
        {
            destroy();
            move_from(other);
        }
        return *this;
    }

    void TextRendererOpenGL::move_from(TextRendererOpenGL& other) noexcept
    {
        m_vao = other.m_vao;
        m_vbo = other.m_vbo;
        m_is_initialized = other.m_is_initialized;

        other.m_vao = 0;
        other.m_vbo = 0;
        other.m_is_initialized = false;
    }

    void TextRendererOpenGL::destroy()
    {
        if (m_vbo != 0)
        {
            glDeleteBuffers(1, &m_vbo);
            m_vbo = 0;
        }

        if (m_vao != 0)
        {
            glDeleteVertexArrays(1, &m_vao);
            m_vao = 0;
        }

        m_is_initialized = false;
    }

    bool TextRendererOpenGL::is_valid() const
    {
        return m_is_initialized && m_vao != 0 && m_vbo != 0;
    }

    void TextRendererOpenGL::init()
    {
        if (m_is_initialized)
        {
            return;
        }

        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);

        if (m_vao == 0 || m_vbo == 0)
        {
            spdlog::error("TextRendererOpenGL::init -> VAO or VBO is 0. GL context valid?");
        }

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            0,
            2,
            GL_FLOAT,
            GL_FALSE,
            static_cast<GLsizei>(sizeof(float) * 2),
            reinterpret_cast<void*>(0)
        );

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        m_is_initialized = true;
    }

    void TextRendererOpenGL::render_text(const std::string& text, float x, float y, float scale)
    {
        if (!m_is_initialized)
        {
            spdlog::warn("TextRendererOpenGL::render_text called before init()");
            return;
        }

        if (text.empty())
        {
            return;
        }

        // stb_easy_font outputs an array of vertices with a specific layout:
        //   struct stb_easy_font_vertex { float x,y,z; unsigned char color[4]; };
        // We replicate that layout here.
        struct EasyFontVertex
        {
            float x;
            float y;
            float z;
            unsigned char color[4];
        };

        static const int MAX_QUADS = 1024;
        EasyFontVertex quad_buffer[MAX_QUADS * 4]; // 4 verts per quad

        int num_quads = stb_easy_font_print(
            x,
            y,
            const_cast<char*>(text.c_str()),
            nullptr,                    // we ignore per-vertex color
            quad_buffer,
            sizeof(quad_buffer)
        );

        if (num_quads <= 0)
        {
            return;
        }

        if (num_quads > MAX_QUADS)
        {
            num_quads = MAX_QUADS;
        }

        // We will convert quads to triangles (2 per quad = 6 verts)
        std::vector<float> vertices;
        vertices.reserve(static_cast<std::size_t>(num_quads) * 6U * 2U);

        const float sx = scale;
        const float sy = scale;

        for (int i = 0; i < num_quads; ++i)
        {
            EasyFontVertex* q = quad_buffer + i * 4;

            float x0 = q[0].x * sx;
            float y0 = q[0].y * sy;
            float x1 = q[1].x * sx;
            float y1 = q[1].y * sy;
            float x2 = q[2].x * sx;
            float y2 = q[2].y * sy;
            float x3 = q[3].x * sx;
            float y3 = q[3].y * sy;

            // Two triangles: (v0, v1, v2) and (v0, v2, v3)
            float tri[6 * 2] =
            {
                x0, y0,
                x1, y1,
                x2, y2,

                x0, y0,
                x2, y2,
                x3, y3
            };

            vertices.insert(vertices.end(), tri, tri + 12);
        }

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        glBufferData(
            GL_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(vertices.size() * sizeof(float)),
            vertices.data(),
            GL_DYNAMIC_DRAW
        );

        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size() / 2));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void TextRendererOpenGL::render_debug_quad(
        float x,
        float y,
        float w,
        float h
    )
    {
        if (!m_is_initialized)
        {
            spdlog::warn("TextRendererOpenGL::render_debug_quad called before init()");
            return;
        }

        float vertices[6 * 2] =
        {
            x,      y,
            x + w,  y,
            x + w,  y + h,

            x,      y,
            x + w,  y + h,
            x,      y + h
        };

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        glBufferData(
            GL_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(sizeof(vertices)),
            vertices,
            GL_DYNAMIC_DRAW
        );

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}