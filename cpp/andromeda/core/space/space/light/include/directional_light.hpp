#ifndef SPACE__DIRECTIONAL_LIGHT__HPP
#define SPACE__DIRECTIONAL_LIGHT__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "../../objects/include/light_object.hpp"
#include "../../transformations/include/rotatable.hpp"
#include "light.hpp"

#include "andromeda/space/light/i_directional_light.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda::space
{
	class SPACE_API DirectionalLight
		: public IDirectionalLight
		, public Light
		, public LightObject
		, public Rotatable
	{
	public:
		DirectionalLight(
			const math::Vec3& direction,
			const math::Vec3& color = math::Vec3{ 1.0f, 1.0f, 1.0f },
			float intensity = 1.0f,
			const math::Vec3& ambient = math::Vec3{ 0.1f, 0.1f, 0.1f },
			const math::Vec3& diffuse = math::Vec3{ 0.4f, 0.4f, 0.4f },
			const math::Vec3& specular = math::Vec3{ 0.4f, 0.4f, 0.4f },
			float orthographic_half_size = 10.0f,
			float near_plane = 1.0f,
			float far_plane = 30.0f
		);

		~DirectionalLight() override;

		// Getters
		float get_light_orthographic_half_size() const override;
		float get_light_near_plane() const override;
		float get_light_far_plane() const override;
		const math::Vec3& get_direction() const override;

		// Setters
		void set_light_orthographic_half_size(float half_size) override;
		void set_light_near_plane(float near_plane) override;
		void set_light_far_plane(float far_plane) override;
		void set_direction(const math::Vec3& direction) override;

	private:
		float m_orthographic_half_size;
		float m_near_plane;
		float m_far_plane;
		math::Vec3 m_direction;
	};
}


#endif // SPACE__DIRECTIONAL_LIGHT__HPP