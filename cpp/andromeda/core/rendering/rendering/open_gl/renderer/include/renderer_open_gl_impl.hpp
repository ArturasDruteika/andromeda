#ifndef RENDERER__OPENGL_RENDERER_IMPL__HPP
#define RENDERER__OPENGL_RENDERER_IMPL__HPP


#include "../../geometry/include/gpu_mesh_open_gl.hpp"
#include "../../support/include/face_culling_control_open_gl.hpp"
#include "../../support/include/frame_buffer_open_gl.hpp"
#include "../../support/include/fps_counter.hpp"
#include "../../support/include/mesh_cache_open_gl.hpp"
#include "../../support/include/text_renderer_open_gl.hpp"
#include "../../../renderers/renderers/include/renderer_open_gl.hpp"
#include "../../../renderers/abstracts/include/grid_control.hpp"
#include "../../../renderers/abstracts/include/illumination_control.hpp"
#include "../../../renderers/abstracts/include/size_control.hpp"
#include "../../../shaders/shaders/include/shader_manager.hpp"
#include "../../../vertices/include/vertex_layouts.hpp"
#include "andromeda/space/transformations/i_transformable.hpp"
#include "pch.hpp"


namespace andromeda::rendering
{
    /// @brief Implements the internal OpenGL renderer functionality.
    ///
    /// Manages frame rendering, framebuffer resources, shadow maps, mesh
    /// caching, shaders, text rendering, face culling, and renderer controls.
    class RendererOpenGL::RendererOpenGLImpl
        : public GridControl
        , public IlluminationControl
        , public SizeControl
    {
    public:
        /// @brief Constructs an uninitialized OpenGL renderer implementation.
        RendererOpenGLImpl();

        /// @brief Destroys the renderer implementation.
        ~RendererOpenGLImpl();

        RendererOpenGLImpl(const RendererOpenGLImpl& other) = delete;
        RendererOpenGLImpl& operator=(const RendererOpenGLImpl& other) = delete;
        RendererOpenGLImpl(RendererOpenGLImpl&& other) noexcept = delete;
        RendererOpenGLImpl& operator=(RendererOpenGLImpl&& other) noexcept = delete;

        // Getters

        /// @brief Checks whether the renderer has been initialized.
        ///
        /// @return `true` if the renderer is initialized; otherwise, `false`.
        bool is_initialized() const;

        /// @brief Retrieves the rendered frame texture handle.
        ///
        /// @return Backend-specific handle to the frame texture.
        void* get_frame_texture_handle() const;

        /// @brief Initializes the renderer.
        ///
        /// @param width Initial render target width in pixels.
        /// @param height Initial render target height in pixels.
        /// @param illumination_mode Initial illumination mode.
        void init(int width, int height, bool illumination_mode = false);

        /// @brief Deinitializes the renderer and releases its resources.
        void de_init();

        /// @brief Renders a frame for the specified scene.
        ///
        /// @param scene Scene to render.
        void render_frame(IScene& scene);

        /// @brief Resizes the renderer output.
        ///
        /// @param width New render target width in pixels.
        /// @param height New render target height in pixels.
        void resize(int width, int height);

    private:
        /// @brief Renders all non-luminous objects using the combined lighting pass.
        ///
        /// @param scene Scene containing the objects and lights.
        /// @param r_camera Active camera.
        /// @param has_dir Indicates whether the scene contains directional lights.
        /// @param has_point Indicates whether the scene contains point lights.
        void render_non_luminous_objects_combined(
            const IScene& scene,
            const ICamera& r_camera,
            bool has_dir,
            bool has_point
        ) const;

        /// @brief Renders luminous objects.
        ///
        /// @param objects Scene objects indexed by object ID.
        /// @param object_transforms Object transforms indexed by object ID.
        /// @param r_camera Active camera.
        void render_luminous_objects(
            const std::unordered_map<int, IGeometricObject*>& objects,
            const std::unordered_map<int, ITransformable*>& object_transforms,
            const ICamera& r_camera
        ) const;

        /// @brief Renders scene objects.
        ///
        /// @param objects Scene objects indexed by object ID.
        /// @param object_transforms Object transforms indexed by object ID.
        /// @param r_camera Active camera.
        void render_objects(
            const std::unordered_map<int, IGeometricObject*>& objects,
            const std::unordered_map<int, ITransformable*>& object_transforms,
            const ICamera& r_camera
        ) const;

        /// @brief Renders the scene grid.
        ///
        /// @param mesh GPU mesh containing the grid geometry.
        void render_grid(const GpuMeshOpenGL& mesh) const;

        /// @brief Begins rendering a new frame.
        void begin_frame() const;

        /// @brief Completes rendering of the current frame.
        void end_frame() const;

        /// @brief Updates and logs the current frame rate.
        void log_fps();

        /// @brief Prepares the main framebuffer for the non-luminous rendering pass.
        void prepare_framebuffer_for_non_luminous_pass() const;

        /// @brief Binds the shadow map to a texture unit.
        ///
        /// @param texture_unit Texture unit to bind.
        void bind_shadow_map(int texture_unit) const;

        /// @brief Renders the grid when grid visibility is enabled.
        ///
        /// @param scene Scene containing the grid.
        void render_grid_if_visible(const IScene& scene) const;

        /// @brief Renders each non-luminous object using the specified shader.
        ///
        /// @param shader Shader used for rendering.
        /// @param objects Scene objects indexed by object ID.
        /// @param object_transforms Object transforms indexed by object ID.
        void render_each_non_luminous_object(
            ShaderOpenGL& shader,
            const std::unordered_map<int, IGeometricObject*>& objects,
            const std::unordered_map<int, ITransformable*>& object_transforms
        ) const;

        /// @brief Configures the point-light shadow depth texture.
        void configure_point_shadow_depth_texture();

        /// @brief Renders the scene using luminous rendering mode.
        ///
        /// @param scene Scene to render.
        /// @param r_camera Active camera.
        void render_luminous_mode(const IScene& scene, const ICamera& r_camera);

        /// @brief Sets the renderer background color.
        ///
        /// @param background_color RGBA background color.
        void set_background_color(const glm::vec4& background_color);

    private:
        /// @brief Indicates whether the renderer has been initialized.
        bool m_is_initialized;

        /// @brief Resolution of the directional-light shadow map.
        int m_directional_shadow_resolution;

        /// @brief Resolution of the point-light shadow cube map.
        int m_shadow_cube_resolution;

        /// @brief Directional-light shadow-space transformation matrix.
        glm::mat4 m_shadow_map_light_space;

        /// @brief Main rendering framebuffer.
        FrameBufferOpenGL m_main_fbo;

        /// @brief Directional-light shadow framebuffer.
        FrameBufferOpenGL m_directional_shadow_fbo;

        /// @brief Point-light shadow framebuffer.
        FrameBufferOpenGL m_point_shadow_fbo;

        /// @brief OpenGL face-culling controller.
        FaceCullingControlOpenGL m_face_culling_control_open_gl;

        /// @brief Cache of GPU mesh resources.
        MeshCacheOpenGL m_mesh_cache;

        /// @brief Shader manager used by the renderer.
        ShaderManager* m_p_shader_manager;

        /// @brief Default vertex layout used by rendered meshes.
        VertexLayout m_default_vertex_layout;

        /// @brief OpenGL text renderer.
        TextRendererOpenGL m_text_renderer;

        /// @brief Frame-rate counter.
        FpsCounter m_fps_counter;

        /// @brief Time point recorded for the previous rendered frame.
        mutable std::chrono::steady_clock::time_point m_last_frame_time = std::chrono::steady_clock::now();
    };
}


#endif // RENDERER__OPENGL_RENDERER_IMPL__HPP