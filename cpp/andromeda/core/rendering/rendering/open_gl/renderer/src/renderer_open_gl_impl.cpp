#include "../include/renderer_open_gl_impl.hpp"
#include "../../support/include/shadow_renderer_open_gl.hpp"
#include "../../../utils/include/math_utils.hpp"
#include "../../../shaders/shaders/include/shader_open_gl.hpp"
#include "../../../shaders/support/include/shader_open_gl_types.hpp"
#include "andromeda/space/objects/i_light_object.hpp"
#include "andromeda/space/objects/i_surface_object.hpp"
#include "andromeda/space/materials/i_material.hpp"
#include "pch.hpp"

#include "glad/gl.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"
#include "spdlog/spdlog.h"


namespace andromeda::rendering
{
    RendererOpenGL::RendererOpenGLImpl::RendererOpenGLImpl()
        : m_is_initialized{ false }
        , m_directional_shadow_resolution{ 2048 }
        , m_shadow_cube_resolution{ 1024 }
        , m_shadow_map_light_space{ glm::mat4{ 1.0f } }
        , m_main_fbo{}
        , m_directional_shadow_fbo{}
        , m_point_shadow_fbo{}
        , m_p_shader_manager{ nullptr }
    {
        m_p_shader_manager = new ShaderManager(true);
        m_default_vertex_layout = VertexLayout(
            {
                { VertexSemantic::Position, ComponentType::Float32, 3, false, 0 },
                { VertexSemantic::Color0,   ComponentType::Float32, 4, true, sizeof(math::Vec3) },
                { VertexSemantic::Normal,   ComponentType::Float32, 3, true, sizeof(math::Vec3) + sizeof(math::Vec4) }
            }
        );
    }

    RendererOpenGL::RendererOpenGLImpl::~RendererOpenGLImpl()
    {
        de_init();
    }

    bool RendererOpenGL::RendererOpenGLImpl::is_initialized() const
    {
        return m_is_initialized;
    }

    void* RendererOpenGL::RendererOpenGLImpl::get_frame_texture_handle() const
    {
        return reinterpret_cast<void*>(static_cast<uintptr_t>(m_main_fbo.get_color_texture()));
    }

    void RendererOpenGL::RendererOpenGLImpl::init(int width, int height, bool illumination_mode)
    {
        if (width <= 0 || height <= 0)
        {
            spdlog::error("Invalid dimensions for initialization: {}x{}", width, height);
            return;
        }

        m_width = width;
        m_height = height;
        m_is_illumination_mode = illumination_mode;

        if (!m_main_fbo.init(width, height, FrameBufferType::ColorDepth))
        {
            spdlog::error("Failed to create main framebuffer");
            return;
        }

        if (m_is_illumination_mode)
        {
            if (!m_directional_shadow_fbo.init(
                m_directional_shadow_resolution,
                m_directional_shadow_resolution,
                FrameBufferType::Depth
            ))
            {
                spdlog::error("Failed to create shadow framebuffer");
                return;
            }
        }

        if (!m_point_shadow_fbo.init(
            m_shadow_cube_resolution,
            m_shadow_cube_resolution,
            FrameBufferType::DepthCube
        ))
        {
            spdlog::error("Failed to create point-light cubemap shadow framebuffer");
            return;
        }

        configure_point_shadow_depth_texture();
        m_text_renderer.init();

        m_is_initialized = true;
    }

    void RendererOpenGL::RendererOpenGLImpl::de_init()
    {
        m_mesh_cache.clear();

        delete m_p_shader_manager;
        m_p_shader_manager = nullptr;
        m_is_initialized = false;
    }

    void RendererOpenGL::RendererOpenGLImpl::resize(int width, int height)
    {
        SizeControl::resize(width, height);
        m_main_fbo.resize(width, height);
    }

