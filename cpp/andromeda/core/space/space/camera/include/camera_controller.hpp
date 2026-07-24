#ifndef SPACE__CAMERA__CAMERA_CONTROLLER__HPP
#define SPACE__CAMERA__CAMERA_CONTROLLER__HPP


#include "CameraView.hpp"
#include "../../MacroExports/include/MacroExports.hpp"
#include "math/linear_algebra/include/quaternions.hpp"
#include "andromeda/space/camera/i_camera_controller.hpp"


namespace andromeda::Space
{
	class SPACE_API CameraController
		: public virtual ICameraController
		, public CameraView
	{
	public:
		CameraController(const math::Vec3& position, const math::Vec3& targetCoords = math::Vec3(0.0f, 0.0f, 0.0f));
		~CameraController();

		void Rotate(float yaw, float pitch, float roll) override;
		void Zoom(float deltaDistance) override;

		//void SetOnDistanceChange(OnDistanceChange callback) override;

	private:
		void UpdateDirection();

	protected:
		float m_distance;
		math::Quaternion m_orientation;
	};
}


#endif // SPACE__CAMERA__CAMERA_CONTROLLER__HPP