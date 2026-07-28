#include "../include/translatable.hpp"
#include "math/linear_algebra/include/linear_algebra_operations.hpp"


namespace andromeda
{
	Translatable::Translatable()
		: m_state_changed{ false }
		, m_position{ 0.0f }
		, m_translation_matrix{}
	{
	}

	Translatable::Translatable(const math::Vec3& position)
		: m_state_changed{ false }
		, m_position{ position }
	{
		update_translation_matrix();
	}

	Translatable::~Translatable() = default;

	bool Translatable::state_changed() const
	{
		return m_state_changed;
	}

	const math::Vec3& Translatable::get_position() const
	{
		return m_position;
	}

	const math::Mat4& Translatable::get_translation_matrix() const
	{
		return m_translation_matrix;
	}

	void Translatable::reset_state()
	{
		m_state_changed = false;
	}

	void Translatable::set_position(const math::Vec3& position)
	{
		m_position = position;
		update_translation_matrix();
		m_state_changed = true;
	}

	void Translatable::translate(const math::Vec3& translation)
	{
		m_position += translation;
		update_translation_matrix();
		m_state_changed = true;
	}

	void Translatable::update_translation_matrix()
	{
		m_translation_matrix = math::LinAlgOps::translate(m_position);
	}
}