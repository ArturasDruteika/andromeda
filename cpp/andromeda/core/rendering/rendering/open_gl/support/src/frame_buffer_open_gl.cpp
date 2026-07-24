#include "../include/frame_buffer_open_gl.hpp"
#include "glad/gl.h"
#include "spdlog/spdlog.h"


namespace andromeda::rendering
{
    FrameBufferOpenGL::FrameBufferOpenGL()
        : m_fbo{ 0 }
        , m_color_tex{ 0 }
        , m_depth_rbo{ 0 }
        , m_depth_tex{ 0 }
        , m_depth_cube_tex{ 0 }
        , m_width{ 0 }
        , m_height{ 0 }
        , m_type{ FrameBufferType::None }
    {
    }

    FrameBufferOpenGL::FrameBufferOpenGL(int width, int height, FrameBufferType type)
        : m_fbo{ 0 }
        , m_color_tex{ 0 }
        , m_depth_rbo{ 0 }
        , m_depth_tex{ 0 }
        , m_depth_cube_tex{ 0 }
        , m_width{ width }
        , m_height{ height }
        , m_type{ type }
    {
        init(width, height, type);
    }


    FrameBufferOpenGL::~FrameBufferOpenGL()
    {
        destroy();
    }

    FrameBufferOpenGL::FrameBufferOpenGL(FrameBufferOpenGL&& other) noexcept
    {
        *this = std::move(other);
    }

    FrameBufferOpenGL& FrameBufferOpenGL::operator=(FrameBufferOpenGL&& other) noexcept
    {
        if (this == &other)
            return *this;

        destroy();

        m_fbo = other.m_fbo;
        m_color_tex = other.m_color_tex;
        m_depth_rbo = other.m_depth_rbo;
        m_depth_tex = other.m_depth_tex;
        m_depth_cube_tex = other.m_depth_cube_tex;
        m_width = other.m_width;
        m_height = other.m_height;
        m_type = other.m_type;

        other.m_fbo = 0;
        other.m_color_tex = 0;
        other.m_depth_rbo = 0;
        other.m_depth_tex = 0;
        other.m_depth_cube_tex = 0;
        other.m_width = 0;
        other.m_height = 0;

        return *this;
    }

    bool FrameBufferOpenGL::init(int width, int height, FrameBufferType type)
    {
        destroy();

        m_width = width;
        m_height = height;
        m_type = type;

        if (m_width <= 0 || m_height <= 0)
        {
            spdlog::error("FrameBufferOpenGL::init: invalid size {}x{}", m_width, m_height);
            return false;
        }

        return build();
    }

    void FrameBufferOpenGL::resize(int width, int height)
    {
        if (width == m_width && height == m_height)
            return;

        init(width, height, m_type);
    }

    void FrameBufferOpenGL::bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    }

    void FrameBufferOpenGL::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    unsigned int FrameBufferOpenGL::get_id() const
    {
        return m_fbo;
    }

    unsigned int FrameBufferOpenGL::get_color_texture() const
    {
        return m_color_tex;
    }

    unsigned int FrameBufferOpenGL::get_depth_renderbuffer() const
    {
        return m_depth_rbo;
    }

    unsigned int FrameBufferOpenGL::get_depth_texture() const
    {
        return m_depth_tex;
    }

    unsigned int FrameBufferOpenGL::get_depth_cube_texture() const
    {
        return m_depth_cube_tex;
    }

    int FrameBufferOpenGL::get_width() const
    {
        return m_width;
    }

    int FrameBufferOpenGL::get_height() const
    {
        return m_height;
    }

    FrameBufferType FrameBufferOpenGL::get_frame_buffer_type() const
    {
        return m_type;
    }

    void FrameBufferOpenGL::destroy()
    {
        if (m_color_tex)
        {
            glDeleteTextures(1, &m_color_tex);
            m_color_tex = 0;
        }
        if (m_depth_tex)
        {
            glDeleteTextures(1, &m_depth_tex);
            m_depth_tex = 0;
        }
        if (m_depth_rbo)
        {
            glDeleteRenderbuffers(1, &m_depth_rbo);
            m_depth_rbo = 0;
        }
        if (m_fbo)
        {
            glDeleteFramebuffers(1, &m_fbo);
            m_fbo = 0;
        }
        if (m_depth_cube_tex)
        {
            glDeleteTextures(1, &m_depth_cube_tex);
            m_depth_cube_tex = 0;
        }
    }

    bool FrameBufferOpenGL::build()
    {
        switch (m_type)
        {
        case FrameBufferType::ColorDepth:
            return build_color_depth();
        case FrameBufferType::Depth:
            return build_depth();
        case FrameBufferType::DepthCube:
            return build_depth_cube();
        default:
            spdlog::error("FrameBufferOpenGL::build: unknown type");
            return false;
        }
    }

    bool FrameBufferOpenGL::build_color_depth()
    {
        glGenFramebuffers(1, &m_fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

        // Create color texture
        glGenTextures(1, &m_color_tex);
        glBindTexture(GL_TEXTURE_2D, m_color_tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_tex, 0);

        // Create depth renderbuffer
        glGenRenderbuffers(1, &m_depth_rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, m_depth_rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_width, m_height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth_rbo);

        GLenum draw_buffers[1] = { GL_COLOR_ATTACHMENT0 };
        glDrawBuffers(1, draw_buffers);

        bool ok = check_status();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return ok;
    }

    bool FrameBufferOpenGL::build_depth()
    {
        glGenFramebuffers(1, &m_fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

        glGenTextures(1, &m_depth_tex);
        glBindTexture(GL_TEXTURE_2D, m_depth_tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        float border_color[] = { 1, 1, 1, 1 };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_tex, 0);

        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);

        bool ok = check_status();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return ok;
    }

    bool FrameBufferOpenGL::build_depth_cube()
    {
        glGenFramebuffers(1, &m_fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

        glGenTextures(1, &m_depth_cube_tex);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_depth_cube_tex);

        // kill mipmap ambiguity across resizes
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0);

        // safer internal format/type pairing for depth
        for (int i = 0; i < 6; ++i)
        {
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_DEPTH_COMPONENT32F,     // <-- use 32F for GL_FLOAT
                m_width,
                m_height,
                0,
                GL_DEPTH_COMPONENT,
                GL_FLOAT,
                nullptr
            );
            // If you prefer 24-bit: internal=GL_DEPTH_COMPONENT24, type=GL_UNSIGNED_INT
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        // attach the WHOLE cubemap (layered)
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_depth_cube_tex, 0);

        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);

        bool ok = check_status();               // checks the currently bound FBO
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return ok;
    }

    bool FrameBufferOpenGL::check_status() const
    {
        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE)
        {
            spdlog::error("Framebuffer not complete! Status: 0x{:X}", status);
            return false;
        }
        return true;
    }
}