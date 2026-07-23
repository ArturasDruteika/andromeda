#ifndef SPACE__TRANSFORMATIONS__ROTATABLE__HPP
#define SPACE__TRANSFORMATIONS__ROTATABLE__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "andromeda/space/transformations/i_rotatable.hpp"
#include "math/LinearAlgebra/include/linear_algebra_data_types.hpp"
#include "math/LinearAlgebra/include/quaternions.hpp"


namespace andromeda
{
    class SPACE_API Rotatable
        : public virtual IRotatable
    {
    public:
        Rotatable();
        ~Rotatable() override;

        // Getters
        bool StateChanged() const override;
        const math::Vec3& GetRotation() const override; // Euler radians (derived)
        const math::Mat4& GetRotationMatrix() const override;
        const math::Quaternion& GetOrientation() const override;

        // Setters
        void ResetState() override;
        void SetRotation(const math::Vec3& rotation) override;
        void Rotate(const math::Vec3& rotation) override;
        void Rotate(const math::Quaternion& delta) override;
        void RotateX(float angle) override;
        void RotateY(float angle) override;
        void RotateZ(float angle) override;

    protected:
        void UpdateRotationDerivedData();

    private:
        bool m_stateChanged;
        math::Vec3 m_rotation;
        math::Mat4 m_rotationMatrix;
        math::Quaternion m_orientation;
    };
}

#endif // SPACE__TRANSFORMATIONS__ROTATABLE__HPP
