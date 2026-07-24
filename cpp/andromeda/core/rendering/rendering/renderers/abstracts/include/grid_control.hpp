#ifndef RENDERER__GRID_CONTROL__HPP
#define RENDERER__GRID_CONTROL__HPP


#include "andromeda/space/colors/colors.hpp"


namespace andromeda::rendering
{
	class GridControl
	{
	public:
		GridControl();
		~GridControl();

		// Getters
		bool is_grid_visible() const;
		float get_grid_size() const;
		float get_grid_spacing() const;
		float get_grid_line_width() const;
		const Color& get_grid_color() const;

		// Setters
		void set_grid_visible(bool visible);
		void set_grid_size(float size);
		void set_grid_spacing(float spacing);
		void set_grid_line_width(float line_width);
		void set_grid_color(const Color& color);

	protected:
		bool m_is_grid_visible;      // Flag to control grid visibility
		float m_grid_size;           // Size of the grid
		float m_grid_spacing;        // Spacing between grid lines
		float m_grid_line_width;     // Width of the grid lines
		Color m_grid_color;          // Color of the grid lines
	};
}


#endif // RENDERER__GRID_CONTROL__HPP