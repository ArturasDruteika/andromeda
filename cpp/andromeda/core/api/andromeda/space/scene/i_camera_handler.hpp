#pragma once


#include "../camera/i_camera.hpp"


namespace andromeda
{
    /// @brief Defines the interface for managing the active camera.
    ///
    /// A camera handler maintains the currently active camera used for
    /// rendering a scene.
    class ICameraHandler
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ICameraHandler() = default;

        // Getters

        /// @brief Retrieves the active camera.
        ///
        /// @return Pointer to the active camera, or `nullptr` if no camera is active.
        virtual ICamera* get_active_camera() const = 0;

        // Setters

        /// @brief Sets the active camera.
        ///
        /// @param camera Pointer to the camera that will become active, or
        ///               `nullptr` to clear the active camera.
        virtual void set_active_camera(ICamera* camera) = 0;
    };
}
