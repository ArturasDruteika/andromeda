#ifndef SPACE__CAMERA__CAMERA_VIEW__HPP
#define SPACE__CAMERA__CAMERA_VIEW__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"
#include "andromeda/space/camera/i_camera_view.hpp"


namespace andromeda::Space
{
	class SPACE_API CameraView
		: public virtual ICameraView
	{
	public:
		CameraView(const math::Vec3& position, const math::Vec3& targetCoords = math::Vec3(0.0f, 0.0f, 0.0f));
		~CameraView();

		const math::Vec3& GetPosition() const override;
		const math::Vec3& GetTargetCoords() const override;
		const math::Vec3& GetForward() const override;
		const math::Vec3& GetRight() const override;
		const math::Vec3& GetUp() const override;
		const math::Mat4& GetViewMatrix() const override;
		// Setters
		void SetPosition(const math::Vec3& position);
		void SetTargetCoords(const math::Vec3& targetCoords);

	protected:
		void CalculateViewMatrix();

	protected:
		math::Vec3 m_position;
		math::Vec3 m_targetCoords;
		math::Vec3 m_forward;
		math::Vec3 m_right;
		math::Vec3 m_up;
		math::Mat4 m_viewMat;
	};
}


#endif // SPACE__CAMERA__CAMERA_VIEW__HPP