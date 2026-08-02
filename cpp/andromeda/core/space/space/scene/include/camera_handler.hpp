#ifndef SPACE__SCENE__CAMERA_HANDLER__HPP
#define SPACE__SCENE__CAMERA_HANDLER__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/scene/i_camera_handler.hpp"


namespace andromeda::space
{
	// Forward declaration
	class Camera;


	/// @brief Manages the active camera for a scene.
	///
	/// Stores and provides access to the camera currently used for rendering.
	class SPACE_API CameraHandler
		: public virtual ICameraHandler
	{
	public:
		/// @brief Constructs a camera handler.
		CameraHandler();

		/// @brief Destroys the camera handler.
		~CameraHandler() override;

		/// @brief Retrieves the active camera.
		///
		/// @return Pointer to the active camera, or `nullptr` if no camera is assigned.
		ICamera* get_active_camera() const override;

		/// @brief Sets the active camera.
		///
		/// @param camera Pointer to the camera to use as the active camera.
		void set_active_camera(ICamera* camera) override;

	protected:
		/// @brief Pointer to the active camera.
		Camera* m_p_camera;
	};
}


#endif // API_CAMERA_HANDLER__I_CAMERA_HANDLER__HPP