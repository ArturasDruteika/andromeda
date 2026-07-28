#ifndef SPACE__CAMERA__PERSPECTIVE_CONTROL__HPP
#define SPACE__CAMERA__PERSPECTIVE_CONTROL__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/camera/i_perspective_control.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda::space
{
	class SPACE_API PerspectiveControl
		: public virtual IPerspectiveControl
	{
	public:
		PerspectiveControl();

		PerspectiveControl(
			float fov_deg,
			float near_plane,
			float far_plane,
			float aspect
		);

		~PerspectiveControl() override;

		// Getters
		float get_field_of_view_degrees() const override;
		float get_near_plane() const override;
		float get_far_plane() const override;
		float get_aspect() const override;
		const math::Mat4& get_projection() const override;

		// Setters
		void set_field_of_view_degrees(
			float fov_deg,
			bool update_projection = true
		) override;

		void set_near_plane(
			float near_plane,
			bool update_projection = true
		) override;

		void set_far_plane(
			float far_plane,
			bool update_projection = true
		) override;

		void set_aspect(
			float aspect,
			bool update_projection = true
		) override;

		// Updates the projection matrix.
		void update_projection() override;

	protected:
		float m_fov_deg;
		float m_near_plane;
		float m_far_plane;
		float m_aspect;
		math::Mat4 m_projection;
	};
}


#endif // SPACE__CAMERA__PERSPECTIVE_CONTROL__HPP