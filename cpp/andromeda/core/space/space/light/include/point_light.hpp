#ifndef SPACE__POINT_LIGHT__HPP
#define SPACE__POINT_LIGHT__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "../../objects/include/light_object.hpp"
#include "light.hpp"

#include "andromeda/space/light/i_point_light.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda::space
{
	/// @brief Represents a point light source.
	///
	/// Models a light that emits in all directions from a position in space.
	/// Stores attenuation parameters and shadow projection settings.
	class SPACE_API PointLight
		: public IPointLight
		, public Light
		, public LightObject
	{
	public:
		/// @brief Constructs a point light.
		///
		/// @param position Light position.
		/// @param color Light color.
		/// @param intensity Light intensity.
		/// @param ambient Ambient lighting component.
		/// @param diffuse Diffuse lighting component.
		/// @param specular Specular lighting component.
		/// @param attenuation_constant Constant attenuation coefficient.
		/// @param attenuation_linear Linear attenuation coefficient.
		/// @param attenuation_quadratic Quadratic attenuation coefficient.
		/// @param shadow_near_plane Near clipping plane for shadow rendering.
		/// @param shadow_far_plane Far clipping plane for shadow rendering.
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

		/// @brief Destroys the point light.
		~PointLight() override;

		// Getters

		/// @brief Retrieves the constant attenuation coefficient.
		///
		/// @return Constant attenuation coefficient.
		float get_attenuation_constant() const override;

		/// @brief Retrieves the linear attenuation coefficient.
		///
		/// @return Linear attenuation coefficient.
		float get_attenuation_linear() const override;

		/// @brief Retrieves the quadratic attenuation coefficient.
		///
		/// @return Quadratic attenuation coefficient.
		float get_attenuation_quadratic() const override;

		/// @brief Retrieves the near clipping plane used for shadow rendering.
		///
		/// @return Near clipping plane distance.
		float get_shadow_near_plane() const override;

		/// @brief Retrieves the far clipping plane used for shadow rendering.
		///
		/// @return Far clipping plane distance.
		float get_shadow_far_plane() const override;

		/// @brief Retrieves the light position.
		///
		/// @return Light position in world space.
		const math::Vec3& get_position() const override;

		// Setters

		/// @brief Sets the constant attenuation coefficient.
		///
		/// @param attenuation_constant New constant attenuation coefficient.
		void set_attenuation_constant(float attenuation_constant) override;

		/// @brief Sets the linear attenuation coefficient.
		///
		/// @param attenuation_linear New linear attenuation coefficient.
		void set_attenuation_linear(float attenuation_linear) override;

		/// @brief Sets the quadratic attenuation coefficient.
		///
		/// @param attenuation_quadratic New quadratic attenuation coefficient.
		void set_attenuation_quadratic(float attenuation_quadratic) override;

		/// @brief Sets the near clipping plane used for shadow rendering.
		///
		/// @param shadow_near_plane New near clipping plane distance.
		void set_shadow_near_plane(float shadow_near_plane) override;

		/// @brief Sets the far clipping plane used for shadow rendering.
		///
		/// @param shadow_far_plane New far clipping plane distance.
		void set_shadow_far_plane(float shadow_far_plane) override;

		/// @brief Sets the light position.
		///
		/// @param position New light position in world space.
		void set_position(const math::Vec3& position) override;

	private:
		/// @brief Constant attenuation coefficient.
		float m_attenuation_constant;

		/// @brief Linear attenuation coefficient.
		float m_attenuation_linear;

		/// @brief Quadratic attenuation coefficient.
		float m_attenuation_quadratic;

		/// @brief Near clipping plane for shadow rendering.
		float m_shadow_near_plane;

		/// @brief Far clipping plane for shadow rendering.
		float m_shadow_far_plane;

		/// @brief Light position in world space.
		math::Vec3 m_position;
	};
}


#endif // SPACE__POINT_LIGHT__HPP