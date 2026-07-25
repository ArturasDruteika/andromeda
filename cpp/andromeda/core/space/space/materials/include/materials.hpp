#ifndef SPACE__MATERIALS__HPP
#define SPACE__MATERIALS__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/materials/i_material.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"
#include "pch.hpp"


namespace andromeda::space
{
	class SPACE_API Material
		: public IMaterial
	{
	public:
		Material();
		~Material() override;

		// Getters
		float get_shininess() const override;
		const std::string& get_name() const override;
		const math::Vec3& get_ambient() const override;
		const math::Vec3& get_diffuse() const override;
		const math::Vec3& get_specular() const override;

		// Setters
		void set_shininess(float shininess) override;
		void set_name(const std::string& name) override;
		void set_ambient(const math::Vec3& ambient) override;
		void set_diffuse(const math::Vec3& diffuse) override;
		void set_specular(const math::Vec3& specular) override;

	private:
		bool validate_vec3_components(const math::Vec3& vector);

	private:
		float m_shininess;
		std::string m_name;
		math::Vec3 m_ambient;
		math::Vec3 m_diffuse;
		math::Vec3 m_specular;
	};
}


#endif // SPACE__MATERIALS__HPP