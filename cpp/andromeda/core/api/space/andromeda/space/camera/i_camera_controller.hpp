#pragma once


#include "i_camera_view.hpp"
//#include <functional>


namespace andromeda
{
    //using OnDistanceChange = std::function<void(float)>;

    /// @brief Defines the interface for controlling a camera.
    ///
    /// Extends the camera view interface with operations for modifying the
    /// camera orientation and zoom level.
    class ICameraController
        : public virtual ICameraView
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ICameraController() = default;

        /// @brief Rotates the camera.
        ///
        /// Applies the specified rotation offsets to the camera orientation.
        ///
        /// @param yaw Rotation around the vertical axis, in degrees.
        /// @param pitch Rotation around the lateral axis, in degrees.
        /// @param roll Rotation around the forward axis, in degrees.
        virtual void rotate(float yaw, float pitch, float roll) = 0;

        /// @brief Adjusts the camera zoom level.
        ///
        /// Changes the camera distance by the specified amount.
        ///
        /// @param delta_distance Distance offset to apply.
        virtual void zoom(float delta_distance) = 0;

        // Observer for distance (zoom) changes.
        //virtual void SetOnDistanceChange(OnDistanceChange callback) = 0;
    };
}
