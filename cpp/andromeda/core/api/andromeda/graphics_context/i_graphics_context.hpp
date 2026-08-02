#pragma once


#include "../window/window/i_window.hpp"


namespace andromeda
{
    /// @brief Defines the interface for a graphics context.
    ///
    /// A graphics context is responsible for initializing the underlying
    /// graphics API, associating it with a window, making it current on the
    /// calling thread, and presenting rendered frames to the display.
    class IGraphicsContext
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IGraphicsContext() = default;

        /// @brief Checks whether the graphics context has been initialized.
        ///
        /// @return `true` if the context is initialized; otherwise, `false`.
        virtual bool is_initialized() const = 0;

        /// @brief Initializes the graphics context for the specified window.
        ///
        /// @param window Window that the graphics context will be associated
        ///               with.
        /// @return `true` if initialization succeeded; otherwise, `false`.
        virtual bool init(IWindow& window) = 0;

        /// @brief Makes this graphics context current on the calling thread.
        ///
        /// Rendering commands issued after this call will use this context
        /// until another context is made current.
        virtual void make_current() = 0;

        /// @brief Presents the rendered frame to the display.
        ///
        /// Typically swaps the front and back buffers of the associated window.
        virtual void present() = 0;
    };
}
