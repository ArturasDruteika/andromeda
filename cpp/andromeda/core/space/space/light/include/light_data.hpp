#ifndef SPACE__LIGHT_DATA__HPP
#define SPACE__LIGHT_DATA__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "andromeda/space/light/light_types.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda::Space
{
    class SPACE_API LightData
    {
    public:
        LightData(
            float intensity = 1.0f,
            float range = 100.0f,
            float innerCutoff = 12.5f,
            float outerCutoff = 17.5f,
            float attenuationConstant = 1.0f,
            float attenuationLinear =  0.05f ,
            float attenuationQuadratic = 0.001f,
            const math::Vec3& diffuseIntensity = math::Vec3{ 1.0f, 1.0f, 1.0f },
            const math::Vec3& specularIntensity = math::Vec3{ 1.0f, 1.0f, 1.0f },
            const math::Vec3& position = math::Vec3{ 0.0f, 0.0f, 0.0f },
            const math::Vec3& color = math::Vec3{ 1.0f, 1.0f, 1.0f },
            const math::Vec3& direction = math::Vec3{ 0.0f, -1.0f, 0.0f },
            const LightType& lightType = LightType::None
        );
        ~LightData();

        // Getters
        float GetIntensity() const;
        float GetRange() const;
        float GetInnerCutoff() const;
        float GetOuterCutoff() const;
        float GetAttenuationConstant() const;
        float GetAttenuationLinear() const;
        float GetAttenuationQuadratic() const;
        math::Vec3 GetDiffuseIntensity() const;
        math::Vec3 GetSpecularIntensity() const;
        LightType GetLightType() const;
        math::Vec3 GetPosition() const;
        math::Vec3 GetColor() const;
        math::Vec3 GetDirection() const;
        // Setters
        void SetIntensity(float intensity);
        void SetRange(float range);
        void SetInnerCutoff(float innerCutoff);
        void SetOuterCutoff(float outerCutoff);
        void SetAttenuationConstant(float constant);
        void SetAttenuationLinear(float linear);
        void SetAttenuationQuadratic(float quadratic);
        void SetDiffuseIntensity(const math::Vec3& diffuseIntensity);
        void SetSpecularIntensity(const math::Vec3& specularIntensity);
        void SetLightType(const LightType& lightType);
        void SetPosition(const math::Vec3& position);
        void SetColor(const math::Vec3& color);
        void SetDirection(const math::Vec3& direction);

    private:
        float m_intensity;
        float m_range;
        // TODO: Move these to the child classes once the spotlight is introduced
        float m_innerCutoff;
        float m_outerCutoff;
        float m_attenuationConstant;
        float m_attenuationLinear;
        float m_attenuationQuadratic;
        math::Vec3 m_diffuseIntensity;
        math::Vec3 m_specularIntensity;
        math::Vec3 m_position;
        math::Vec3 m_color;
        math::Vec3 m_direction;
        LightType m_lightType;
    };
}


#endif // SPACE__LIGHT_DATA__HPP