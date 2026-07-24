#ifndef RENDERER__OPENGL__SUPPORT__FRAME_BUFFER_OPENGL__HPP
#define RENDERER__OPENGL__SUPPORT__FRAME_BUFFER_OPENGL__HPP


namespace andromeda::rendering
{
    enum class FrameBufferType
    {
        None,
        Color,
        Depth,
        ColorDepth,
        DepthCube
    };


    class FrameBufferOpenGL
    {
    public:
        FrameBufferOpenGL();
        FrameBufferOpenGL(int width, int height, FrameBufferType type);
        ~FrameBufferOpenGL();

        FrameBufferOpenGL(const FrameBufferOpenGL& other) = delete;
        FrameBufferOpenGL& operator=(const FrameBufferOpenGL& other) = delete;
        FrameBufferOpenGL(FrameBufferOpenGL&& other) noexcept;
        FrameBufferOpenGL& operator=(FrameBufferOpenGL&& other) noexcept;

        bool init(int width, int height, FrameBufferType type);
        void resize(int width, int height);

        void bind() const;
        static void unbind();

        // Getters
        unsigned int get_id() const;
        unsigned int get_color_texture() const;        // valid only for ColorDepth
        unsigned int get_depth_renderbuffer() const;   // valid only for ColorDepth
        unsigned int get_depth_texture() const;        // valid only for Depth
        unsigned int get_depth_cube_texture() const;
        int get_width() const;
        int get_height() const;
        FrameBufferType get_frame_buffer_type() const;

    private:
        void destroy();
        bool build();
        bool build_color_depth();
        bool build_depth();
        bool build_depth_cube();
        bool check_status() const;

    private:
        unsigned int m_fbo;
        unsigned int m_color_tex;
        unsigned int m_depth_rbo;
        unsigned int m_depth_tex;
        unsigned int m_depth_cube_tex;
        int m_width;
        int m_height;
        FrameBufferType m_type;
    };
}


#endif // RENDERER__OPENGL__SUPPORT__FRAME_BUFFER_OPENGL__HPP