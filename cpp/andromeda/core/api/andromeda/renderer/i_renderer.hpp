#pragma once


#include "i_grid_control.hpp"
#include "i_illumination_control.hpp"
#include "i_size_control.hpp"
#include "../space/scene/i_scene.hpp"
#include "../macro_exports/macro_exports.hpp"
#include "../components/graphics_backend.hpp"


namespace andromeda
{
    /// @brief Defines the interface for a renderer.
    ///
    /// A renderer is responsible for initializing graphics resources, rendering
    /// scenes, managing the output framebuffer, and exposing rendering controls
    /// such as grid visibility, illumination mode, and viewport size.
    class IRenderer
        : public IGridControl
        , public IIlluminationControl
        , public ISizeControl
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IRenderer() = default;

        // Getters

        /// @brief Checks whether the renderer has been initialized.
        ///
        /// @return `true` if the renderer is initialized; otherwise, `false`.
        virtual bool is_initialized() const = 0;

        /// @brief Retrieves the native handle of the rendered frame texture.
        ///
        /// The returned handle is backend-specific and may be used by external
        /// systems, such as UI frameworks, to display the rendered image.
        ///
        /// @return Pointer to the native texture handle.
        virtual void* get_frame_texture_handle() const = 0;

        /// @brief Initializes the renderer.
        ///
        /// Allocates rendering resources and prepares the renderer for drawing.
        ///
        /// @param width Initial render target width in pixels.
        /// @param height Initial render target height in pixels.
        /// @param illumination_mode Initial illumination mode.
        virtual void init(int width, int height, bool illumination_mode = false) = 0;

        /// @brief Shuts down the renderer.
        ///
        /// Releases all rendering resources allocated during initialization.
        virtual void de_init() = 0;

        /// @brief Renders a frame for the specified scene.
        ///
        /// @param scene Scene to render.
        virtual void render_frame(IScene& scene) = 0;
    };

    // TODO: Consider dropping or implementing this function
    // /// @brief Creates a renderer for the specified graphics backend.
    // ///
    // /// @param graphics_backend Graphics backend to use.
    // /// @return A unique pointer to the created renderer instance.
    // ANDROMEDA_API std::unique_ptr<IRenderer> create_renderer(const GraphicsBackend& graphics_backend);
}
