#ifndef SPACE__CAMERA__CAMERA_VIEW__HPP
#define SPACE__CAMERA__CAMERA_VIEW__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/camera/i_camera_view.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda::space
{
	/// @brief Implements camera view state and view matrix generation.
	///
	/// Stores the camera position, target, orientation vectors, and view matrix,
	/// and provides functionality for updating the view transformation.
	class SPACE_API CameraView
		: public virtual ICameraView
	{
	public:
		/// @brief Constructs a camera view.
		///
		/// @param position Initial camera position.
		/// @param target_coords Initial point the camera looks at.
		CameraView(
			const math::Vec3& position,
			const math::Vec3& target_coords = math::Vec3(0.0f, 0.0f, 0.0f)
		);

		/// @brief Destroys the camera view.
		~CameraView() override;

		// Getters

		/// @brief Retrieves the camera position.
		///
		/// @return Camera position in world space.
		const math::Vec3& get_position() const override;

		/// @brief Retrieves the camera target.
		///
		/// @return Target position in world space.
		const math::Vec3& get_target_coords() const override;

		/// @brief Retrieves the forward direction vector.
		///
		/// @return Normalized forward vector.
		const math::Vec3& get_forward() const override;

		/// @brief Retrieves the right direction vector.
		///
		/// @return Normalized right vector.
		const math::Vec3& get_right() const override;

		/// @brief Retrieves the up direction vector.
		///
		/// @return Normalized up vector.
		const math::Vec3& get_up() const override;

		/// @brief Retrieves the camera view matrix.
		///
		/// @return View transformation matrix.
		const math::Mat4& get_view_matrix() const override;

		// Setters

		/// @brief Sets the camera position.
		///
		/// @param position New camera position.
		void set_position(const math::Vec3& position);

		/// @brief Sets the camera target.
		///
		/// @param target_coords New target position.
		void set_target_coords(const math::Vec3& target_coords);

	protected:
		/// @brief Computes the camera view matrix.
		void calculate_view_matrix();

		/// @brief Updates the stored view matrix.
		void update_view_matrix();

	protected:
		/// @brief Camera position in world space.
		math::Vec3 m_position;

		/// @brief Camera target position in world space.
		math::Vec3 m_target_coords;

		/// @brief Camera forward direction.
		math::Vec3 m_forward;

		/// @brief Camera right direction.
		math::Vec3 m_right;

		/// @brief Camera up direction.
		math::Vec3 m_up;

		/// @brief Camera view transformation matrix.
		math::Mat4 m_view_matrix;
	};
}


#endif // SPACE__CAMERA__CAMERA_VIEW__HPP