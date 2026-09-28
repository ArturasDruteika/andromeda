#pragma once


namespace andromeda::rendering
{
    /// @brief Enumerates the supported framebuffer configurations.
    enum class FrameBufferType
    {
        /// @brief No framebuffer attachments.
        None,

        /// @brief Color attachment only.
        Color,

        /// @brief Depth attachment only.
        Depth,

        /// @brief Combined color and depth attachments.
        ColorDepth,

        /// @brief Depth cubemap attachment.
        DepthCube
    };


    /// @brief Represents an OpenGL framebuffer object.
    ///
    /// Manages framebuffer creation, resizing, binding, and destruction,
    /// together with its associated color and depth attachments.
    class FrameBufferOpenGL
    {
    public:
        /// @brief Constructs an uninitialized framebuffer.
        FrameBufferOpenGL();

        /// @brief Constructs and initializes a framebuffer.
        ///
        /// @param width Framebuffer width in pixels.
        /// @param height Framebuffer height in pixels.
        /// @param type Framebuffer configuration.
        FrameBufferOpenGL(int width, int height, FrameBufferType type);

        /// @brief Destroys the framebuffer and its attachments.
        ~FrameBufferOpenGL();

        FrameBufferOpenGL(const FrameBufferOpenGL& other) = delete;
        FrameBufferOpenGL& operator=(const FrameBufferOpenGL& other) = delete;
        FrameBufferOpenGL(FrameBufferOpenGL&& other) noexcept;
        FrameBufferOpenGL& operator=(FrameBufferOpenGL&& other) noexcept;

        /// @brief Initializes the framebuffer.
        ///
        /// @param width Framebuffer width in pixels.
        /// @param height Framebuffer height in pixels.
        /// @param type Framebuffer configuration.
        /// @return `true` if initialization succeeded; otherwise, `false`.
        bool init(int width, int height, FrameBufferType type);

        /// @brief Resizes the framebuffer and recreates its attachments.
        ///
        /// @param width New framebuffer width in pixels.
        /// @param height New framebuffer height in pixels.
        void resize(int width, int height);

        /// @brief Binds the framebuffer.
        void bind() const;

        /// @brief Binds the default framebuffer.
        static void unbind();

        // Getters

        /// @brief Retrieves the OpenGL framebuffer object identifier.
        ///
        /// @return Framebuffer object identifier.
        unsigned int get_id() const;

        /// @brief Retrieves the color texture attachment.
        ///
        /// Valid only for `FrameBufferType::ColorDepth`.
        ///
        /// @return Color texture identifier.
        unsigned int get_color_texture() const;

        /// @brief Retrieves the depth renderbuffer attachment.
        ///
        /// Valid only for `FrameBufferType::ColorDepth`.
        ///
        /// @return Depth renderbuffer identifier.
        unsigned int get_depth_renderbuffer() const;

        /// @brief Retrieves the depth texture attachment.
        ///
        /// Valid only for `FrameBufferType::Depth`.
        ///
        /// @return Depth texture identifier.
        unsigned int get_depth_texture() const;

        /// @brief Retrieves the depth cubemap texture attachment.
        ///
        /// @return Depth cubemap texture identifier.
        unsigned int get_depth_cube_texture() const;

        /// @brief Retrieves the framebuffer width.
        ///
        /// @return Width in pixels.
        int get_width() const;

        /// @brief Retrieves the framebuffer height.
        ///
        /// @return Height in pixels.
        int get_height() const;

        /// @brief Retrieves the framebuffer configuration.
        ///
        /// @return Framebuffer type.
        FrameBufferType get_frame_buffer_type() const;

    private:
        /// @brief Releases all framebuffer resources.
        void destroy();

        /// @brief Builds the framebuffer.
        ///
        /// @return `true` if framebuffer creation succeeded; otherwise, `false`.
        bool build();

        /// @brief Builds a framebuffer with color and depth attachments.
        ///
        /// @return `true` if creation succeeded; otherwise, `false`.
        bool build_color_depth();

        /// @brief Builds a depth-only framebuffer.
        ///
        /// @return `true` if creation succeeded; otherwise, `false`.
        bool build_depth();

        /// @brief Builds a depth cubemap framebuffer.
        ///
        /// @return `true` if creation succeeded; otherwise, `false`.
        bool build_depth_cube();

        /// @brief Checks whether the framebuffer is complete.
        ///
        /// @return `true` if the framebuffer is complete; otherwise, `false`.
        bool check_status() const;

    private:
        /// @brief OpenGL framebuffer object identifier.
        unsigned int m_fbo;

        /// @brief Color texture attachment identifier.
        unsigned int m_color_tex;

        /// @brief Depth renderbuffer attachment identifier.
        unsigned int m_depth_rbo;

        /// @brief Depth texture attachment identifier.
        unsigned int m_depth_tex;

        /// @brief Depth cubemap texture attachment identifier.
        unsigned int m_depth_cube_tex;

        /// @brief Framebuffer width in pixels.
        int m_width;

        /// @brief Framebuffer height in pixels.
        int m_height;

        /// @brief Framebuffer configuration.
        FrameBufferType m_type;
    };
}
