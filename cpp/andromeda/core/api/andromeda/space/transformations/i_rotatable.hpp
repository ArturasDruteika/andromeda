#ifndef API__SPACE__TRANSFORMATIONS__I_ROTATABLE__HPP
#define API__SPACE__TRANSFORMATIONS__I_ROTATABLE__HPP


#include "Math/LinearAlgebra/include/linear_algebra_data_types.hpp"
#include "Math/LinearAlgebra/include/quaternions.hpp"


namespace andromeda
{
    class IRotatable
    {
    public:
        virtual ~IRotatable() = default;

        // Getters
        virtual bool state_changed() const = 0;
        virtual const Math::Vec3& get_rotation() const = 0;
        virtual const Math::Mat4& get_rotation_matrix() const = 0;
        virtual const Math::Quaternion& get_orientation() const = 0;

        // Setters
        virtual void reset_state() = 0;
        virtual void set_rotation(const Math::Vec3& rotation) = 0;
        virtual void rotate(const Math::Vec3& rotation) = 0;
        virtual void rotate(const Math::Quaternion& delta) = 0;
        virtual void rotate_x(float angle) = 0;
        virtual void rotate_y(float angle) = 0;
        virtual void rotate_z(float angle) = 0;
    };
}


#endif // API__SPACE__TRANSFORMATIONS__I_ROTATABLE__HPP