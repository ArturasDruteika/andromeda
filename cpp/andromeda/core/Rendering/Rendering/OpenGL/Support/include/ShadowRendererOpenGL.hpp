#ifndef RENDERING__OPENGL__SUPPORT__SHADOW_RENDERER_OPENGL__HPP
#define RENDERING__OPENGL__SUPPORT__SHADOW_RENDERER_OPENGL__HPP


#include "FrameBufferOpenGL.hpp"
#include "FaceCullingControlOpenGL.hpp"
#include "../../../Shaders/Shaders/include/ShaderManager.hpp"
#include "../../Support/include/MeshCacheOpenGL.hpp"
#include "andromeda/space/light/i_directional_light.hpp"
#include "andromeda/space/light/i_point_light.hpp"
#include "andromeda/space/objects/i_geometric_object.hpp"
#include "andromeda/space/transformations/i_transformable.hpp"
#include "pch.hpp"


namespace andromeda::Rendering
{
    class ShadowRendererOpenGL
    {
    public:
        static void RenderDirectionalShadowMap(
            const std::unordered_map<int, IGeometricObject*>& objects,
            const std::unordered_map<int, ITransformable*>& objectTransforms,
            FrameBufferOpenGL& shadowFbo,
            int resolution,
            const glm::mat4& lightSpaceMatrix,
            ShaderManager& shaderManager,
            MeshCacheOpenGL& meshCache,
            FaceCullingControlOpenGL& culling
        );

        static void RenderPointShadowCube(
            const std::unordered_map<int, IGeometricObject*>& objects,
            const std::unordered_map<int, ITransformable*>& objectTransforms,
            FrameBufferOpenGL& pointShadowFbo,
            int resolution,
            const glm::vec3& lightPos,
            float nearPlane,
            float farPlane,
            ShaderManager& shaderManager,
            MeshCacheOpenGL& meshCache,
            FaceCullingControlOpenGL& culling
        );

        // TODO: consider making it a void and calculating ONLY when the scene state has been changed
        static glm::mat4 ComputeLightSpaceMatrix(
            const std::unordered_map<int, const IDirectionalLight*>& directionalLights,
            const Math::Vec3& sceneCenter
        );

        static void PopulateDirectionalLightUniforms(
            ShaderOpenGL& shader,
            const std::unordered_map<int, const IDirectionalLight*>& dirLights
        );

        static void PopulatePointLightUniforms(
            ShaderOpenGL& shader,
            const std::unordered_map<int, const IPointLight*>& pointLights
        );
    };
}


#endif // RENDERING__OPENGL__SUPPORT__SHADOW_RENDERER_OPENGL__HPP
