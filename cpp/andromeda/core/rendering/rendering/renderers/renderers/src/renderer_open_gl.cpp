#include "../include/open_gl_renderer.hpp"
#include "../../../open_gl/renderer/include/open_gl_renderer_impl.hpp"


namespace andromeda::rendering
{
	RendererOpenGL::RendererOpenGL()
		: m_p_renderer_open_gl_impl{ std::make_unique<RendererOpenGLImpl>() }
	{
	}

	RendererOpenGL::~RendererOpenGL() = default;

	bool RendererOpenGL::is_initialized() const
	{
		return m_p_renderer_open_gl_impl->is_initialized();
	}

	bool RendererOpenGL::is_grid_visible() const
	{
		return m_p_renderer_open_gl_impl->is_grid_visible();
	}

	bool RendererOpenGL::is_illumination_mode() const
	{
		return m_p_renderer_open_gl_impl->is_illumination_mode();
	}

	int RendererOpenGL::get_width() const
	{
		return m_p_renderer_open_gl_impl->get_width();
	}

	int RendererOpenGL::get_height() const
	{
		return m_p_renderer_open_gl_impl->get_height();
	}

	void* RendererOpenGL::get_frame_texture_handle() const
	{
		return m_p_renderer_open_gl_impl->get_frame_texture_handle();
	}

	void RendererOpenGL::set_grid_visible(bool visible)
	{
		m_p_renderer_open_gl_impl->set_grid_visible(visible);
	}

	void RendererOpenGL::set_illumination_mode(bool mode)
	{
		m_p_renderer_open_gl_impl->set_illumination_mode(mode);
	}

	void RendererOpenGL::init(int width, int height, bool illumination_mode)
	{
		m_p_renderer_open_gl_impl->init(width, height, illumination_mode);
	}

	void RendererOpenGL::de_init()
	{
		m_p_renderer_open_gl_impl->de_init();
	}

	void RendererOpenGL::render_frame(IScene& scene)
	{
		m_p_renderer_open_gl_impl->render_frame(scene);
	}

	void RendererOpenGL::resize(int width, int height)
	{
		m_p_renderer_open_gl_impl->resize(width, height);
	}
}