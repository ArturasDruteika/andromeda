#pragma once


#include "../macro_exports/macro_exports.hpp"
#include "../components/graphics_backend.hpp"
#include "../renderer/i_renderer.hpp"
#include "../space/scene/i_scene.hpp"
#include "../window/events/i_event.hpp"

#include <memory>


namespace andromeda
{
    /// @brief Defines the interface for the engine core.
    ///
    /// The engine manages the selected graphics backend, owns the renderer,
    /// processes application events, and controls initialization and shutdown
    /// of engine subsystems.
    class IEngine
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IEngine() = default;

        /// @brief Checks whether the engine has been successfully initialized.
        ///
        /// @return `true` if the engine is initialized; otherwise, `false`.
        virtual bool is_initialized() const = 0;

        /// @brief Retrieves the graphics backend used by the engine.
        ///
        /// @return The active graphics backend.
        virtual GraphicsBackend get_graphics_backend() const = 0;

        /// @brief Retrieves the engine's renderer.
        ///
        /// @return Pointer to the renderer instance.
        virtual IRenderer* get_renderer() const = 0;

        /// @brief Initializes the engine.
        ///
        /// Initializes all required engine subsystems and prepares the selected
        /// graphics backend for use.
        ///
        /// @return `true` if initialization succeeded; otherwise, `false`.
        virtual bool init() = 0;

        /// @brief Shuts down the engine.
        ///
        /// Releases all resources allocated during initialization and performs
        /// any necessary cleanup.
        virtual void de_init() = 0;

        /// @brief Handles an engine event.
        ///
        /// @param event Event to process.
        virtual void on_event(IEvent& event) = 0;
    };

    /// @brief Creates an engine instance for the specified graphics backend.
    ///
    /// @param graphics_backend Graphics backend to initialize.
    /// @return A unique pointer to the created engine instance.
    ANDROMEDA_API std::unique_ptr<IEngine> create_engine(const GraphicsBackend& graphics_backend);
}