    void RendererOpenGL::RendererOpenGLImpl::render_frame(IScene& scene)
    {
        if (!m_is_initialized)
            return;

        const ICamera* p_camera = scene.get_active_camera();
        if (!p_camera)
            return;

        m_mesh_cache.sync(scene.get_objects(), m_default_vertex_layout);

        set_background_color(MathUtils::to_glm(scene.get_background_color()));
        begin_frame();

        if (m_is_illumination_mode)
        {
            render_luminous_mode(scene, *p_camera);
        }
        else
        {
            render_objects(scene.get_objects(), scene.get_object_transforms(), *p_camera);
        }

        end_frame();
        log_fps();
    }

    void RendererOpenGL::RendererOpenGLImpl::render_non_luminous_objects_combined(
        const IScene& scene,
        const ICamera& r_camera,
        bool has_dir,
        bool has_point
    ) const
    {
        glViewport(0, 0, m_width, m_height);
        m_face_culling_control_open_gl.enable_face_culling(GL_BACK, GL_CCW);

        const int DIR_UNIT = 5;
        const int POINT_UNIT = 6;

        if (has_dir)
        {
            glActiveTexture(GL_TEXTURE0 + DIR_UNIT);
            glBindTexture(GL_TEXTURE_2D, m_directional_shadow_fbo.get_depth_texture());
        }

        if (has_point)
        {
            glActiveTexture(GL_TEXTURE0 + POINT_UNIT);
            glBindTexture(GL_TEXTURE_CUBE_MAP, m_point_shadow_fbo.get_depth_cube_texture());
        }

        ShaderOpenGL* shader =
            m_p_shader_manager->get_shader(ShaderOpenGLTypes::RenderableObjectsNonLuminous);

        shader->bind();

        shader->set_uniform(
            "u_view",
            MathUtils::to_glm(r_camera.get_view_matrix())
        );

        shader->set_uniform(
            "u_projection",
            glm::transpose(MathUtils::to_glm(r_camera.get_projection()))
        );

        shader->set_uniform(
            "u_cameraPosWS",
            MathUtils::to_glm(r_camera.get_position())
        );

        if (has_dir)
        {
            shader->set_uniform("u_dir_shadow_map", DIR_UNIT);
            shader->set_uniform("u_light_space_matrix", m_shadow_map_light_space);

            ShadowRendererOpenGL::populate_directional_light_uniforms(
                *shader,
                scene.get_directional_lights()
            );
        }

        if (has_point)
        {
            shader->set_uniform("u_point_shadow_cube", POINT_UNIT);

            ShadowRendererOpenGL::populate_point_light_uniforms(
                *shader,
                scene.get_point_lights()
            );
        }

        render_each_non_luminous_object(
            *shader,
            scene.get_objects(),
            scene.get_object_transforms()
        );

        shader->unbind();
        m_face_culling_control_open_gl.disable_face_culling();
    }

    void RendererOpenGL::RendererOpenGLImpl::render_luminous_objects(
        const std::unordered_map<int, IGeometricObject*>& objects,
        const std::unordered_map<int, ITransformable*>& object_transforms,
        const ICamera& r_camera
    ) const
    {
        ShaderOpenGL* lum_shader =
            m_p_shader_manager->get_shader(ShaderOpenGLTypes::RenderableObjectsLuminous);

        lum_shader->bind();

        lum_shader->set_uniform(
            "u_view",
            MathUtils::to_glm(r_camera.get_view_matrix())
        );

        lum_shader->set_uniform(
            "u_projection",
            MathUtils::to_glm(r_camera.get_projection())
        );

        for (const auto& [id, obj] : objects)
        {
            if (!obj)
            {
                continue;
            }

            if (!dynamic_cast<ILightObject*>(obj))
            {
                continue;
            }

            std::unordered_map<int, ITransformable*>::const_iterator transform_it =
                object_transforms.find(id);

            if (transform_it == object_transforms.end() || !transform_it->second)
            {
                continue;
            }

            const int obj_id = obj->get_id();
            const GpuMeshOpenGL* mesh = m_mesh_cache.try_get(obj_id);

            if (!mesh)
            {
                continue;
            }

            lum_shader->set_uniform(
                "u_model",
                MathUtils::to_glm(transform_it->second->get_model_matrix())
            );

            glBindVertexArray(mesh->get_vao());

            glDrawElements(
                GL_TRIANGLES,
                static_cast<GLsizei>(mesh->get_index_count()),
                GL_UNSIGNED_INT,
                nullptr
            );
        }

        lum_shader->unbind();
        m_face_culling_control_open_gl.disable_face_culling();
    }

