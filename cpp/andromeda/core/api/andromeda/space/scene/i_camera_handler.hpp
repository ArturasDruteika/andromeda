#ifndef API__CAMERA_HANDLER__I_CAMERA_HANDLER__HPP
#define API__CAMERA_HANDLER__I_CAMERA_HANDLER__HPP


#include "../camera/i_camera.hpp"


namespace andromeda
{
	class ICameraHandler
	{
	public:
		virtual ~ICameraHandler() = default;

		// Getters
		virtual ICamera* get_active_camera() const = 0;
		// Setters
		virtual void set_active_camera(ICamera* camera) = 0;
	};
}


#endif // API_CAMERA_HANDLER__I_CAMERA_HANDLER__HPP