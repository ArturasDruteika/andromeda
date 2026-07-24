#ifndef RENDERER__FACE_CULLING_CONTROL_OPENGL__HPP
#define RENDERER__FACE_CULLING_CONTROL_OPENGL__HPP


namespace andromeda::rendering
{
	class FaceCullingControlOpenGL
	{
	public:
		FaceCullingControlOpenGL();
		~FaceCullingControlOpenGL();

		// Getters
		bool is_face_culling_enabled() const;
		bool is_back_face_culling_enabled() const;

		void enable_face_culling(unsigned int face, unsigned int winding) const;
		void disable_face_culling() const;

	protected:
		mutable bool m_is_face_culling_enabled;
		mutable bool m_is_back_face_culling_enabled;
	};
}


#endif // RENDERER__FACE_CULLING_CONTROL_OPENGL__HPP