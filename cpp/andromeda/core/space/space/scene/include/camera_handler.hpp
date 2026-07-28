#ifndef SPACE__SCENE__CAMERA_HANDLER__HPP
#define SPACE__SCENE__CAMERA_HANDLER__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/scene/i_camera_handler.hpp"


namespace andromeda::space
{
	// Forward declaration
	class Camera;


	class SPACE_API CameraHandler
		: public virtual ICameraHandler
	{
	public:
		CameraHandler();
		~CameraHandler() override;

		ICamera* get_active_camera() const override;
		void set_active_camera(ICamera* camera) override;

	protected:
		Camera* m_p_camera;
	};
}


#endif // API_CAMERA_HANDLER__I_CAMERA_HANDLER__HPP