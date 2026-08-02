#ifndef SPACE__LIGHT__HPP
#define SPACE__LIGHT__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/light/i_light.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda::space
{
	/// @brief Implements the common properties of a light source.
	///
	/// Stores the color, intensity, and ambient, diffuse, and specular
	/// components shared by concrete light types.
	class SPACE_API Light
		: public virtual ILight
	{
	public:
		/// @brief Constructs a light source.
		///
		/// @param color Light color.
		/// @param intensity Light intensity.
		/// @param ambient Ambient lighting component.
		/// @param diffuse Diffuse lighting component.
		/// @param specular Specular lighting component.
		Light(
			const math::Vec3& color,
			float intensity,
			const math::Vec3& ambient,
			const math::Vec3& diffuse,
			const math::Vec3& specular
		);

		/// @brief Destroys the light source.
		~Light() override;

		// Getters

		/// @brief Retrieves the light intensity.
		///
		/// @return Light intensity.
		float get_intensity() const override;

		/// @brief Retrieves the light color.
		///
		/// @return Light color.
		math::Vec3 get_color() const override;

		/// @brief Retrieves the ambient lighting component.
		///
		/// @return Ambient lighting component.
		math::Vec3 get_ambient() const override;

		/// @brief Retrieves the diffuse lighting component.
		///
		/// @return Diffuse lighting component.
		math::Vec3 get_diffuse() const override;

		/// @brief Retrieves the specular lighting component.
		///
		/// @return Specular lighting component.
		math::Vec3 get_specular() const override;

		// Setters

		/// @brief Sets the light intensity.
		///
		/// @param intensity New light intensity.
		void set_intensity(float intensity) override;

		/// @brief Sets the light color.
		///
		/// @param color New light color.
		void set_color(const math::Vec3& color) override;

		/// @brief Sets the ambient lighting component.
		///
		/// @param ambient New ambient lighting component.
		void set_ambient(const math::Vec3& ambient) override;

		/// @brief Sets the diffuse lighting component.
		///
		/// @param diffuse New diffuse lighting component.
		void set_diffuse(const math::Vec3& diffuse) override;

		/// @brief Sets the specular lighting component.
		///
		/// @param specular New specular lighting component.
		void set_specular(const math::Vec3& specular) override;

	private:
		/// @brief Light intensity.
		float m_intensity;

		/// @brief Light color.
		math::Vec3 m_color;

		/// @brief Ambient lighting component.
		math::Vec3 m_ambient;

		/// @brief Diffuse lighting component.
		math::Vec3 m_diffuse;

		/// @brief Specular lighting component.
		math::Vec3 m_specular;
	};
}


#endif // SPACE__LIGHT__HPP