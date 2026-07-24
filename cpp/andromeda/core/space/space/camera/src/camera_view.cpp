#include "../include/CameraView.hpp"
#include "math/linear_algebra/include/linear_algebra_operations.hpp"


namespace andromeda::Space
{
	CameraView::CameraView(const math::Vec3& position, const math::Vec3& targetCoords)
		: m_position{ position }
		, m_targetCoords{ targetCoords }
		, m_forward{ math::LinAlgOps::Normalize(m_targetCoords - m_position) }
		, m_right{ math::LinAlgOps::Normalize(math::LinAlgOps::Cross(m_forward, math::Vec3(0.0f, 1.0f, 0.0f))) }
		, m_up{ math::LinAlgOps::Cross(m_right, m_forward) }
	{
		CalculateViewMatrix();
	}

	CameraView::~CameraView() = default;

	const math::Vec3& CameraView::GetPosition() const
	{
		return m_position;
	}

	const math::Vec3& CameraView::GetTargetCoords() const
	{
		return m_targetCoords;
	}

	const math::Vec3& CameraView::GetForward() const
	{
		return m_forward;
	}

	const math::Vec3& CameraView::GetRight() const
	{
		return m_right;
	}

	const math::Vec3& CameraView::GetUp() const
	{
		return m_up;
	}

	const math::Mat4& CameraView::GetViewMatrix() const
	{
		return m_viewMat;
	}

	void CameraView::SetPosition(const math::Vec3& position)
	{
		m_position = position;
		CalculateViewMatrix();
	}

	void CameraView::SetTargetCoords(const math::Vec3& targetCoords)
	{
		m_targetCoords = targetCoords;
		CalculateViewMatrix();
	}

	void CameraView::CalculateViewMatrix()
	{
		m_viewMat = math::LinAlgOps::LookAt(m_position, m_targetCoords, m_up);
	}
}
