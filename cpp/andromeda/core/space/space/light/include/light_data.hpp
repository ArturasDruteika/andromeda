#ifndef SPACE__LIGHT_DATA__HPP
#define SPACE__LIGHT_DATA__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/light/light_types.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda::space
{
    /// @brief Stores common light source properties.
    ///
    /// Contains lighting, attenuation, spatial, and type information shared
    /// across different light implementations.
    class SPACE_API LightData
    {
    public:
        /// @brief Constructs a light data object.
        ///
        /// @param intensity Light intensity.
        /// @param range Maximum effective range of the light.
        /// @param inner_cutoff Inner spotlight cutoff angle.
        /// @param outer_cutoff Outer spotlight cutoff angle.
        /// @param attenuation_constant Constant attenuation coefficient.
        /// @param attenuation_linear Linear attenuation coefficient.
        /// @param attenuation_quadratic Quadratic attenuation coefficient.
        /// @param diffuse_intensity Diffuse lighting intensity.
        /// @param specular_intensity Specular lighting intensity.
        /// @param position Light position.
        /// @param color Light color.
        /// @param direction Light direction.
        /// @param light_type Light source type.
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

        /// @brief Destroys the light data object.
        ~LightData();

        // Getters

        /// @brief Retrieves the light intensity.
        ///
        /// @return Light intensity.
        float get_intensity() const;

        /// @brief Retrieves the maximum effective light range.
        ///
        /// @return Light range.
        float get_range() const;

        /// @brief Retrieves the inner spotlight cutoff.
        ///
        /// @return Inner cutoff value.
        float get_inner_cutoff() const;

        /// @brief Retrieves the outer spotlight cutoff.
        ///
        /// @return Outer cutoff value.
        float get_outer_cutoff() const;

        /// @brief Retrieves the constant attenuation coefficient.
        ///
        /// @return Constant attenuation coefficient.
        float get_attenuation_constant() const;

        /// @brief Retrieves the linear attenuation coefficient.
        ///
        /// @return Linear attenuation coefficient.
        float get_attenuation_linear() const;

        /// @brief Retrieves the quadratic attenuation coefficient.
        ///
        /// @return Quadratic attenuation coefficient.
        float get_attenuation_quadratic() const;

        /// @brief Retrieves the diffuse lighting intensity.
        ///
        /// @return Diffuse intensity.
        math::Vec3 get_diffuse_intensity() const;

        /// @brief Retrieves the specular lighting intensity.
        ///
        /// @return Specular intensity.
        math::Vec3 get_specular_intensity() const;

        /// @brief Retrieves the light source type.
        ///
        /// @return Light type.
        LightType get_light_type() const;

        /// @brief Retrieves the light position.
        ///
        /// @return Light position.
        math::Vec3 get_position() const;

        /// @brief Retrieves the light color.
        ///
        /// @return Light color.
        math::Vec3 get_color() const;

        /// @brief Retrieves the light direction.
        ///
        /// @return Light direction.
        math::Vec3 get_direction() const;

        // Setters

        /// @brief Sets the light intensity.
        ///
        /// @param intensity New light intensity.
        void set_intensity(float intensity);

        /// @brief Sets the maximum effective light range.
        ///
        /// @param range New light range.
        void set_range(float range);

        /// @brief Sets the inner spotlight cutoff.
        ///
        /// @param inner_cutoff New inner cutoff value.
        void set_inner_cutoff(float inner_cutoff);

        /// @brief Sets the outer spotlight cutoff.
        ///
        /// @param outer_cutoff New outer cutoff value.
        void set_outer_cutoff(float outer_cutoff);

        /// @brief Sets the constant attenuation coefficient.
        ///
        /// @param attenuation_constant New constant attenuation coefficient.
        void set_attenuation_constant(float attenuation_constant);

        /// @brief Sets the linear attenuation coefficient.
        ///
        /// @param attenuation_linear New linear attenuation coefficient.
        void set_attenuation_linear(float attenuation_linear);

        /// @brief Sets the quadratic attenuation coefficient.
        ///
        /// @param attenuation_quadratic New quadratic attenuation coefficient.
        void set_attenuation_quadratic(float attenuation_quadratic);

        /// @brief Sets the diffuse lighting intensity.
        ///
        /// @param diffuse_intensity New diffuse intensity.
        void set_diffuse_intensity(const math::Vec3& diffuse_intensity);

        /// @brief Sets the specular lighting intensity.
        ///
        /// @param specular_intensity New specular intensity.
        void set_specular_intensity(const math::Vec3& specular_intensity);

        /// @brief Sets the light source type.
        ///
        /// @param light_type New light type.
        void set_light_type(const LightType& light_type);

        /// @brief Sets the light position.
        ///
        /// @param position New light position.
        void set_position(const math::Vec3& position);

        /// @brief Sets the light color.
        ///
        /// @param color New light color.
        void set_color(const math::Vec3& color);

        /// @brief Sets the light direction.
        ///
        /// @param direction New light direction.
        void set_direction(const math::Vec3& direction);

    private:
        /// @brief Light intensity.
        float m_intensity;

        /// @brief Maximum effective light range.
        float m_range;

        // TODO: Move these to the child classes once the spotlight is introduced

        /// @brief Inner spotlight cutoff.
        float m_inner_cutoff;

        /// @brief Outer spotlight cutoff.
        float m_outer_cutoff;

        /// @brief Constant attenuation coefficient.
        float m_attenuation_constant;

        /// @brief Linear attenuation coefficient.
        float m_attenuation_linear;

        /// @brief Quadratic attenuation coefficient.
        float m_attenuation_quadratic;

        /// @brief Diffuse lighting intensity.
        math::Vec3 m_diffuse_intensity;

        /// @brief Specular lighting intensity.
        math::Vec3 m_specular_intensity;

        /// @brief Light position.
        math::Vec3 m_position;

        /// @brief Light color.
        math::Vec3 m_color;

        /// @brief Light direction.
        math::Vec3 m_direction;

        /// @brief Light source type.
        LightType m_light_type;
    };
}


#endif // SPACE__LIGHT_DATA__HPP