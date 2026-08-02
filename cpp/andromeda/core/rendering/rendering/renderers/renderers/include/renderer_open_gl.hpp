#ifndef RENDERER__OPEN_GL_RENDERER__HPP
#define RENDERER__OPEN_GL_RENDERER__HPP


#include "../../../macro_exports/include/macro_exports.hpp"
#include "andromeda/renderer/i_renderer.hpp"
#include "andromeda/space/scene/i_scene.hpp"
#include "pch.hpp"


namespace andromeda::rendering
{
	/// @brief OpenGL implementation of the renderer interface.
	///
	/// Provides rendering of scenes using the OpenGL graphics API. The public
	/// interface delegates its implementation to an internal renderer object.
	class RENDERING_API RendererOpenGL
		: public IRenderer
	{
	public:
		/// @brief Constructs an OpenGL renderer.
		RendererOpenGL();

		/// @brief Destroys the OpenGL renderer.
		~RendererOpenGL();

		RendererOpenGL(const RendererOpenGL& other) = delete;
		RendererOpenGL& operator=(const RendererOpenGL& other) = delete;
		RendererOpenGL(RendererOpenGL&& other) noexcept = delete;
		RendererOpenGL& operator=(RendererOpenGL&& other) noexcept = delete;

		// Getters

		/// @brief Checks whether the renderer has been initialized.
		///
		/// @return `true` if the renderer is initialized; otherwise, `false`.
		bool is_initialized() const override;

		/// @brief Checks whether the scene grid is visible.
		///
		/// @return `true` if the grid is visible; otherwise, `false`.
		bool is_grid_visible() const override;

		/// @brief Checks whether illumination mode is enabled.
		///
		/// @return `true` if illumination mode is enabled; otherwise, `false`.
		bool is_illumination_mode() const override;

		/// @brief Retrieves the render target width.
		///
		/// @return Render width in pixels.
		int get_width() const override;

		/// @brief Retrieves the render target height.
		///
		/// @return Render height in pixels.
		int get_height() const override;

		/// @brief Retrieves the rendered frame texture handle.
		///
		/// @return Backend-specific frame texture handle.
		void* get_frame_texture_handle() const override;

		// Setters

		/// @brief Sets the visibility of the scene grid.
		///
		/// @param visible `true` to display the grid; otherwise, `false`.
		void set_grid_visible(bool visible) override;

		/// @brief Enables or disables illumination mode.
		///
		/// @param mode `true` to enable illumination; otherwise, `false`.
		void set_illumination_mode(bool mode) override;

		/// @brief Initializes the renderer.
		///
		/// @param width Initial render target width in pixels.
		/// @param height Initial render target height in pixels.
		/// @param illumination_mode Initial illumination mode.
		void init(int width, int height, bool illumination_mode = false) override;

		/// @brief Deinitializes the renderer and releases its resources.
		void de_init() override;

		/// @brief Renders a frame for the specified scene.
		///
		/// @param scene Scene to render.
		void render_frame(IScene& scene) override;

		/// @brief Resizes the renderer output.
		///
		/// @param width New render target width in pixels.
		/// @param height New render target height in pixels.
		void resize(int width, int height) override;

	private:
		/// @brief Internal renderer implementation.
		class RendererOpenGLImpl;

		/// @brief Pointer to the internal renderer implementation.
		std::unique_ptr<RendererOpenGLImpl> m_p_renderer_open_gl_impl;
	};
}


#endif // RENDERER__OPEN_GL_RENDERER__HPP