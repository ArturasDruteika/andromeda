#ifndef RENDERING__CAMERA__HPP
#define RENDERING__CAMERA__HPP


#include "PerspectiveControl.hpp"
#include "CameraController.hpp"
#include "../../MacroExports/include/MacroExports.hpp"
#include "andromeda/space/camera/i_camera.hpp"
#include "math/Constants/include/constants.hpp"


namespace andromeda::Space
{
    class SPACE_API Camera
        : public ICamera
        , public PerspectiveControl
        , public CameraController
    {
    public:
        Camera();
        Camera(const math::Vec3& position, float yawRadians = -math::PI_HALF, float pitchRadians = 0.0f);
        ~Camera();

        //void SetOnDistanceChange(OnDistanceChange callback);

    //private:
        //OnDistanceChange m_onDistanceChangeCallback;
    };
}


#endif // RENDERING__CAMERA__HPP