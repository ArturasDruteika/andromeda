#include "../include/size_control.hpp"
#include "spdlog/spdlog.h"


namespace andromeda::rendering
{
	SizeControl::SizeControl(int width, int height)
		: m_width{ width }
		, m_height{ height }
	{
	}

	SizeControl::~SizeControl() = default;

	int SizeControl::get_width() const
	{
		return m_width;
	}

	int SizeControl::get_height() const
	{
		return m_height;
	}

	void SizeControl::resize(int width, int height)
	{
		if (width <= 0 || height <= 0)
		{
			spdlog::error("Invalid dimensions for resizing: {}x{}", width, height);
			return;
		}

		m_width = width;
		m_height = height;
	}
}