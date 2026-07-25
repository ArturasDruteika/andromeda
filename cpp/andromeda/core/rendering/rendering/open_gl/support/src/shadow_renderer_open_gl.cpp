#include "../include/shadow_renderer_open_gl.hpp"
#include "../../../shaders/shaders/include/shader_open_gl.hpp"
#include "../../../shaders/support/include/shader_open_gl_types.hpp"
#include "../../../utils/include/math_utils.hpp"
#include "andromeda/space/objects/i_light_object.hpp"

#include "glad/gl.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"


namespace andromeda::rendering
{
    void ShadowRendererOpenGL::render_directional_shadow_map(
        const std::unordered_map<int, IGeometricObject*>& objects,
        const std::unordered_map<int, ITransformable*>& object_transforms,
        FrameBufferOpenGL& shadow_fbo,
        int resolution,
        const glm::mat4& light_space_matrix,
        ShaderManager& shader_manager,
        MeshCacheOpenGL& mesh_cache,
        FaceCullingControlOpenGL& culling
    )
    {
        culling.enable_face_culling(GL_FRONT, GL_CCW);

        int prev_fbo;
        glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &prev_fbo);

        shadow_fbo.bind();
        glViewport(0, 0, resolution, resolution);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);

        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(2.0f, 4.0f);

        ShaderOpenGL* depth_shader = shader_manager.get_shader(ShaderOpenGLTypes::ShadowMap);
        depth_shader->bind();
        depth_shader->set_uniform("u_light_space_matrix", light_space_matrix);

        for (const auto& [id, obj] : objects)
        {
            if (!obj)
            {
                continue;
            }

            std::unordered_map<int, ITransformable*>::const_iterator transform_it =
                object_transforms.find(id);
            if (transform_it == object_transforms.end() || !transform_it->second)
            {
                continue;
            }

            const GpuMeshOpenGL* mesh = mesh_cache.try_get(obj->get_id());
            if (!mesh)
            {
                continue;
            }

            depth_shader->set_uniform(
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

        depth_shader->unbind();

        glBindFramebuffer(GL_FRAMEBUFFER, prev_fbo);
        glDisable(GL_POLYGON_OFFSET_FILL);
        culling.disable_face_culling();
    }

    void ShadowRendererOpenGL::render_point_shadow_cube(
        const std::unordered_map<int, IGeometricObject*>& objects,
        const std::unordered_map<int, ITransformable*>& object_transforms,
        FrameBufferOpenGL& point_shadow_fbo,
        int resolution,
        const glm::vec3& light_pos,
        float near_plane,
        float far_plane,
        ShaderManager& shader_manager,
        MeshCacheOpenGL& mesh_cache,
        FaceCullingControlOpenGL& culling
    )
    {
        culling.enable_face_culling(GL_FRONT, GL_CCW);

        int prev_fbo;
        glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &prev_fbo);

        point_shadow_fbo.bind();
        glViewport(0, 0, resolution, resolution);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);

        ShaderOpenGL* shader = shader_manager.get_shader(ShaderOpenGLTypes::PointShadowCubeMap);
        shader->bind();

        const glm::mat4 proj = glm::perspective(glm::radians(90.0f), 1.0f, near_plane, far_plane);

        std::vector<glm::vec3> ups{
            {0, -1, 0},
            {0, -1, 0},
            {0,  0, 1},
            {0,  0,-1},
            {0, -1, 0},
            {0, -1, 0}
        };

        std::vector<glm::vec3> targets{
            light_pos + glm::vec3(1, 0, 0),
            light_pos + glm::vec3(-1, 0, 0),
            light_pos + glm::vec3(0, 1, 0),
            light_pos + glm::vec3(0,-1, 0),
            light_pos + glm::vec3(0, 0, 1),
            light_pos + glm::vec3(0, 0,-1)
        };

        std::vector<glm::mat4> matrices(6);
        for (std::size_t i = 0; i < matrices.size(); ++i)
        {
            matrices[i] = proj * glm::lookAt(light_pos, targets[i], ups[i]);
        }

        shader->set_uniform("u_shadow_matrices[0]", matrices);
        shader->set_uniform("u_light_pos", light_pos);
        shader->set_uniform("u_far_plane", far_plane);

        for (const auto& [id, obj] : objects)
        {
            if (!obj)
            {
                continue;
            }

            if (dynamic_cast<const ILightObject*>(obj))
            {
                continue;
            }

            std::unordered_map<int, ITransformable*>::const_iterator transform_it =
                object_transforms.find(id);
            if (transform_it == object_transforms.end() || !transform_it->second)
            {
                continue;
            }

            const GpuMeshOpenGL* mesh = mesh_cache.try_get(obj->get_id());
            if (!mesh)
            {
                continue;
            }

            shader->set_uniform(
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

        shader->unbind();
        glBindFramebuffer(GL_FRAMEBUFFER, prev_fbo);
        culling.disable_face_culling();
    }

    glm::mat4 ShadowRendererOpenGL::compute_light_space_matrix(
        const std::unordered_map<int, const IDirectionalLight*>& directional_lights,
        const math::Vec3& scene_center
    )
    {
        const IDirectionalLight* light = directional_lights.begin()->second;

        glm::vec3 direction = MathUtils::to_glm(light->get_direction());
        glm::vec3 up(0.0f, 1.0f, 0.0f);

        glm::vec3 light_pos = MathUtils::to_glm(scene_center) - direction * 20.0f;

        glm::mat4 view = glm::lookAt(light_pos, MathUtils::to_glm(scene_center), up);

        glm::mat4 proj = glm::ortho(
            -light->get_light_orthographic_half_size(),
            light->get_light_orthographic_half_size(),
            -light->get_light_orthographic_half_size(),
            light->get_light_orthographic_half_size(),
            light->get_light_near_plane(),
            light->get_light_far_plane()
        );

        return proj * view;
    }

    void ShadowRendererOpenGL::populate_directional_light_uniforms(
        ShaderOpenGL& shader,
        const std::unordered_map<int, const IDirectionalLight*>& directional_lights
    )
    {
        std::vector<glm::vec3> directions;
        std::vector<glm::vec3> ambient;
        std::vector<glm::vec3> diffuse;
        std::vector<glm::vec3> specular;

        for (const auto& [id, light] : directional_lights)
        {
            directions.push_back(MathUtils::to_glm(light->get_direction()));
            ambient.push_back(glm::vec3(0.9f));
            diffuse.push_back(MathUtils::to_glm(light->get_diffuse()));
            specular.push_back(MathUtils::to_glm(light->get_specular()));
        }

        shader.set_uniform("u_num_dir_lights", static_cast<int>(directions.size()));
        shader.set_uniform("u_dir_light_directions", directions);
        shader.set_uniform("u_dir_light_ambient", ambient);
        shader.set_uniform("u_dir_light_diffuse", diffuse);
        shader.set_uniform("u_dir_light_specular", specular);
    }

    void ShadowRendererOpenGL::populate_point_light_uniforms(
        ShaderOpenGL& shader,
        const std::unordered_map<int, const IPointLight*>& point_lights
    )
    {
        std::vector<glm::vec3> positions, ambient, diffuse, specular;
        std::vector<float> intensity, constant, linear, quadratic, far_plane;

        for (const auto& [id, point_light] : point_lights)
        {
            positions.push_back(MathUtils::to_glm(point_light->get_position()));
            ambient.push_back(MathUtils::to_glm(point_light->get_ambient()));
            diffuse.push_back(MathUtils::to_glm(point_light->get_diffuse()));
            specular.push_back(MathUtils::to_glm(point_light->get_specular()));

            intensity.push_back(point_light->get_intensity());
            constant.push_back(point_light->get_attenuation_constant());
            linear.push_back(point_light->get_attenuation_linear());
            quadratic.push_back(point_light->get_attenuation_quadratic());
            far_plane.push_back(point_light->get_shadow_far_plane());
        }

        shader.set_uniform("u_num_point_lights", static_cast<int>(positions.size()));
        shader.set_uniform("u_point_light_positions", positions);
        shader.set_uniform("u_point_light_ambient", ambient);
        shader.set_uniform("u_point_light_diffuse", diffuse);
        shader.set_uniform("u_point_light_specular", specular);
        shader.set_uniform("u_point_light_intensity", intensity);
        shader.set_uniform("u_point_light_constant", constant);
        shader.set_uniform("u_point_light_linear", linear);
        shader.set_uniform("u_point_light_quadratic", quadratic);
        shader.set_uniform("u_point_light_far_planes", far_plane);
    }
}