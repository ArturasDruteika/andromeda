#ifndef SPACE__POINT_LIGHT__HPP
#define SPACE__POINT_LIGHT__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "../../objects/include/light_object.hpp"
#include "light.hpp"

#include "andromeda/space/light/i_point_light.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda::space
{
	class SPACE_API PointLight
		: public IPointLight
		, public Light
		, public LightObject
	{
	public:
		PointLight(
			const math::Vec3& position,
			const math::Vec3& color = math::Vec3{ 1.0f, 1.0f, 1.0f },
			float intensity = 1.0f,
			const math::Vec3& ambient = math::Vec3{ 0.1f, 0.1f, 0.1f },
			const math::Vec3& diffuse = math::Vec3{ 1.0f, 1.0f, 1.0f },
			const math::Vec3& specular = math::Vec3{ 1.0f, 1.0f, 1.0f },
			float attenuation_constant = 1.0f,
			float attenuation_linear = 0.1f,
			float attenuation_quadratic = 0.01f,
			float shadow_near_plane = 0.1f,
			float shadow_far_plane = 25.0f
		);

		~PointLight() override;

		// Getters
		float get_attenuation_constant() const override;
		float get_attenuation_linear() const override;
		float get_attenuation_quadratic() const override;
		float get_shadow_near_plane() const override;
		float get_shadow_far_plane() const override;
		const math::Vec3& get_position() const override;

		// Setters
		void set_attenuation_constant(float attenuation_constant) override;
		void set_attenuation_linear(float attenuation_linear) override;
		void set_attenuation_quadratic(float attenuation_quadratic) override;
		void set_shadow_near_plane(float shadow_near_plane) override;
		void set_shadow_far_plane(float shadow_far_plane) override;
		void set_position(const math::Vec3& position) override;

	private:
		float m_attenuation_constant;
		float m_attenuation_linear;
		float m_attenuation_quadratic;

		float m_shadow_near_plane;
		float m_shadow_far_plane;

		math::Vec3 m_position;
	};
}


#endif // SPACE__POINT_LIGHT__HPP