    void RendererOpenGL::RendererOpenGLImpl::render_objects(
        const std::unordered_map<int, IGeometricObject*>& objects,
        const std::unordered_map<int, ITransformable*>& object_transforms,
        const ICamera& r_camera
    ) const
    {
        m_face_culling_control_open_gl.enable_face_culling(GL_BACK, GL_CCW);

        ShaderOpenGL* shader =
            m_p_shader_manager->get_shader(ShaderOpenGLTypes::RenderableObjects);

        shader->bind();

        shader->set_uniform(
            "u_view",
            MathUtils::to_glm(r_camera.get_view_matrix())
        );

        shader->set_uniform(
            "u_projection",
            glm::transpose(MathUtils::to_glm(r_camera.get_projection()))
        );

        for (const auto& [id, obj] : objects)
        {
            if (!obj)
                continue;

            if (id < 0)
                continue;

            std::unordered_map<int, ITransformable*>::const_iterator transform_it =
                object_transforms.find(id);

            if (transform_it == object_transforms.end() || !transform_it->second)
            {
                continue;
            }

            int obj_id = obj->get_id();
            const GpuMeshOpenGL* mesh = m_mesh_cache.try_get(obj_id);

            if (!mesh)
                continue;

            const math::Mat4& model_matrix =
                transform_it->second->get_model_matrix();

            shader->set_uniform(
                "u_model",
                MathUtils::to_glm(model_matrix)
            );

            glBindVertexArray(mesh->get_vao());

            glDrawElements(
                GL_TRIANGLES,
                static_cast<GLsizei>(mesh->get_index_count()),
                GL_UNSIGNED_INT,
                nullptr
            );
        }

        shader->unbind();
        m_face_culling_control_open_gl.disable_face_culling();
    }

    void RendererOpenGL::RendererOpenGLImpl::render_grid(const GpuMeshOpenGL& mesh) const
    {
        //if (m_width == 0 || m_height == 0)
        //{
        //    spdlog::error("Framebuffer dimensions are zero. Cannot render grid.");
        //    return;
        //}

        //ShaderOpenGL* shader = m_p_shader_manager->get_shader(ShaderOpenGLTypes::Grid);
        //shader->bind();

        //shader->set_uniform("u_view", MathUtils::to_glm(m_p_camera->get_view_matrix()));
        //shader->set_uniform("u_projection", MathUtils::to_glm(m_p_camera->get_projection()));

        //glBindVertexArray(mesh.get_vao());
        //glDrawElements(GL_LINES, static_cast<GLsizei>(mesh.get_index_count()), GL_UNSIGNED_INT, nullptr);

        //shader->unbind();
    }

