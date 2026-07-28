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
    class RendererOpenGL::RendererOpenGLImpl
        : public GridControl
        , public IlluminationControl
        , public SizeControl
    {
    public:
        RendererOpenGLImpl();
        ~RendererOpenGLImpl();

        RendererOpenGLImpl(const RendererOpenGLImpl& other) = delete;
        RendererOpenGLImpl& operator=(const RendererOpenGLImpl& other) = delete;
        RendererOpenGLImpl(RendererOpenGLImpl&& other) noexcept = delete;
        RendererOpenGLImpl& operator=(RendererOpenGLImpl&& other) noexcept = delete;

        // Getters
        bool is_initialized() const;
        void* get_frame_texture_handle() const;

        void init(int width, int height, bool illumination_mode = false);
        void de_init();
        void render_frame(IScene& scene);
        void resize(int width, int height);

    private:
        void render_non_luminous_objects_combined(
            const IScene& scene,
            const ICamera& r_camera,
            bool has_dir,
            bool has_point
        ) const;

        void render_luminous_objects(
            const std::unordered_map<int, IGeometricObject*>& objects,
            const std::unordered_map<int, ITransformable*>& object_transforms,
            const ICamera& r_camera
        ) const;

        void render_objects(
            const std::unordered_map<int, IGeometricObject*>& objects,
            const std::unordered_map<int, ITransformable*>& object_transforms,
            const ICamera& r_camera
        ) const;

        void render_grid(const GpuMeshOpenGL& mesh) const;
        void begin_frame() const;
        void end_frame() const;
        void log_fps();
        void prepare_framebuffer_for_non_luminous_pass() const;
        void bind_shadow_map(int texture_unit) const;
        void render_grid_if_visible(const IScene& scene) const;

        void render_each_non_luminous_object(
            ShaderOpenGL& shader,
            const std::unordered_map<int, IGeometricObject*>& objects,
            const std::unordered_map<int, ITransformable*>& object_transforms
        ) const;

        void configure_point_shadow_depth_texture();
        void render_luminous_mode(const IScene& scene, const ICamera& r_camera);
        void set_background_color(const glm::vec4& background_color);

    private:
        bool m_is_initialized;
        int m_directional_shadow_resolution;
        int m_shadow_cube_resolution;
        glm::mat4 m_shadow_map_light_space;
        FrameBufferOpenGL m_main_fbo;
        FrameBufferOpenGL m_directional_shadow_fbo;
        FrameBufferOpenGL m_point_shadow_fbo;
        FaceCullingControlOpenGL m_face_culling_control_open_gl;
        MeshCacheOpenGL m_mesh_cache;
        ShaderManager* m_p_shader_manager;
        VertexLayout m_default_vertex_layout;
        TextRendererOpenGL m_text_renderer;
        FpsCounter m_fps_counter;
        mutable std::chrono::steady_clock::time_point m_last_frame_time = std::chrono::steady_clock::now();
    };
}


#endif // RENDERER__OPENGL_RENDERER_IMPL__HPP