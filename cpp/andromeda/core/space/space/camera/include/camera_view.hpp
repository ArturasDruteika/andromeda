#ifndef SPACE__CAMERA__CAMERA_VIEW__HPP
#define SPACE__CAMERA__CAMERA_VIEW__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/camera/i_camera_view.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda::space
{
	class SPACE_API CameraView
		: public virtual ICameraView
	{
	public:
		CameraView(
			const math::Vec3& position,
			const math::Vec3& target_coords = math::Vec3(0.0f, 0.0f, 0.0f)
		);

		~CameraView() override;

		// Getters
		const math::Vec3& get_position() const override;
		const math::Vec3& get_target_coords() const override;
		const math::Vec3& get_forward() const override;
		const math::Vec3& get_right() const override;
		const math::Vec3& get_up() const override;
		const math::Mat4& get_view_matrix() const override;

		// Setters
		void set_position(const math::Vec3& position);
		void set_target_coords(const math::Vec3& target_coords);

	protected:
		void calculate_view_matrix();
		void update_view_matrix();

	protected:
		math::Vec3 m_position;
		math::Vec3 m_target_coords;
		math::Vec3 m_forward;
		math::Vec3 m_right;
		math::Vec3 m_up;
		math::Mat4 m_view_matrix;
	};
}


#endif // SPACE__CAMERA__CAMERA_VIEW__HPP