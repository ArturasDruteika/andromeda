#ifndef RENDERING__SHADERS__SUPPORT__SHADER_OPEN_GL_TYPES__HPP
#define RENDERING__SHADERS__SUPPORT__SHADER_OPEN_GL_TYPES__HPP


#include "pch.hpp"


namespace andromeda::rendering
{
	enum class ShaderOpenGLTypes
	{
		RenderableObjects,
		RenderableObjectsLuminous,
		RenderableObjectsNonLuminous,
		ShadowMap,
		ShadowMapTest,
		PointShadowCubeMap,
		Grid,
		Text
	};

	struct ShaderDefinition
	{
		ShaderOpenGLTypes type;
		std::filesystem::path vertex_path{};
		std::filesystem::path fragment_path{};
		std::filesystem::path geometry_path{};
	};
}


#endif // RENDERING__SHADERS__SUPPORT__SHADER_OPEN_GL_TYPES__HPP