#ifndef SPACE__LIGHT__HPP
#define SPACE__LIGHT__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/light/i_light.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda::space
{
	class SPACE_API Light
		: public virtual ILight
	{
	public:
		Light(
			const math::Vec3& color,
			float intensity,
			const math::Vec3& ambient,
			const math::Vec3& diffuse,
			const math::Vec3& specular
		);

		~Light() override;

		// Getters
		float get_intensity() const override;
		math::Vec3 get_color() const override;
		math::Vec3 get_ambient() const override;
		math::Vec3 get_diffuse() const override;
		math::Vec3 get_specular() const override;

		// Setters
		void set_intensity(float intensity) override;
		void set_color(const math::Vec3& color) override;
		void set_ambient(const math::Vec3& ambient) override;
		void set_diffuse(const math::Vec3& diffuse) override;
		void set_specular(const math::Vec3& specular) override;

	private:
		float m_intensity;
		math::Vec3 m_color;
		math::Vec3 m_ambient;
		math::Vec3 m_diffuse;
		math::Vec3 m_specular;
	};
}


#endif // SPACE__LIGHT__HPP