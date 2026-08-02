#ifndef API__CAMERA__I_CAMERA__HPP
#define API__CAMERA__I_CAMERA__HPP


#include "i_camera_controller.hpp"
#include "i_camera_view.hpp"


namespace andromeda
{
    /// @brief Defines the complete camera interface.
    ///
    /// Combines camera view access, camera control, and perspective control
    /// into a single interface representing a fully configurable camera.
    class ICamera
        : public virtual ICameraController
        , public virtual IPerspectiveControl
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ICamera() = default;
    };
}


#endif // API__CAMERA__I_CAMERA__HPP