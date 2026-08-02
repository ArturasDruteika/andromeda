#ifndef SPACE__MATERIALS__HPP
#define SPACE__MATERIALS__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/materials/i_material.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"
#include "pch.hpp"


namespace andromeda::space
{
	/// @brief Represents a material used for rendering surface appearance.
	///
	/// Stores material properties such as ambient, diffuse, specular
	/// reflectance, shininess, and a descriptive name.
	class SPACE_API Material
		: public IMaterial
	{
	public:
		/// @brief Constructs a material with default properties.
		Material();

		/// @brief Destroys the material.
		~Material() override;

		// Getters

		/// @brief Retrieves the material shininess.
		///
		/// @return Shininess exponent.
		float get_shininess() const override;

		/// @brief Retrieves the material name.
		///
		/// @return Material name.
		const std::string& get_name() const override;

		/// @brief Retrieves the ambient reflectance.
		///
		/// @return Ambient color.
		const math::Vec3& get_ambient() const override;

		/// @brief Retrieves the diffuse reflectance.
		///
		/// @return Diffuse color.
		const math::Vec3& get_diffuse() const override;

		/// @brief Retrieves the specular reflectance.
		///
		/// @return Specular color.
		const math::Vec3& get_specular() const override;

		// Setters

		/// @brief Sets the material shininess.
		///
		/// @param shininess New shininess exponent.
		void set_shininess(float shininess) override;

		/// @brief Sets the material name.
		///
		/// @param name New material name.
		void set_name(const std::string& name) override;

		/// @brief Sets the ambient reflectance.
		///
		/// @param ambient New ambient color.
		void set_ambient(const math::Vec3& ambient) override;

		/// @brief Sets the diffuse reflectance.
		///
		/// @param diffuse New diffuse color.
		void set_diffuse(const math::Vec3& diffuse) override;

		/// @brief Sets the specular reflectance.
		///
		/// @param specular New specular color.
		void set_specular(const math::Vec3& specular) override;

	private:
		/// @brief Validates the components of a 3D vector.
		///
		/// @param vector Vector to validate.
		/// @return `true` if all vector components are valid; otherwise, `false`.
		bool validate_vec3_components(const math::Vec3& vector);

	private:
		/// @brief Material shininess exponent.
		float m_shininess;

		/// @brief Material name.
		std::string m_name;

		/// @brief Ambient reflectance.
		math::Vec3 m_ambient;

		/// @brief Diffuse reflectance.
		math::Vec3 m_diffuse;

		/// @brief Specular reflectance.
		math::Vec3 m_specular;
	};
}


#endif // SPACE__MATERIALS__HPP