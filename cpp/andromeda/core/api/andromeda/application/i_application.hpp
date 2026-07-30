#ifndef API__APPLICATION__I_APPLICATION__HPP
#define API__APPLICATION__I_APPLICATION__HPP


#include "../components/graphics_backend.hpp"
#include "../macro_exports/macro_exports.hpp"
#include "../renderer/i_renderer.hpp"
#include "../space/scene/i_scene.hpp"

#include <memory>


namespace andromeda
{
    /// @brief Defines the interface for an Andromeda application.
    ///
    /// An application is responsible for initializing the graphics backend,
    /// managing the active scene, providing access to the renderer, and
    /// executing the main application loop.
    class IApplication
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IApplication() = default;

        /// @brief Retrieves the application's renderer.
        ///
        /// @return Pointer to the renderer instance.
        virtual IRenderer* get_renderer() = 0;

        /// @brief Initializes the application.
        ///
        /// Creates the application window, initializes the selected graphics
        /// backend, and prepares all required resources.
        ///
        /// @param width Width of the application window in pixels.
        /// @param height Height of the application window in pixels.
        /// @param title Title displayed in the application window.
        /// @return `true` if initialization succeeded; otherwise, `false`.
        virtual bool init(unsigned int width, unsigned int height, const std::string& title) = 0;

        /// @brief Shuts down the application.
        ///
        /// Releases all resources allocated during initialization and performs
        /// any required cleanup.
        virtual void de_init() = 0;

        /// @brief Sets the active scene.
        ///
        /// The application does not take ownership of the provided scene unless
        /// specified by the concrete implementation.
        ///
        /// @param p_scene Pointer to the scene that will become active.
        virtual void set_scene(IScene* p_scene) = 0;

        /// @brief Executes the application's main loop.
        ///
        /// Runs until the application is requested to exit.
        ///
        /// @return Application exit code.
        virtual int run() = 0;
    };

    /// @brief Creates an application instance for the specified graphics backend.
    ///
    /// @param graphics_backend Graphics backend implementation to use.
    /// @return A unique pointer to the created application instance.
    ANDROMEDA_API std::unique_ptr<IApplication> create_app(const GraphicsBackend& graphics_backend);
}

#endif // API__APPLICATION__I_APPLICATION__HPP
