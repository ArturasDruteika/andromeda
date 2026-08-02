#ifndef API__RENDERER__I_GRID_CONTROL__HPP
#define API__RENDERER__I_GRID_CONTROL__HPP


namespace andromeda
{
    /// @brief Defines the interface for controlling renderer grid visualization.
    ///
    /// This interface provides access to the visibility state of the editor or
    /// debugging grid rendered by the engine.
    class IGridControl
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IGridControl() = default;

        // Getters

        /// @brief Checks whether the grid is currently visible.
        ///
        /// @return `true` if the grid is visible; otherwise, `false`.
        virtual bool is_grid_visible() const = 0;

        // Setters

        /// @brief Sets the grid visibility.
        ///
        /// @param visible `true` to display the grid; `false` to hide it.
        virtual void set_grid_visible(bool visible) = 0;
    };
}


#endif // API__RENDERER__I_GRID_CONTROL__HPP