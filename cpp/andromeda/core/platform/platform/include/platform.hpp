#ifndef PLATFORM__PLATFORM__PLATFORM__HPP
#define PLATFORM__PLATFORM__PLATFORM__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "pch.hpp"
#include "andromeda/components/graphics_backend.hpp"
#include "andromeda/graphics_context/i_graphics_context.hpp"
#include "andromeda/platform/i_platform.hpp"
#include "andromeda/window/window/i_window.hpp"


namespace andromeda::platform
{
    /// @brief Default implementation of the platform interface.
    ///
    /// Manages platform-specific resources, including the application window
    /// and graphics context.
    class PLATFORM_API Platform
        : public IPlatform
    {
    public:
        /// @brief Constructs a platform for the specified graphics backend.
        ///
        /// @param graphics_backend Graphics backend to use.
        Platform(const GraphicsBackend& graphics_backend);

        /// @brief Destroys the platform and releases its resources.
        ~Platform() override;

        /// @brief Checks whether the platform has been initialized.
        ///
        /// @return `true` if the platform is initialized; otherwise, `false`.
        bool is_initialized() const override;

        /// @brief Retrieves the graphics backend used by the platform.
        ///
        /// @return Active graphics backend.
        GraphicsBackend get_graphics_backend() const override;

        /// @brief Initializes the platform.
        ///
        /// Creates the application window and graphics context.
        ///
        /// @param width Initial window width in pixels.
        /// @param height Initial window height in pixels.
        /// @param title Window title.
        /// @return `true` if initialization succeeded; otherwise, `false`.
        bool init(int width, int height, const std::string& title) override;

        /// @brief Shuts down the platform.
        ///
        /// Releases the window and graphics context.
        void shutdown() override;

        /// @brief Retrieves the graphics context.
        ///
        /// @return Pointer to the graphics context.
        IGraphicsContext* get_graphics_context() const override;

        /// @brief Retrieves the application window.
        ///
        /// @return Pointer to the application window.
        IWindow* get_window() const override;

    private:
        /// @brief Creates the application window.
        ///
        /// @param width Window width in pixels.
        /// @param height Window height in pixels.
        /// @param title Window title.
        void create_window(int width, int height, const std::string& title);

        /// @brief Creates the graphics context.
        void create_graphics_context();

    private:
        /// @brief Indicates whether the platform has been initialized.
        bool m_initialized;

        /// @brief Selected graphics backend.
        GraphicsBackend m_graphics_backend;

        /// @brief Owned graphics context.
        std::unique_ptr<IGraphicsContext> m_p_graphics_context;

        /// @brief Owned application window.
        std::unique_ptr<IWindow> m_p_window;
    };
}


#endif // PLATFORM__PLATFORM__PLATFORM__HPP