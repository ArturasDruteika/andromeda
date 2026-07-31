#ifndef RENDERING__SHADERS__SUPPORT__SHADER_OPEN_GL_TYPES__HPP
#define RENDERING__SHADERS__SUPPORT__SHADER_OPEN_GL_TYPES__HPP


#include "pch.hpp"


namespace andromeda::rendering
{
	/// @brief Identifies the built-in OpenGL shader programs.
	enum class ShaderOpenGLTypes
	{
		/// @brief General-purpose object rendering shader.
		RenderableObjects,

		/// @brief Shader for rendering luminous objects.
		RenderableObjectsLuminous,

		/// @brief Shader for rendering non-luminous objects.
		RenderableObjectsNonLuminous,

		/// @brief Directional shadow-map generation shader.
		ShadowMap,

		/// @brief Shader used to visualize shadow maps.
		ShadowMapTest,

		/// @brief Point-light shadow cubemap generation shader.
		PointShadowCubeMap,

		/// @brief Grid rendering shader.
		Grid,

		/// @brief Text rendering shader.
		Text
	};

	/// @brief Describes the source files required to create a shader.
	struct ShaderDefinition
	{
		/// @brief Type of shader.
		ShaderOpenGLTypes type;

		/// @brief Path to the vertex shader source file.
		std::filesystem::path vertex_path{};

		/// @brief Path to the fragment shader source file.
		std::filesystem::path fragment_path{};

		/// @brief Path to the geometry shader source file.
		std::filesystem::path geometry_path{};
	};
}


#endif // RENDERING__SHADERS__SUPPORT__SHADER_OPEN_GL_TYPES__HPP