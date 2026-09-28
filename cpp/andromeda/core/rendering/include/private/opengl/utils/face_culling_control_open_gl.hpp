#pragma once


namespace andromeda::rendering
{
	/// @brief Controls OpenGL face-culling state.
	///
	/// Provides functions for enabling and disabling face culling and for
	/// querying the currently tracked culling configuration.
	class FaceCullingControlOpenGL
	{
	public:
		/// @brief Constructs a face-culling controller.
		FaceCullingControlOpenGL();

		/// @brief Destroys the face-culling controller.
		~FaceCullingControlOpenGL();

		// Getters

		/// @brief Checks whether face culling is enabled.
		///
		/// @return `true` if face culling is enabled; otherwise, `false`.
		bool is_face_culling_enabled() const;

		/// @brief Checks whether back-face culling is enabled.
		///
		/// @return `true` if back-face culling is enabled; otherwise, `false`.
		bool is_back_face_culling_enabled() const;

		/// @brief Enables OpenGL face culling.
		///
		/// @param face Face selection passed to the OpenGL culling configuration.
		/// @param winding Front-face winding order passed to OpenGL.
		void enable_face_culling(unsigned int face, unsigned int winding) const;

		/// @brief Disables OpenGL face culling.
		void disable_face_culling() const;

	protected:
		/// @brief Indicates whether face culling is currently enabled.
		mutable bool m_is_face_culling_enabled;

		/// @brief Indicates whether back-face culling is currently enabled.
		mutable bool m_is_back_face_culling_enabled;
	};
}
