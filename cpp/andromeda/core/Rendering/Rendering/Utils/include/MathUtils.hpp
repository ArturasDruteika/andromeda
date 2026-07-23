#ifndef RENDERING__MATH_UTLS__HPP
#define RENDERING__MATH_UTLS__HPP


#include "math/LinearAlgebra/include/linear_algebra_data_types.hpp"
#include <glm/glm.hpp>


namespace andromeda::Rendering
{
	class mathUtils
	{
	public:
		static glm::vec2 ToGLM(const math::Vec2& vec);
		static math::Vec2 FromGLM(const glm::vec2& glmVec);
		static glm::vec3 ToGLM(const math::Vec3& vec);
		static math::Vec3 FromGLM(const glm::vec3& glmVec);
		static glm::vec4 ToGLM(const math::Vec4& vec);
		static math::Vec4 FromGLM(const glm::vec4& glmVec);
		static glm::mat2 ToGLM(const math::Mat2& mat);
		static math::Mat2 FromGLM(const glm::mat2& glmMat);
		static glm::mat3 ToGLM(const math::Mat3& mat);
		static math::Mat3 FromGLM(const glm::mat3& glmMat);
		static glm::mat4 ToGLM(const math::Mat4& mat);
		static math::Mat4 FromGLM(const glm::mat4& glmMat);
	};
}


#endif // RENDERING__MATH_UTLS__HPP