#ifndef API__RENDERER__I_SIZE__HPP
#define API__RENDERER__I_SIZE__HPP


namespace andromeda
{
    /// @brief Defines the interface for controlling renderer dimensions.
    ///
    /// This interface provides access to the current render target size and
    /// allows it to be resized when the viewport or output dimensions change.
    class ISizeControl
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ISizeControl() = default;

        // Getters

        /// @brief Retrieves the current render target width.
        ///
        /// @return Width in pixels.
        virtual int get_width() const = 0;

        /// @brief Retrieves the current render target height.
        ///
        /// @return Height in pixels.
        virtual int get_height() const = 0;

        /// @brief Resizes the render target.
        ///
        /// @param width New width in pixels.
        /// @param height New height in pixels.
        virtual void resize(int width, int height) = 0;
    };
}


#endif // API__RENDERER__I_SIZE__HPP