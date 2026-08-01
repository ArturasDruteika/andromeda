#ifndef SPACE__CAMERA__PERSPECTIVE_CONTROL__HPP
#define SPACE__CAMERA__PERSPECTIVE_CONTROL__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/camera/i_perspective_control.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda::space
{
	/// @brief Implements perspective projection control.
	///
	/// Stores perspective projection parameters and maintains the projection
	/// matrix used for rendering.
	class SPACE_API PerspectiveControl
		: public virtual IPerspectiveControl
	{
	public:
		/// @brief Constructs a perspective controller using default parameters.
		PerspectiveControl();

		/// @brief Constructs a perspective controller with custom parameters.
		///
		/// @param fov_deg Vertical field of view in degrees.
		/// @param near_plane Distance to the near clipping plane.
		/// @param far_plane Distance to the far clipping plane.
		/// @param aspect Viewport aspect ratio.
		PerspectiveControl(
			float fov_deg,
			float near_plane,
			float far_plane,
			float aspect
		);

		/// @brief Destroys the perspective controller.
		~PerspectiveControl() override;

		// Getters

		/// @brief Retrieves the vertical field of view.
		///
		/// @return Field of view in degrees.
		float get_field_of_view_degrees() const override;

		/// @brief Retrieves the near clipping plane distance.
		///
		/// @return Near clipping plane distance.
		float get_near_plane() const override;

		/// @brief Retrieves the far clipping plane distance.
		///
		/// @return Far clipping plane distance.
		float get_far_plane() const override;

		/// @brief Retrieves the viewport aspect ratio.
		///
		/// @return Aspect ratio.
		float get_aspect() const override;

		/// @brief Retrieves the projection matrix.
		///
		/// @return Perspective projection matrix.
		const math::Mat4& get_projection() const override;

		// Setters

		/// @brief Sets the vertical field of view.
		///
		/// @param fov_deg Field of view in degrees.
		/// @param update_projection `true` to immediately update the projection
		/// matrix.
		void set_field_of_view_degrees(
			float fov_deg,
			bool update_projection = true
		) override;

		/// @brief Sets the near clipping plane distance.
		///
		/// @param near_plane Near clipping plane distance.
		/// @param update_projection `true` to immediately update the projection
		/// matrix.
		void set_near_plane(
			float near_plane,
			bool update_projection = true
		) override;

		/// @brief Sets the far clipping plane distance.
		///
		/// @param far_plane Far clipping plane distance.
		/// @param update_projection `true` to immediately update the projection
		/// matrix.
		void set_far_plane(
			float far_plane,
			bool update_projection = true
		) override;

		/// @brief Sets the viewport aspect ratio.
		///
		/// @param aspect Aspect ratio.
		/// @param update_projection `true` to immediately update the projection
		/// matrix.
		void set_aspect(
			float aspect,
			bool update_projection = true
		) override;

		/// @brief Recomputes the perspective projection matrix.
		void update_projection() override;

	protected:
		/// @brief Vertical field of view in degrees.
		float m_fov_deg;

		/// @brief Near clipping plane distance.
		float m_near_plane;

		/// @brief Far clipping plane distance.
		float m_far_plane;

		/// @brief Viewport aspect ratio.
		float m_aspect;

		/// @brief Perspective projection matrix.
		math::Mat4 m_projection;
	};
}


#endif // SPACE__CAMERA__PERSPECTIVE_CONTROL__HPP