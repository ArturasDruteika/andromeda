#include "../include/Translatable.hpp"
#include "math/linear_algebra/include/linear_algebra_operations.hpp"


namespace andromeda
{
	Translatable::Translatable()
		: m_stateChanged{ false }
		, m_position{ 0.0f }
		, m_translationMatrix{}
	{
	}

	Translatable::Translatable(const math::Vec3& position)
		: m_stateChanged{ false }
		, m_position{ position }
	{
		UpdateTranslationMatrix();
	}

	Translatable::~Translatable() = default;

	bool Translatable::StateChanged() const
	{
		return m_stateChanged;
	}

	const math::Vec3& Translatable::GetPosition() const
	{
		return m_position;
	}

	const math::Mat4& Translatable::GetTranslationMatrix() const
	{
		return m_translationMatrix;
	}

	void Translatable::ResetState()
	{
		m_stateChanged = false;
	}

	void Translatable::SetPosition(const math::Vec3& position)
	{
		m_position = position;
		UpdateTranslationMatrix();
		m_stateChanged = true;
	}

	void Translatable::Translate(const math::Vec3& translation)
	{
		m_position += translation;
		UpdateTranslationMatrix();
		m_stateChanged = true;
	}

	void Translatable::UpdateTranslationMatrix()
	{
		m_translationMatrix = math::LinAlgOps::Translate(m_position);
	}
}