#include "../include/camera.hpp"


constexpr andromeda::math::Vec3 DEFAULT_CAMERA_POSITION = { 10.0f, 10.0f , 10.0f };


namespace andromeda::space
{
    Camera::Camera()
        : Camera(DEFAULT_CAMERA_POSITION, -math::PI_HALF, 0.0f)
    {
    }

    Camera::Camera(
        const math::Vec3& position,
        float yaw_radians,
        float pitch_radians
    )
        : PerspectiveControl(45.0f, 0.1f, 1000.0f, 1.0f)
        , CameraController(position)
    {
    }

    Camera::~Camera() = default;

  //  void Camera::zoom(float delta_distance)
  //  {
        //CameraController::zoom(delta_distance);
  //      //m_on_distance_change_callback(m_distance);
  //  }

 //   void Camera::set_on_distance_change(OnDistanceChange callback)
 //   {
 //       m_on_distance_change_callback = std::move(callback);
    //}
}