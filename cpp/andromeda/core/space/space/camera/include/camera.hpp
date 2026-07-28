#ifndef SPACE__CAMERA__CAMERA__HPP
#define SPACE__CAMERA__CAMERA__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "camera_controller.hpp"
#include "perspective_control.hpp"

#include "andromeda/space/camera/i_camera.hpp"
#include "math/constants/include/constants.hpp"


namespace andromeda::space
{
    class SPACE_API Camera
        : public ICamera
        , public PerspectiveControl
        , public CameraController
    {
    public:
        Camera();

        Camera(
            const math::Vec3& position,
            float yaw_radians = -math::PI_HALF,
            float pitch_radians = 0.0f
        );

        ~Camera() override;

        // void set_on_distance_change(OnDistanceChange callback);

    private:
        // OnDistanceChange m_on_distance_change_callback;
    };
}


#endif // SPACE__CAMERA__CAMERA__HPP