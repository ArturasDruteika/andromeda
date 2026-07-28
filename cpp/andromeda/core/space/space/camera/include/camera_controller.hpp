#ifndef SPACE__CAMERA__CAMERA_CONTROLLER__HPP
#define SPACE__CAMERA__CAMERA_CONTROLLER__HPP


#include "camera_view.hpp"
#include "../../macro_exports/include/macro_exports.hpp"
#include "math/linear_algebra/include/quaternions.hpp"
#include "andromeda/space/camera/i_camera_controller.hpp"


namespace andromeda::space
{
	class SPACE_API CameraController
		: public virtual ICameraController
		, public CameraView
	{
	public:
		CameraController(
			const math::Vec3& position,
			const math::Vec3& target_coords = math::Vec3(0.0f, 0.0f, 0.0f)
		);

		~CameraController();

		void rotate(float yaw, float pitch, float roll) override;
		void zoom(float delta_distance) override;

		// void set_on_distance_change(OnDistanceChange callback) override;

	private:
		void update_direction();

	protected:
		float m_distance;
		math::Quaternion m_orientation;
	};
}


#endif // SPACE__CAMERA__CAMERA_CONTROLLER__HPP