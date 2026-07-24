#include "../include/face_culling_control_open_gl.hpp"
#include "glad/gl.h"


namespace andromeda::rendering
{
	FaceCullingControlOpenGL::FaceCullingControlOpenGL()
		: m_is_face_culling_enabled{ false }
		, m_is_back_face_culling_enabled{ false }
	{
	}

	FaceCullingControlOpenGL::~FaceCullingControlOpenGL() = default;

	bool FaceCullingControlOpenGL::is_face_culling_enabled() const
	{
		return m_is_face_culling_enabled;
	}

	bool FaceCullingControlOpenGL::is_back_face_culling_enabled() const
	{
		return m_is_back_face_culling_enabled;
	}

	void FaceCullingControlOpenGL::enable_face_culling(
		unsigned int face,
		unsigned int winding
	) const
	{
		glEnable(GL_CULL_FACE);
		glCullFace(face);
		glFrontFace(winding);

		m_is_face_culling_enabled = true;
		m_is_back_face_culling_enabled = (face == GL_BACK);
	}

	void FaceCullingControlOpenGL::disable_face_culling() const
	{
		glDisable(GL_CULL_FACE);
		glFrontFace(GL_CCW);

		m_is_face_culling_enabled = false;
		m_is_back_face_culling_enabled = false;
	}
}