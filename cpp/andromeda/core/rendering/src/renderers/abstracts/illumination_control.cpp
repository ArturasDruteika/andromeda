#include "../include/illumination_control.hpp"


namespace andromeda::rendering
{
	IlluminationControl::IlluminationControl()
		: m_is_illumination_mode{ false }
	{
	}

	IlluminationControl::~IlluminationControl() = default;

	bool IlluminationControl::is_illumination_mode() const
	{
		return m_is_illumination_mode;
	}

	void IlluminationControl::set_illumination_mode(bool mode)
	{
		m_is_illumination_mode = mode;
	}
}