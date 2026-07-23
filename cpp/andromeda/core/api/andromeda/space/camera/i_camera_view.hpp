#ifndef API__CAMERA__I_CAMERA_VIEW__HPP
#define API__CAMERA__I_CAMERA_VIEW__HPP


#include "i_perspective_control.hpp"
#include "Math/LinearAlgebra/include/linear_algebra_data_types.hpp"


namespace Andromeda
{
    class ICameraView
        : public virtual IPerspectiveControl
    {
    public:
        virtual ~ICameraView() = default;

        // Getters
        virtual const Math::Vec3& get_position() const = 0;
        virtual const Math::Vec3& get_target_coords() const = 0;
        virtual const Math::Vec3& get_forward() const = 0;
        virtual const Math::Vec3& get_right() const = 0;
        virtual const Math::Vec3& get_up() const = 0;
        virtual const Math::Mat4& get_view_matrix() const = 0;
    };
}


#endif // API__CAMERA__I_CAMERA_VIEW__HPP