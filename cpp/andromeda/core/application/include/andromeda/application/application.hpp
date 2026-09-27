#pragma once


#include "andromeda/components/graphics_backend.hpp"
#include "andromeda/application/i_application.hpp"
#include "andromeda/engine/i_engine.hpp"
#include "andromeda/platform/i_platform.hpp"
#include "andromeda/space/scene/i_scene.hpp"
#include "pch.hpp"


namespace andromeda::application
{
    /// @brief Default implementation of the application interface.
    ///
    /// Coordinates the platform, engine, renderer, and active scene. The
    /// application owns the platform and engine, initializes all subsystems,
    /// and executes the main render loop.
    class Application
        : public virtual IApplication
    {
    public:
        /// @brief Constructs an application for the specified graphics backend.
        ///
        /// @param graphics_backend Graphics backend to use.
        explicit Application(GraphicsBackend graphics_backend);

        /// @brief Destroys the application.
        ~Application() override;

        Application(const Application& other) = delete;
        Application& operator=(const Application& other) = delete;

        Application(Application&& other) noexcept = delete;
        Application& operator=(Application&& other) noexcept = delete;

        // Getters

        /// @brief Retrieves the application's renderer.
        ///
        /// @return Pointer to the renderer instance.
        IRenderer* get_renderer() override;

        /// @brief Initializes the application.
        ///
        /// Initializes the platform, engine, renderer, and other internal
        /// subsystems required to run the application.
        ///
        /// @param width Initial window width in pixels.
        /// @param height Initial window height in pixels.
        /// @param title Window title.
        /// @return `true` if initialization succeeded; otherwise, `false`.
        bool init(
            unsigned int width,
            unsigned int height,
            const std::string& title
        ) override;

        /// @brief Shuts down the application.
        ///
        /// Releases all owned resources and deinitializes subsystems.
        void de_init() override;

        /// @brief Sets the active scene.
        ///
        /// @param p_scene Pointer to the scene to render.
        void set_scene(IScene* p_scene) override;

        /// @brief Executes the main application loop.
        ///
        /// @return `0` on successful termination; otherwise, a non-zero error code.
        int run() override;

    private:
        /// @brief Initializes the platform subsystem.
        bool init_platform(
            unsigned int width,
            unsigned int height,
            const std::string& title
        );

        /// @brief Initializes the engine subsystem.
        bool init_engine();

        /// @brief Initializes the renderer.
        bool init_renderer(int width, int height);

        /// @brief Performs complete application initialization.
        bool init_internal(
            unsigned int width,
            unsigned int height,
            const std::string& title
        );

        /// @brief Connects platform and engine event handlers.
        void connect_events();

        /// @brief Executes the rendering loop.
        void run_render_loop();

    private:
        /// @brief Indicates whether the application has been initialized.
        bool m_initialized;

        /// @brief Selected graphics backend.
        GraphicsBackend m_graphics_backend;

        /// @brief Owned platform implementation.
        std::unique_ptr<IPlatform> m_p_platform;

        /// @brief Owned engine implementation.
        std::unique_ptr<IEngine> m_p_engine;

        /// @brief Active scene.
        IScene* m_p_scene;

        /// @brief Platform window.
        IWindow* m_p_window;

        /// @brief Graphics context.
        IGraphicsContext* m_p_context;

        /// @brief Renderer instance.
        IRenderer* m_p_renderer;
    };
}
