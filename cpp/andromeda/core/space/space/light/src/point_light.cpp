#include "../include/point_light.hpp"
#include "spdlog/spdlog.h"


namespace andromeda::space
{
    PointLight::PointLight(
        const math::Vec3& position,
        const math::Vec3& color,
        float intensity,
        const math::Vec3& ambient,
        const math::Vec3& diffuse,
        const math::Vec3& specular,
        float attenuation_constant,
        float attenuation_linear,
        float attenuation_quadratic,
        float shadow_near_plane,
        float shadow_far_plane
    )
        : Light{
            color,
            intensity,
            ambient,
            diffuse,
            specular
        }
        , LightObject{ LightType::Point }
        , m_attenuation_constant{ attenuation_constant }
        , m_attenuation_linear{ attenuation_linear }
        , m_attenuation_quadratic{ attenuation_quadratic }
        , m_shadow_near_plane{ shadow_near_plane }
        , m_shadow_far_plane{ shadow_far_plane }
        , m_position{ position }
    {
    }

    PointLight::~PointLight() = default;

    float PointLight::get_attenuation_constant() const
    {
        return m_attenuation_constant;
    }

    float PointLight::get_attenuation_linear() const
    {
        return m_attenuation_linear;
    }

    float PointLight::get_attenuation_quadratic() const
    {
        return m_attenuation_quadratic;
    }

    float PointLight::get_shadow_near_plane() const
    {
        return m_shadow_near_plane;
    }

    float PointLight::get_shadow_far_plane() const
    {
        return m_shadow_far_plane;
    }

    const math::Vec3& PointLight::get_position() const
    {
        return m_position;
    }

    void PointLight::set_attenuation_constant(float attenuation_constant)
    {
        if (attenuation_constant < 0.0f)
        {
            spdlog::error("Attenuation constant must be non-negative");
            return;
        }

        m_attenuation_constant = attenuation_constant;
    }

    void PointLight::set_attenuation_linear(float attenuation_linear)
    {
        if (attenuation_linear < 0.0f || attenuation_linear > 1.0f)
        {
            spdlog::error(
                "Attenuation linear component must be between 0.0 and 1.0"
            );
            return;
        }

        m_attenuation_linear = attenuation_linear;
    }

    void PointLight::set_attenuation_quadratic(float attenuation_quadratic)
    {
        if (attenuation_quadratic < 0.0f || attenuation_quadratic > 1.0f)
        {
            spdlog::error(
                "Attenuation quadratic component must be between 0.0 and 1.0"
            );
            return;
        }

        m_attenuation_quadratic = attenuation_quadratic;
    }

    void PointLight::set_shadow_near_plane(float shadow_near_plane)
    {
        m_shadow_near_plane = shadow_near_plane;
    }

    void PointLight::set_shadow_far_plane(float shadow_far_plane)
    {
        m_shadow_far_plane = shadow_far_plane;
    }

    void PointLight::set_position(const math::Vec3& position)
    {
        m_position = position;
    }
}