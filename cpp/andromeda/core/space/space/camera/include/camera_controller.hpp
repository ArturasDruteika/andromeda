#pragma once


#include "camera_view.hpp"
#include "../../macro_exports/include/macro_exports.hpp"
#include "math/linear_algebra/include/quaternions.hpp"
#include "andromeda/space/camera/i_camera_controller.hpp"


namespace andromeda::space
{
	/// @brief Implements camera movement and orientation controls.
	///
	/// Extends CameraView with functionality for rotating and zooming the camera
	/// while maintaining its orientation and viewing distance.
	class SPACE_API CameraController
		: public virtual ICameraController
		, public CameraView
	{
	public:
		/// @brief Constructs a camera controller.
		///
		/// @param position Initial camera position.
		/// @param target_coords Initial point the camera looks at.
		CameraController(
			const math::Vec3& position,
			const math::Vec3& target_coords = math::Vec3(0.0f, 0.0f, 0.0f)
		);

		/// @brief Destroys the camera controller.
		~CameraController();

		/// @brief Rotates the camera.
		///
		/// @param yaw Rotation around the vertical axis.
		/// @param pitch Rotation around the lateral axis.
		/// @param roll Rotation around the forward axis.
		void rotate(float yaw, float pitch, float roll) override;

		/// @brief Adjusts the camera distance from its target.
		///
		/// @param delta_distance Distance change applied to the camera.
		void zoom(float delta_distance) override;

		// void set_on_distance_change(OnDistanceChange callback) override;

	private:
		/// @brief Recomputes the camera direction vectors.
		void update_direction();

	protected:
		/// @brief Distance from the camera to its target.
		float m_distance;

		/// @brief Camera orientation represented as a quaternion.
		math::Quaternion m_orientation;
	};
}
