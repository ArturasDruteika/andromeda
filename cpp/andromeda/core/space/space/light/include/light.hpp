#ifndef SPACE__LIGHT__HPP
#define SPACE__LIGHT__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "andromeda/space/light/i_light.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda::Space
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
		float GetIntensity() const override;
		math::Vec3 GetColor() const override;
		math::Vec3 GeAmbient() const override;
		math::Vec3 GetDiffuse() const override;
		math::Vec3 GetSpecular() const override;
		// Setters
		void SetIntensity(float intensity) override;
		void SetColor(const math::Vec3& color) override;
		void SetAmbient(const math::Vec3& ambient) override;
		void SetDiffuse(const math::Vec3& diffuse) override;
		void SetSpecular(const math::Vec3& specular) override;

	private:
		float m_intensity;
		math::Vec3 m_color;
		math::Vec3 m_ambient;
		math::Vec3 m_diffuse;
		math::Vec3 m_specular;
	};
}


#endif // SPACE__LIGHT__HPP