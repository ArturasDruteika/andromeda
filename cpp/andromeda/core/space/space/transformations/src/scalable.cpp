#include "../include/scalable.hpp"
#include "math/linear_algebra/include/linear_algebra_operations.hpp"


namespace andromeda
{
	Scalable::Scalable()
		: m_state_changed{ false }
		, m_scale{ 1.0f }
		, m_scale_matrix{}
	{
	}

	Scalable::~Scalable() = default;

	bool Scalable::state_changed() const
	{
		return m_state_changed;
	}

	const math::Vec3& Scalable::get_scale() const
	{
		return m_scale;
	}

	const math::Mat4& Scalable::get_scale_matrix() const
	{
		return m_scale_matrix;
	}

	void Scalable::reset_state()
	{
		m_state_changed = false;
	}

	void Scalable::set_scale(const math::Vec3& scale)
	{
		m_scale = scale;
		update_scale_matrix();
		m_state_changed = true;
	}

	void Scalable::scale(const math::Vec3& scale)
	{
		m_scale = scale;
		update_scale_matrix();
		m_state_changed = true;
	}

	void Scalable::scale(float uniform_scale)
	{
		m_scale = math::Vec3{ uniform_scale };
		update_scale_matrix();
		m_state_changed = true;
	}

	void Scalable::update_scale_matrix()
	{
		m_scale_matrix = math::LinAlgOps::scale(math::Mat4(), m_scale);
	}
}