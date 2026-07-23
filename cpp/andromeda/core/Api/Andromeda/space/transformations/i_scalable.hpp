#ifndef API__SPACE__TRANSFORMATIONS__I_SCALABLE__HPP
#define API__SPACE__TRANSFORMATIONS__I_SCALABLE__HPP

#include "Math/LinearAlgebra/include/linear_algebra_data_types.hpp"


namespace Andromeda
{
    class IScalable
    {
    public:
        virtual ~IScalable() = default;

        // Getters
        virtual bool state_changed() const = 0;
        virtual const Math::Vec3& get_scale() const = 0;
		virtual const Math::Mat4& get_scale_matrix() const = 0;
        // Setters
        virtual void reset_state() = 0;
        virtual void set_scale(const Math::Vec3& scale) = 0;

        virtual void scale(const Math::Vec3& scale) = 0;
        virtual void scale(float uniform_scale) = 0;
    };
}


#endif // API__SPACE__TRANSFORMATIONS__I_SCALABLE__HPP