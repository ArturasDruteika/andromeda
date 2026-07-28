#ifndef API__RENDERER__I_GRID_CONTROL__HPP
#define API__RENDERER__I_GRID_CONTROL__HPP


namespace andromeda
{
	class IGridControl
	{
	public:
		virtual ~IGridControl() = default;

		// Getters
		virtual bool is_grid_visible() const = 0;
		// Setters
		virtual void set_grid_visible(bool visible) = 0;
	};
}


#endif // API__RENDERER__I_GRID_CONTROL__HPP