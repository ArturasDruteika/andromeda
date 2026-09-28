#include "../include/grid_control.hpp"


namespace andromeda::rendering
{
	GridControl::GridControl()
        : m_is_grid_visible{ false }
        , m_grid_size{ 10.0f }
        , m_grid_spacing{ 1.0f }
        , m_grid_line_width{ 0.1f }
        , m_grid_color{ 1.0f, 1.0f, 1.0f, 1.0f }
	{
	}

	GridControl::~GridControl() = default;

    bool GridControl::is_grid_visible() const
    {
        return m_is_grid_visible;
    }

    float GridControl::get_grid_size() const
    {
        return m_grid_size;
    }

    float GridControl::get_grid_spacing() const
    {
        return m_grid_spacing;
    }

    float GridControl::get_grid_line_width() const
    {
        return m_grid_line_width;
    }

    const Color& GridControl::get_grid_color() const
    {
		return m_grid_color;
    }

    void GridControl::set_grid_visible(bool visible)
    {
        m_is_grid_visible = visible;
	}

    void GridControl::set_grid_size(float size)
    {
		m_grid_size = size;
    }

    void GridControl::set_grid_spacing(float spacing)
    {
		m_grid_spacing = spacing;
    }

    void GridControl::set_grid_line_width(float line_width)
    {
		m_grid_line_width = line_width;
    }

    void GridControl::set_grid_color(const Color& color)
    {
		m_grid_color = color;
    }
}