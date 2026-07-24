#ifndef SPACE__TRANSFORMATIONS__ROTATABLE__HPP
#define SPACE__TRANSFORMATIONS__ROTATABLE__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/transformations/i_rotatable.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"
#include "math/linear_algebra/include/quaternions.hpp"


namespace andromeda
{
    class SPACE_API Rotatable
        : public virtual IRotatable
    {
    public:
        Rotatable();
        ~Rotatable() override;

        // Getters
        bool state_changed() const override;
        const math::Vec3& get_rotation() const override; // Euler radians (derived)
        const math::Mat4& get_rotation_matrix() const override;
        const math::Quaternion& get_orientation() const override;

        // Setters
        void reset_state() override;
        void set_rotation(const math::Vec3& rotation) override;
        void rotate(const math::Vec3& rotation) override;
        void rotate(const math::Quaternion& delta) override;
        void rotate_x(float angle) override;
        void rotate_y(float angle) override;
        void rotate_z(float angle) override;

    protected:
        void update_rotation_derived_data();

    private:
        bool m_state_changed;
        math::Vec3 m_rotation;
        math::Mat4 m_rotation_matrix;
        math::Quaternion m_orientation;
    };
}

#endif // SPACE__TRANSFORMATIONS__ROTATABLE__HPP