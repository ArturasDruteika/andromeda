#ifndef RENDERING__OPENGL__SUPPORT__SHADOW_RENDERER_OPEN_GL__HPP
#define RENDERING__OPENGL__SUPPORT__SHADOW_RENDERER_OPEN_GL__HPP


#include "frame_buffer_open_gl.hpp"
#include "face_culling_control_open_gl.hpp"
#include "../../../shaders/shaders/include/shader_manager.hpp"
#include "../../support/include/mesh_cache_open_gl.hpp"
#include "andromeda/space/light/i_directional_light.hpp"
#include "andromeda/space/light/i_point_light.hpp"
#include "andromeda/space/objects/i_geometric_object.hpp"
#include "andromeda/space/transformations/i_transformable.hpp"
#include "pch.hpp"


namespace andromeda::rendering
{
    class ShadowRendererOpenGL
    {
    public:
        static void render_directional_shadow_map(
            const std::unordered_map<int, IGeometricObject*>& objects,
            const std::unordered_map<int, ITransformable*>& object_transforms,
            FrameBufferOpenGL& shadow_fbo,
            int resolution,
            const glm::mat4& light_space_matrix,
            ShaderManager& shader_manager,
            MeshCacheOpenGL& mesh_cache,
            FaceCullingControlOpenGL& culling
        );

        static void render_point_shadow_cube(
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
        );

        // TODO: consider making it void and calculating only when the scene state has changed.
        static glm::mat4 compute_light_space_matrix(
            const std::unordered_map<int, const IDirectionalLight*>& directional_lights,
            const math::Vec3& scene_center
        );

        static void populate_directional_light_uniforms(
            ShaderOpenGL& shader,
            const std::unordered_map<int, const IDirectionalLight*>& directional_lights
        );

        static void populate_point_light_uniforms(
            ShaderOpenGL& shader,
            const std::unordered_map<int, const IPointLight*>& point_lights
        );
    };
}


#endif // RENDERING__OPENGL__SUPPORT__SHADOW_RENDERER_OPEN_GL__HPP