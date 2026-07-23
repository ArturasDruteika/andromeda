#ifndef API__SPACE__TRANSFORMATIONS__I_SCALABLE__HPP
#define API__SPACE__TRANSFORMATIONS__I_SCALABLE__HPP

#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda
{
    class IScalable
    {
    public:
        virtual ~IScalable() = default;

        // Getters
        virtual bool state_changed() const = 0;
        virtual const math::Vec3& get_scale() const = 0;
		virtual const math::Mat4& get_scale_matrix() const = 0;
        // Setters
        virtual void reset_state() = 0;
        virtual void set_scale(const math::Vec3& scale) = 0;

        virtual void scale(const math::Vec3& scale) = 0;
        virtual void scale(float uniform_scale) = 0;
    };
}


#endif // API__SPACE__TRANSFORMATIONS__I_SCALABLE__HPP