#ifndef SPACE__LIGHT_DATA__HPP
#define SPACE__LIGHT_DATA__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/light/light_types.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda::space
{
    class SPACE_API LightData
    {
    public:
        LightData(
            float intensity = 1.0f,
            float range = 100.0f,
            float inner_cutoff = 12.5f,
            float outer_cutoff = 17.5f,
            float attenuation_constant = 1.0f,
            float attenuation_linear = 0.05f,
            float attenuation_quadratic = 0.001f,
            const math::Vec3& diffuse_intensity = math::Vec3{ 1.0f, 1.0f, 1.0f },
            const math::Vec3& specular_intensity = math::Vec3{ 1.0f, 1.0f, 1.0f },
            const math::Vec3& position = math::Vec3{ 0.0f, 0.0f, 0.0f },
            const math::Vec3& color = math::Vec3{ 1.0f, 1.0f, 1.0f },
            const math::Vec3& direction = math::Vec3{ 0.0f, -1.0f, 0.0f },
            const LightType& light_type = LightType::None
        );

        ~LightData();

        // Getters
        float get_intensity() const;
        float get_range() const;
        float get_inner_cutoff() const;
        float get_outer_cutoff() const;
        float get_attenuation_constant() const;
        float get_attenuation_linear() const;
        float get_attenuation_quadratic() const;
        math::Vec3 get_diffuse_intensity() const;
        math::Vec3 get_specular_intensity() const;
        LightType get_light_type() const;
        math::Vec3 get_position() const;
        math::Vec3 get_color() const;
        math::Vec3 get_direction() const;

        // Setters
        void set_intensity(float intensity);
        void set_range(float range);
        void set_inner_cutoff(float inner_cutoff);
        void set_outer_cutoff(float outer_cutoff);
        void set_attenuation_constant(float attenuation_constant);
        void set_attenuation_linear(float attenuation_linear);
        void set_attenuation_quadratic(float attenuation_quadratic);
        void set_diffuse_intensity(const math::Vec3& diffuse_intensity);
        void set_specular_intensity(const math::Vec3& specular_intensity);
        void set_light_type(const LightType& light_type);
        void set_position(const math::Vec3& position);
        void set_color(const math::Vec3& color);
        void set_direction(const math::Vec3& direction);

    private:
        float m_intensity;
        float m_range;

        // TODO: Move these to the child classes once the spotlight is introduced
        float m_inner_cutoff;
        float m_outer_cutoff;

        float m_attenuation_constant;
        float m_attenuation_linear;
        float m_attenuation_quadratic;

        math::Vec3 m_diffuse_intensity;
        math::Vec3 m_specular_intensity;

        math::Vec3 m_position;
        math::Vec3 m_color;
        math::Vec3 m_direction;

        LightType m_light_type;
    };
}


#endif // SPACE__LIGHT_DATA__HPP