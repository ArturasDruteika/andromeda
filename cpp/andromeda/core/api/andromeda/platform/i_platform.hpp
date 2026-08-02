#ifndef API__PLATFORM__I_PLATFORM__HPP
#define API__PLATFORM__I_PLATFORM__HPP


#include "../macro_exports/macro_exports.hpp"
#include "../components/graphics_backend.hpp"
#include "../graphics_context/i_graphics_context.hpp"
#include "../window/window/i_window.hpp"

#include <memory>
#include <string>


namespace andromeda
{
    /// @brief Defines the interface for a platform implementation.
    ///
    /// A platform is responsible for creating and managing the application
    /// window and graphics context for a specific graphics backend. It also
    /// handles platform-specific initialization and shutdown.
    class IPlatform
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IPlatform() = default;

        /// @brief Checks whether the platform has been initialized.
        ///
        /// @return `true` if the platform is initialized; otherwise, `false`.
        virtual bool is_initialized() const = 0;

        /// @brief Retrieves the graphics backend used by the platform.
        ///
        /// @return The active graphics backend.
        virtual GraphicsBackend get_graphics_backend() const = 0;

        /// @brief Initializes the platform.
        ///
        /// Creates the application window and initializes the graphics context
        /// for the selected graphics backend.
        ///
        /// @param width Width of the application window in pixels.
        /// @param height Height of the application window in pixels.
        /// @param title Title displayed in the application window.
        /// @return `true` if initialization succeeded; otherwise, `false`.
        virtual bool init(int width, int height, const std::string& title) = 0;

        /// @brief Shuts down the platform.
        ///
        /// Releases all platform-specific resources, including the window and
        /// graphics context.
        virtual void shutdown() = 0;

        /// @brief Retrieves the platform's graphics context.
        ///
        /// @return Pointer to the graphics context.
        virtual IGraphicsContext* get_graphics_context() const = 0;

        /// @brief Retrieves the application window.
        ///
        /// @return Pointer to the window.
        virtual IWindow* get_window() const = 0;
    };

    /// @brief Creates a platform instance for the specified graphics backend.
    ///
    /// @param graphics_backend Graphics backend to use.
    /// @return A unique pointer to the created platform instance.
    ANDROMEDA_API std::unique_ptr<IPlatform> create_platform(const GraphicsBackend& graphics_backend);
}


#endif // API__PLATFORM__I_PLATFORM__HPP