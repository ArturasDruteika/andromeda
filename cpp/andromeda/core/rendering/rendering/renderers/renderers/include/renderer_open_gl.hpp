#ifndef RENDERER__OPEN_GL_RENDERER__HPP
#define RENDERER__OPEN_GL_RENDERER__HPP


#include "../../../macro_exports/include/macro_exports.hpp"
#include "andromeda/renderer/i_renderer.hpp"
#include "andromeda/space/scene/i_scene.hpp"
#include "pch.hpp"


namespace andromeda::rendering
{
	class RENDERING_API RendererOpenGL
		: public IRenderer
	{
	public:
		RendererOpenGL();
		~RendererOpenGL();

		RendererOpenGL(const RendererOpenGL& other) = delete;
		RendererOpenGL& operator=(const RendererOpenGL& other) = delete;
		RendererOpenGL(RendererOpenGL&& other) noexcept = delete;
		RendererOpenGL& operator=(RendererOpenGL&& other) noexcept = delete;

		// Getters
		bool is_initialized() const override;
		bool is_grid_visible() const override;
		bool is_illumination_mode() const override;
		int get_width() const override;
		int get_height() const override;
		void* get_frame_texture_handle() const override;

		// Setters
		void set_grid_visible(bool visible) override;
		void set_illumination_mode(bool mode) override;

		void init(int width, int height, bool illumination_mode = false) override;
		void de_init() override;
		void render_frame(IScene& scene) override;
		void resize(int width, int height) override;

	private:
		class RendererOpenGLImpl;
		std::unique_ptr<RendererOpenGLImpl> m_p_renderer_open_gl_impl;
	};
}


#endif // RENDERER__OPEN_GL_RENDERER__HPP