#include "../include/transformable.hpp"


namespace andromeda
{
	Transformable::Transformable()
		: m_state_changed{ false }
		, m_model_matrix{ 1.0f }
	{
	}

	Transformable::Transformable(const math::Vec3& position)
		: Translatable{ position }
		, m_state_changed{ false }
	{
		update_model_matrix();
	}

	Transformable::~Transformable() = default;

	bool Transformable::state_changed() const
	{
		bool state_changed =
			m_state_changed
			|| Rotatable::state_changed()
			|| Scalable::state_changed()
			|| Translatable::state_changed();

		return state_changed;
	}

	math::Mat4 Transformable::get_model_matrix()
	{
		if (state_changed())
		{
			update_model_matrix();

			// Clear all dirty flags so subsequent calls do not rebuild again.
			m_state_changed = false;
			Rotatable::reset_state();
			Scalable::reset_state();
			Translatable::reset_state();
		}

		return m_model_matrix;
	}

	void Transformable::set_model_matrix(const math::Mat4& model_matrix)
	{
		m_model_matrix = model_matrix;
		m_state_changed = true;
	}

	void Transformable::update_model_matrix()
	{
		// Rebuild model matrix from current component matrices.
		// Order matches your existing get_model_matrix(): T * R * S
		m_model_matrix =
			Translatable::get_translation_matrix()
			* Rotatable::get_rotation_matrix()
			* Scalable::get_scale_matrix();
	}

	void Transformable::reset_state()
	{
		m_state_changed = false;
		Rotatable::reset_state();
		Scalable::reset_state();
		Translatable::reset_state();
	}
}