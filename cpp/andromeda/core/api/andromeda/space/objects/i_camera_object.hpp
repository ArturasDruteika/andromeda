#ifndef API__OBJECTS__I_CAMERA_OBJECT__HPP
#define API__OBJECTS__I_CAMERA_OBJECT__HPP


#include "i_object.hpp"


namespace andromeda
{
    /// @brief Defines the interface for a camera object.
    ///
    /// A camera object is an object that represents a camera within a scene.
    /// This interface serves as a common base for camera-specific scene objects.
    class ICameraObject
        : public virtual IObject
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ICameraObject() = default;
    };
}


#endif // API__OBJECTS__I_CAMERA_OBJECT__HPP