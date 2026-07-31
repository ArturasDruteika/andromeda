#ifndef RENDERER__GRID_CONTROL__HPP
#define RENDERER__GRID_CONTROL__HPP


#include "andromeda/space/colors/colors.hpp"


namespace andromeda::rendering
{
	/// @brief Controls grid rendering settings.
	///
	/// Stores the configuration used to render the scene grid, including its
	/// visibility, dimensions, line width, and color.
	class GridControl
	{
	public:
		/// @brief Constructs a grid controller.
		GridControl();

		/// @brief Destroys the grid controller.
		~GridControl();

		// Getters

		/// @brief Checks whether the grid is visible.
		///
		/// @return `true` if the grid is visible; otherwise, `false`.
		bool is_grid_visible() const;

		/// @brief Retrieves the grid size.
		///
		/// @return Grid size.
		float get_grid_size() const;

		/// @brief Retrieves the spacing between grid lines.
		///
		/// @return Grid line spacing.
		float get_grid_spacing() const;

		/// @brief Retrieves the grid line width.
		///
		/// @return Grid line width.
		float get_grid_line_width() const;

		/// @brief Retrieves the grid line color.
		///
		/// @return Grid color.
		const Color& get_grid_color() const;

		// Setters

		/// @brief Sets the grid visibility.
		///
		/// @param visible `true` to show the grid; otherwise, `false`.
		void set_grid_visible(bool visible);

		/// @brief Sets the grid size.
		///
		/// @param size New grid size.
		void set_grid_size(float size);

		/// @brief Sets the spacing between grid lines.
		///
		/// @param spacing New grid spacing.
		void set_grid_spacing(float spacing);

		/// @brief Sets the grid line width.
		///
		/// @param line_width New line width.
		void set_grid_line_width(float line_width);

		/// @brief Sets the grid line color.
		///
		/// @param color New grid color.
		void set_grid_color(const Color& color);

	protected:
		/// @brief Indicates whether the grid is visible.
		bool m_is_grid_visible;

		/// @brief Size of the grid.
		float m_grid_size;

		/// @brief Spacing between grid lines.
		float m_grid_spacing;

		/// @brief Width of the grid lines.
		float m_grid_line_width;

		/// @brief Color of the grid lines.
		Color m_grid_color;
	};
}


#endif // RENDERER__GRID_CONTROL__HPP