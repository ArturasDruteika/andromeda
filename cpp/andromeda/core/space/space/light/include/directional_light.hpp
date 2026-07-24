#ifndef SPACE__DIRECTIONAL_LIGHT__HPP
#define SPACE__DIRECTIONAL_LIGHT__HPP


#include "Light.hpp"
#include "../../Objects/include/LightObject.hpp"
#include "../../Transformations/include/Rotatable.hpp"
#include "../../MacroExports/include/MacroExports.hpp"
#include "andromeda/space/light/i_directional_light.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda::Space
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
			float orthographicHalfSize = 10.0f,
			float nearPlane = 1.0f,
			float farPlane = 30.0f
		);
		~DirectionalLight() override;

		// Getters
		float GetLightOrthographicHalfSize() const override;
		float GetLightNearPlane() const override;
		float GetLightFarPlane() const override;
		const math::Vec3& GetDirection() const override;
		// Setters
		void SetLightOrthographicHalfSize(float halfSize) override;
		void SetLightNearPlane(float nearPlane) override;
		void SetLightFarPlane(float farPlane) override;
		void SetDirection(const math::Vec3& direction) override;

	private:
		float m_orthographicHalfSize;
		float m_nearPlane;
		float m_farPlane;
		math::Vec3 m_direction;
	};
}


#endif // SPACE__DIRECTIONAL_LIGHT__HPP