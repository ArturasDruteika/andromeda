#ifndef SPACE__MATERIALS__HPP
#define SPACE__MATERIALS__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "pch.hpp"
#include "math/LinearAlgebra/include/linear_algebra_data_types.hpp"
#include "andromeda/space/materials/i_material.hpp"


namespace andromeda::Space
{
    class SPACE_API Material
		: public IMaterial
    {
    public:
        Material();
        ~Material();

        // Getters
        float GetShininess() const override;
        const std::string& GetName() const override;
        const math::Vec3& GetAmbient() const override;
        const math::Vec3& GetDiffuse() const override;
        const math::Vec3& GetSpecular() const override;
        // Setters
        void SetShininess(float shininess) override;
        void SetName(const std::string& name) override;
        void SetAmbient(const math::Vec3& ambient) override;
        void SetDiffuse(const math::Vec3& diffuse) override;
        void SetSpecular(const math::Vec3& specular) override;

    private:
        bool ValidateVec3Components(const math::Vec3& vector);

    private:
        float m_shininess;
        std::string m_name;
        math::Vec3 m_ambient;
        math::Vec3 m_diffuse;
        math::Vec3 m_specular;
    };
}


#endif // SPACE__MATERIALS__HPP