    void RendererOpenGL::RendererOpenGLImpl::begin_frame() const
    {
        m_main_fbo.bind();
        glViewport(0, 0, m_width, m_height);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RendererOpenGL::RendererOpenGLImpl::end_frame() const
    {
        // Blit FBO color to default framebuffer
        glBindFramebuffer(GL_READ_FRAMEBUFFER, m_main_fbo.get_id());
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

        glBlitFramebuffer(
            0, 0, m_width, m_height,          // src rect
            0, 0, m_width, m_height,          // dst rect
            GL_COLOR_BUFFER_BIT,
            GL_NEAREST
        );

        // If you also want to blit depth (for further drawing on default):
        // glBlitFramebuffer(0, 0, m_width, m_height,
        //                   0, 0, m_width, m_height,
        //                   GL_DEPTH_BUFFER_BIT, GL_NEAREST);

        // Return to default framebuffer bound
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void RendererOpenGL::RendererOpenGLImpl::log_fps()
    {
        // update FPS counter
        m_fps_counter.frame_tick();
        float fps = m_fps_counter.get_smoothed_fps();

        ShaderOpenGL* text_shader = m_p_shader_manager->get_shader(ShaderOpenGLTypes::Text);
        if (!text_shader)
        {
            spdlog::error("Text shader is null (ShaderOpenGLTypes::Text).");
            return;
        }

        if (!m_text_renderer.is_valid())
        {
            spdlog::error("TextRendererOpenGL is not valid (VAO/VBO not created).");
            return;
        }

        // Draw directly to default framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, m_width, m_height);

        text_shader->bind();

        // Y-down orthographic projection to match stb_easy_font coordinates
        glm::mat4 proj = glm::ortho(
            0.0f,
            static_cast<float>(m_width),
            static_cast<float>(m_height),
            0.0f
        );

        text_shader->set_uniform("u_projection", proj);
        text_shader->set_uniform("u_color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)); // white

        GLboolean depth_was_enabled = glIsEnabled(GL_DEPTH_TEST);
        GLboolean cull_was_enabled = glIsEnabled(GL_CULL_FACE);

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);

        // Compose FPS text
        const std::string fps_text = "FPS: " + std::to_string(static_cast<int>(fps));

        // Top-left-ish corner, in pixels
        m_text_renderer.render_text(fps_text, 10.0f, 20.0f, 2.0f);

        if (depth_was_enabled)
        {
            glEnable(GL_DEPTH_TEST);
        }
        if (cull_was_enabled)
        {
            glEnable(GL_CULL_FACE);
        }

        text_shader->unbind();

        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
            spdlog::error("OpenGL error after RenderText: {}", err);
        }
    }

    void RendererOpenGL::RendererOpenGLImpl::prepare_framebuffer_for_non_luminous_pass() const
    {
        m_main_fbo.bind();
        glViewport(0, 0, m_width, m_height);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RendererOpenGL::RendererOpenGLImpl::bind_shadow_map(int texture_unit) const
    {
        glActiveTexture(GL_TEXTURE0 + texture_unit);
        glBindTexture(GL_TEXTURE_2D, m_directional_shadow_fbo.get_depth_texture());
    }

    void RendererOpenGL::RendererOpenGLImpl::render_grid_if_visible(const IScene& scene) const
    {
        if (!m_is_grid_visible)
        {
            return;
        }

        // If you use a special ID for grid, fetch it from scene and then draw its cached GPU mesh.
        // Example assumes the grid object exists in scene objects and its ID is returned by obj->get_id().
        //
        // If your grid is keyed by SpecialIndices::Grid in the map key, uncomment SpecialIndices include
        // and use that to find the object, then use its get_id() to lookup m_gpu_meshes.

        //std::unordered_map<int, IGeometricObject*>::const_iterator it_obj =
        //    scene.get_objects().find(static_cast<int>(SpecialIndices::Grid));
        //if (it_obj == scene.get_objects().end() || !it_obj->second)
        //{
        //    return;
        //}
        //const int grid_id = it_obj->second->get_id();
        //const GpuMeshOpenGL* mesh = try_get_gpu_mesh(grid_id);

        // Minimal generic approach: first object with negative key is treated as grid
        const std::unordered_map<int, IGeometricObject*>& objects = scene.get_objects();
        for (const auto& [id, obj] : objects)
        {
            if (id >= 0)
            {
                continue;
            }

            if (!obj)
            {
                continue;
            }

            const int grid_id = obj->get_id();
            const GpuMeshOpenGL* mesh = m_mesh_cache.try_get(grid_id);
            if (!mesh)
            {
                return;
            }

            render_grid(*mesh);
            return;
        }
    }

    void RendererOpenGL::RendererOpenGLImpl::render_each_non_luminous_object(
        ShaderOpenGL& shader,
        const std::unordered_map<int, IGeometricObject*>& objects,
        const std::unordered_map<int, ITransformable*>& object_transforms
    ) const
    {
        for (const auto& [id, obj] : objects)
        {
            if (!obj)
            {
                continue;
            }

            if (id < 0 || dynamic_cast<ILightObject*>(obj))
            {
                continue;
            }

            ISurfaceObject* surface_obj = dynamic_cast<ISurfaceObject*>(obj);

            if (surface_obj != nullptr)
            {
                std::unordered_map<int, ITransformable*>::const_iterator transform_it =
                    object_transforms.find(id);
                if (transform_it == object_transforms.end() || !transform_it->second)
                {
                    continue;
                }

                const IMaterial* material = surface_obj->get_material();
                glm::mat3 normal_matrix = glm::inverseTranspose(
                    MathUtils::to_glm(transform_it->second->get_model_matrix())
                );

                shader.set_uniform("u_material_ambient", MathUtils::to_glm(material->get_ambient()));
                shader.set_uniform("u_material_diffuse", MathUtils::to_glm(material->get_diffuse()));
                shader.set_uniform("u_material_specular", MathUtils::to_glm(material->get_specular()));
                shader.set_uniform("u_material_shininess", material->get_shininess());

                shader.set_uniform("u_model", MathUtils::to_glm(transform_it->second->get_model_matrix()));
                shader.set_uniform("u_normal_matrix", normal_matrix);

                const int obj_id = obj->get_id();
                const GpuMeshOpenGL* mesh = m_mesh_cache.try_get(obj_id);
                if (!mesh)
                {
                    continue;
                }

                glBindVertexArray(mesh->get_vao());
                glDrawElements(
                    GL_TRIANGLES,
                    static_cast<GLsizei>(mesh->get_index_count()),
                    GL_UNSIGNED_INT,
                    nullptr
                );
            }
        }
    }

    void RendererOpenGL::RendererOpenGLImpl::configure_point_shadow_depth_texture()
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_point_shadow_fbo.get_depth_cube_texture());

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_MODE, GL_NONE);

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void RendererOpenGL::RendererOpenGLImpl::render_luminous_mode(
        const IScene& scene,
        const ICamera& r_camera
    )
    {
        const std::unordered_map<int, const IDirectionalLight*>& dir_lights =
            scene.get_directional_lights();
        const bool has_dir = !dir_lights.empty();

        const std::unordered_map<int, const IPointLight*>& point_lights =
            scene.get_point_lights();
        const bool has_point = !point_lights.empty();


        if (has_dir)
        {
            m_shadow_map_light_space = ShadowRendererOpenGL::compute_light_space_matrix(
                scene.get_directional_lights(),
                scene.get_scene_center()
            );

            ShadowRendererOpenGL::render_directional_shadow_map(
                scene.get_objects(),
                scene.get_object_transforms(),
                m_directional_shadow_fbo,
                m_directional_shadow_resolution,
                m_shadow_map_light_space,
                *m_p_shader_manager,
                m_mesh_cache,
                m_face_culling_control_open_gl
            );
        }

        if (has_point)
        {
            const IPointLight* pl = point_lights.begin()->second;
            const glm::vec3 light_pos = MathUtils::to_glm(pl->get_position());
            const float near_plane = pl->get_shadow_near_plane();
            const float far_plane = pl->get_shadow_far_plane();

            ShadowRendererOpenGL::render_point_shadow_cube(
                scene.get_objects(),
                scene.get_object_transforms(),
                m_point_shadow_fbo,
                m_shadow_cube_resolution,
                light_pos,
                near_plane,
                far_plane,
                *m_p_shader_manager,
                m_mesh_cache,
                m_face_culling_control_open_gl
            );
        }

        render_non_luminous_objects_combined(scene, r_camera, has_dir, has_point);
        render_luminous_objects(scene.get_objects(), scene.get_object_transforms(), r_camera);

        render_grid_if_visible(scene);
    }

    void RendererOpenGL::RendererOpenGLImpl::set_background_color(
        const glm::vec4& background_color
    )
    {
        glClearColor(
            background_color.r,
            background_color.g,
            background_color.b,
            background_color.a
        );
    }
}