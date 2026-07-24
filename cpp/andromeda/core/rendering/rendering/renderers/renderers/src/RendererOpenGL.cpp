#include "../include/RendererOpenGL.hpp"
#include "../../../OpenGL/Renderer/include/RendererOpenGLImpl.hpp"


namespace andromeda::Rendering
{
	RendererOpenGL::RendererOpenGL()
		: m_pRendererOpenGLImpl{ std::make_unique<RendererOpenGL::RendererOpenGLImpl>() }
	{
	}

	RendererOpenGL::~RendererOpenGL() = default;

	bool RendererOpenGL::is_initialized() const
	{
		return m_pRendererOpenGLImpl->is_initialized();
	}

	bool RendererOpenGL::IsGridVisible() const
	{
		return m_pRendererOpenGLImpl->IsGridVisible();
	}

	bool RendererOpenGL::IsIlluminationMode() const
	{
		return m_pRendererOpenGLImpl->IsIlluminationMode();
	}

	int RendererOpenGL::GetWidth() const
	{
		return m_pRendererOpenGLImpl->GetWidth();
	}

	int RendererOpenGL::GetHeight() const
	{
		return m_pRendererOpenGLImpl->GetHeight();
	}

	void* RendererOpenGL::GetFrameTextureHandle() const
	{
		return m_pRendererOpenGLImpl->GetFrameTextureHandle();
	}

	void RendererOpenGL::SetGridVisible(bool visible)
	{
		return m_pRendererOpenGLImpl->SetGridVisible(visible);
	}

	void RendererOpenGL::SetIlluminationMode(bool mode)
	{
		m_pRendererOpenGLImpl->SetIlluminationMode(mode);
	}

	void RendererOpenGL::init(int width, int height, bool illuminationMode)
	{
		m_pRendererOpenGLImpl->init(width, height, illuminationMode);
	}

	void RendererOpenGL::de_init()
	{
		m_pRendererOpenGLImpl->de_init();
	}

	void RendererOpenGL::render_frame(IScene& scene)
	{
		m_pRendererOpenGLImpl->render_frame(scene);
	}

	void RendererOpenGL::Resize(int width, int height)
	{
		m_pRendererOpenGLImpl->Resize(width, height);
	}
}
