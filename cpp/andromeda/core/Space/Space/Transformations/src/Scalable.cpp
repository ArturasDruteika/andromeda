#include "../include/Scalable.hpp"
#include "math/linear_algebra/include/linear_algebra_operations.hpp"


namespace andromeda
{
	Scalable::Scalable()
		: m_stateChanged{ false}
		, m_scale{ 1.0f }
		, m_scaleMatrix{}
	{
	}

	Scalable::~Scalable() = default;

	bool Scalable::StateChanged() const
	{
		return m_stateChanged;
	}

	const math::Vec3& Scalable::GetScale() const
	{
		return m_scale;
	}

	const math::Mat4& Scalable::GetScaleMatrix() const
	{
		return m_scaleMatrix;
	}

	void Scalable::ResetState()
	{
		m_stateChanged = false;
	}

	void Scalable::SetScale(const math::Vec3& scale)
	{
		m_scale = scale;
		UpdateScaleMatrix();
		m_stateChanged = true;
	}

	void Scalable::Scale(const math::Vec3& scale)
	{
		m_scale = scale;
		UpdateScaleMatrix();
		m_stateChanged = true;
	}

	void Scalable::Scale(float uniformScale)
	{
		m_scale = math::Vec3{ uniformScale };
		UpdateScaleMatrix();
		m_stateChanged = true;
	}

	void Scalable::UpdateScaleMatrix()
	{
		m_scaleMatrix = math::LinAlgOps::Scale(math::Mat4(), m_scale);
	}
}