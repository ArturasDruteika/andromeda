#ifndef SPACE__CAMERA__CAMERA__HPP
#define SPACE__CAMERA__CAMERA__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "camera_controller.hpp"
#include "perspective_control.hpp"

#include "andromeda/space/camera/i_camera.hpp"
#include "math/constants/include/constants.hpp"


namespace andromeda::space
{
    /// @brief Default implementation of the camera interface.
    ///
    /// Combines perspective projection and camera control functionality into a
    /// single camera object suitable for rendering a 3D scene.
    class SPACE_API Camera
        : public ICamera
        , public PerspectiveControl
        , public CameraController
    {
    public:
        /// @brief Constructs a camera using default settings.
        Camera();

        /// @brief Constructs a camera with the specified position and orientation.
        ///
        /// @param position Initial camera position.
        /// @param yaw_radians Initial yaw angle in radians.
        /// @param pitch_radians Initial pitch angle in radians.
        Camera(
            const math::Vec3& position,
            float yaw_radians = -math::PI_HALF,
            float pitch_radians = 0.0f
        );

        /// @brief Destroys the camera.
        ~Camera() override;

        // void set_on_distance_change(OnDistanceChange callback);

    private:
        // OnDistanceChange m_on_distance_change_callback;
    };
}


#endif // SPACE__CAMERA__CAMERA__HPP