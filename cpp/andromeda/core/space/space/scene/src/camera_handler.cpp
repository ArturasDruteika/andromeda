#include "../include/camera_handler.hpp"
#include "../../camera/include/camera.hpp"


namespace andromeda::space
{
    CameraHandler::CameraHandler()
        : m_p_camera{ nullptr }
    {
    }

    CameraHandler::~CameraHandler()
    {
        delete m_p_camera;
        m_p_camera = nullptr;
    }

    ICamera* CameraHandler::get_active_camera() const
    {
        return m_p_camera;
    }

    void CameraHandler::set_active_camera(ICamera* camera)
    {
        if (camera == nullptr)
        {
            delete m_p_camera;
            m_p_camera = nullptr;
            return;
        }

        // Only accept space::Camera instances.
        Camera* p_new_camera = dynamic_cast<Camera*>(camera);
        if (p_new_camera == nullptr)
        {
            // Reject unknown ICamera implementations.
            // (Keep existing camera unchanged.)
            return;
        }

        if (p_new_camera == m_p_camera)
        {
            return;
        }

        delete m_p_camera;
        m_p_camera = p_new_camera;
    }
}