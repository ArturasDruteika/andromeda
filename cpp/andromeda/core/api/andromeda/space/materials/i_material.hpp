#ifndef ANDROMEDA__MATERIALS__I_MATERIAL__HPP
#define ANDROMEDA__MATERIALS__I_MATERIAL__HPP


#include "math/linear_algebra/include/linear_algebra_data_types.hpp"
#include <string>


namespace andromeda
{
    class IMaterial
    {
    public:
        virtual ~IMaterial() = default;

        // Getters
        virtual float get_shininess() const = 0;
        virtual const std::string& get_name() const = 0;
        virtual const math::Vec3& get_ambient() const = 0;
        virtual const math::Vec3& get_diffuse() const = 0;
        virtual const math::Vec3& get_specular() const = 0;
        // Setters
        virtual void set_shininess(float shininess) = 0;
        virtual void set_name(const std::string& name) = 0;
        virtual void set_ambient(const math::Vec3& ambient) = 0;
        virtual void set_diffuse(const math::Vec3& diffuse) = 0;
        virtual void set_specular(const math::Vec3& specular) = 0;
    };
}


#endif // ANDROMEDA__MATERIALS__I_MATERIAL__HPP