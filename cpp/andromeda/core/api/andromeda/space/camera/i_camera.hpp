#ifndef API__CAMERA__I_CAMERA__HPP
#define API__CAMERA__I_CAMERA__HPP


#include "i_camera_controller.hpp"
#include "i_camera_view.hpp"


namespace Andromeda
{
    class ICamera
        : public virtual ICameraController
		, public virtual IPerspectiveControl
    {
    public:
        virtual ~ICamera() = default;
    };
}


#endif // API__CAMERA__I_CAMERA__HPP