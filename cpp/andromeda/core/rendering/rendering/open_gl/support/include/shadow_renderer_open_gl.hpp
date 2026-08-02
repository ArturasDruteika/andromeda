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
    /// @brief Provides OpenGL shadow rendering utility functions.
    ///
    /// Contains static operations for rendering directional and point-light
    /// shadow maps, computing light-space transforms, and populating light
    /// shader uniforms.
    class ShadowRendererOpenGL
    {
    public:
        /// @brief Renders a directional-light shadow map.
        ///
        /// @param objects Geometric objects indexed by object ID.
        /// @param object_transforms Object transforms indexed by object ID.
        /// @param shadow_fbo Framebuffer used for the directional shadow map.
        /// @param resolution Shadow-map resolution in pixels.
        /// @param light_space_matrix Light-space transformation matrix.
        /// @param shader_manager Shader manager used for rendering.
        /// @param mesh_cache Cache containing GPU mesh resources.
        /// @param culling Face-culling controller.
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

        /// @brief Renders a point-light shadow cubemap.
        ///
        /// @param objects Geometric objects indexed by object ID.
        /// @param object_transforms Object transforms indexed by object ID.
        /// @param point_shadow_fbo Framebuffer used for the point-light shadow map.
        /// @param resolution Shadow cubemap resolution in pixels.
        /// @param light_pos Point-light position in world space.
        /// @param near_plane Near clipping plane.
        /// @param far_plane Far clipping plane.
        /// @param shader_manager Shader manager used for rendering.
        /// @param mesh_cache Cache containing GPU mesh resources.
        /// @param culling Face-culling controller.
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

        /// @brief Computes the directional-light space transformation matrix.
        ///
        /// @param directional_lights Directional lights indexed by object ID.
        /// @param scene_center Center of the scene in world space.
        /// @return Light-space transformation matrix.
        static glm::mat4 compute_light_space_matrix(
            const std::unordered_map<int, const IDirectionalLight*>& directional_lights,
            const math::Vec3& scene_center
        );

        /// @brief Populates directional-light shader uniforms.
        ///
        /// @param shader Shader whose uniforms will be updated.
        /// @param directional_lights Directional lights indexed by object ID.
        static void populate_directional_light_uniforms(
            ShaderOpenGL& shader,
            const std::unordered_map<int, const IDirectionalLight*>& directional_lights
        );

        /// @brief Populates point-light shader uniforms.
        ///
        /// @param shader Shader whose uniforms will be updated.
        /// @param point_lights Point lights indexed by object ID.
        static void populate_point_light_uniforms(
            ShaderOpenGL& shader,
            const std::unordered_map<int, const IPointLight*>& point_lights
        );
    };
}


#endif // RENDERING__OPENGL__SUPPORT__SHADOW_RENDERER_OPEN_GL__HPP