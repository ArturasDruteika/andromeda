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
	/// @brief Represents a directional light source.
	///
	/// Models a light with parallel rays, commonly used to simulate sunlight.
	/// Stores lighting parameters together with shadow projection settings.
	class SPACE_API DirectionalLight
		: public IDirectionalLight
		, public Light
		, public LightObject
		, public Rotatable
	{
	public:
		/// @brief Constructs a directional light.
		///
		/// @param direction Light direction.
		/// @param color Light color.
		/// @param intensity Light intensity.
		/// @param ambient Ambient lighting contribution.
		/// @param diffuse Diffuse lighting contribution.
		/// @param specular Specular lighting contribution.
		/// @param orthographic_half_size Half-size of the orthographic shadow projection.
		/// @param near_plane Near clipping plane for shadow rendering.
		/// @param far_plane Far clipping plane for shadow rendering.
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

		/// @brief Destroys the directional light.
		~DirectionalLight() override;

		// Getters

		/// @brief Retrieves the half-size of the orthographic shadow projection.
		///
		/// @return Orthographic projection half-size.
		float get_light_orthographic_half_size() const override;

		/// @brief Retrieves the near clipping plane used for shadow rendering.
		///
		/// @return Near clipping plane distance.
		float get_light_near_plane() const override;

		/// @brief Retrieves the far clipping plane used for shadow rendering.
		///
		/// @return Far clipping plane distance.
		float get_light_far_plane() const override;

		/// @brief Retrieves the light direction.
		///
		/// @return Normalized light direction.
		const math::Vec3& get_direction() const override;

		// Setters

		/// @brief Sets the half-size of the orthographic shadow projection.
		///
		/// @param half_size New orthographic projection half-size.
		void set_light_orthographic_half_size(float half_size) override;

		/// @brief Sets the near clipping plane used for shadow rendering.
		///
		/// @param near_plane New near clipping plane distance.
		void set_light_near_plane(float near_plane) override;

		/// @brief Sets the far clipping plane used for shadow rendering.
		///
		/// @param far_plane New far clipping plane distance.
		void set_light_far_plane(float far_plane) override;

		/// @brief Sets the light direction.
		///
		/// @param direction New light direction.
		void set_direction(const math::Vec3& direction) override;

	private:
		/// @brief Half-size of the orthographic shadow projection.
		float m_orthographic_half_size;

		/// @brief Near clipping plane for shadow rendering.
		float m_near_plane;

		/// @brief Far clipping plane for shadow rendering.
		float m_far_plane;

		/// @brief Direction of the light.
		math::Vec3 m_direction;
	};
}


#endif // SPACE__DIRECTIONAL_LIGHT__HPP