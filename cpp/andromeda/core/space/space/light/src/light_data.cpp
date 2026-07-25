#include "../include/light_data.hpp"
#include "math/linear_algebra/include/linear_algebra_operations.hpp"
#include "spdlog/spdlog.h"


namespace andromeda::space
{
    LightData::LightData(
        float intensity,
        float range,
        float inner_cutoff,
        float outer_cutoff,
        float attenuation_constant,
        float attenuation_linear,
        float attenuation_quadratic,
        const math::Vec3& diffuse_intensity,
        const math::Vec3& specular_intensity,
        const math::Vec3& position,
        const math::Vec3& color,
        const math::Vec3& direction,
        const LightType& light_type
    )
        : m_intensity{ intensity }
        , m_range{ range }
        , m_inner_cutoff{ inner_cutoff }
        , m_outer_cutoff{ outer_cutoff }
        , m_attenuation_constant{ attenuation_constant }
        , m_attenuation_linear{ attenuation_linear }
        , m_attenuation_quadratic{ attenuation_quadratic }
        , m_diffuse_intensity{ diffuse_intensity }
        , m_specular_intensity{ specular_intensity }
        , m_light_type{ light_type }
        , m_position{ position }
        , m_color{ color }
        , m_direction{ math::LinAlgOps::normalize(direction) }
    {
    }

    LightData::~LightData() = default;

    float LightData::get_intensity() const
    {
        return m_intensity;
    }

    float LightData::get_range() const
    {
        return m_range;
    }

    float LightData::get_inner_cutoff() const
    {
        return m_inner_cutoff;
    }

    float LightData::get_outer_cutoff() const
    {
        return m_outer_cutoff;
    }

    float LightData::get_attenuation_constant() const
    {
        return m_attenuation_constant;
    }

    float LightData::get_attenuation_linear() const
    {
        return m_attenuation_linear;
    }

    float LightData::get_attenuation_quadratic() const
    {
        return m_attenuation_quadratic;
    }

    math::Vec3 LightData::get_diffuse_intensity() const
    {
        return m_diffuse_intensity;
    }

    math::Vec3 LightData::get_specular_intensity() const
    {
        return m_specular_intensity;
    }

    LightType LightData::get_light_type() const
    {
        return m_light_type;
    }

    math::Vec3 LightData::get_position() const
    {
        return m_position;
    }

    math::Vec3 LightData::get_color() const
    {
        return m_color;
    }

    math::Vec3 LightData::get_direction() const
    {
        return m_direction;
    }


    void LightData::set_intensity(float intensity)
    {
        if (intensity < 0.0f)
            spdlog::error("Intensity must be non-negative");
        m_intensity = intensity;
    }

    void LightData::set_range(float range)
    {
        if (range <= 0.0f)
            spdlog::error("Range must be positive");
        m_range = range;
    }

    void LightData::set_inner_cutoff(float inner_cutoff)
    {
        if (inner_cutoff < 0.0f || inner_cutoff > 1.0f)
            spdlog::error("Inner cutoff must be in [0, 1]");
        if (inner_cutoff > m_outer_cutoff)
            spdlog::error("Inner cutoff cannot exceed outer cutoff");
        m_inner_cutoff = inner_cutoff;
    }

    void LightData::set_outer_cutoff(float outer_cutoff)
    {
        if (outer_cutoff < 0.0f || outer_cutoff > 1.0f)
            spdlog::error("Outer cutoff must be in [0, 1]");
        if (outer_cutoff < m_inner_cutoff)
            spdlog::error("Outer cutoff cannot be less than inner cutoff");
        m_outer_cutoff = outer_cutoff;
    }

    void LightData::set_attenuation_constant(float constant)
    {
        if (constant < 0.0f)
            spdlog::error("Attenuation constant must be non-negative");
        m_attenuation_constant = constant;
    }

    void LightData::set_attenuation_linear(float linear)
    {
        if (linear < 0 || linear > 1)
        {
            spdlog::error(
                "Attenuation linear components must be between 0.0 and 1.0"
            );
            return;
        }
        m_attenuation_linear = linear;
    }

    void LightData::set_attenuation_quadratic(float quadratic)
    {
        if (quadratic < 0 || quadratic > 1)
        {
            spdlog::error(
                "Attenuation quadratic components must be between 0.0 and 1.0"
            );
            return;
        }
        m_attenuation_quadratic = quadratic;
    }

    void LightData::set_diffuse_intensity(const math::Vec3& diffuse_intensity)
    {
        m_diffuse_intensity = diffuse_intensity;
    }

    void LightData::set_specular_intensity(const math::Vec3& specular_intensity)
    {
        m_specular_intensity = specular_intensity;
    }

    void LightData::set_light_type(const LightType& light_type)
    {
        m_light_type = light_type;
    }

    void LightData::set_position(const math::Vec3& position)
    {
        m_position = position;
    }

    void LightData::set_color(const math::Vec3& color)
    {
        m_color = color;
    }

    void LightData::set_direction(const math::Vec3& direction)
    {
        float len_2 = math::LinAlgOps::dot_prod(direction, direction);
        if (len_2 < 1e-6f)
        {
            spdlog::error("Direction vector must be non-zero");
            return;
        }
        m_direction = math::LinAlgOps::normalize(direction);
    }
}