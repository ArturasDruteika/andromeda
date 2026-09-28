#pragma once


namespace andromeda::rendering
{
	/// @brief Identifies the supported OpenGL shader stages.
	enum class ShaderType
	{
		/// @brief Vertex shader stage.
		Vertex,

		/// @brief Fragment shader stage.
		Fragment,

		/// @brief Geometry shader stage.
		Geometry
	};
}
