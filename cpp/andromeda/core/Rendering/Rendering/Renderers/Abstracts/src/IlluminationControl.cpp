#include "../include/IlluminationControl.hpp"


namespace andromeda::Rendering
{
	IlluminationControl::IlluminationControl()
		: m_isIlluminationMode{ false }
	{
	}

	IlluminationControl::~IlluminationControl() = default;

	bool IlluminationControl::IsIlluminationMode() const
	{
		return m_isIlluminationMode;
	}

	void IlluminationControl::SetIlluminationMode(bool mode)
	{
		m_isIlluminationMode = mode;
	}
}
