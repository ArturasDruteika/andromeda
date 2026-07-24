#ifndef RENDERING__MATH_UTILS__HPP
#define RENDERING__MATH_UTILS__HPP


#include "math/linear_algebra/include/linear_algebra_data_types.hpp"
#include <glm/glm.hpp>


namespace andromeda::rendering
{
	class mathUtils
	{
	public:
		static glm::vec2 to_glm(const math::Vec2& vec);
		static math::Vec2 from_glm(const glm::vec2& glm_vec);
		static glm::vec3 to_glm(const math::Vec3& vec);
		static math::Vec3 from_glm(const glm::vec3& glm_vec);
		static glm::vec4 to_glm(const math::Vec4& vec);
		static math::Vec4 from_glm(const glm::vec4& glm_vec);
		static glm::mat2 to_glm(const math::Mat2& mat);
		static math::Mat2 from_glm(const glm::mat2& glm_mat);
		static glm::mat3 to_glm(const math::Mat3& mat);
		static math::Mat3 from_glm(const glm::mat3& glm_mat);
		static glm::mat4 to_glm(const math::Mat4& mat);
		static math::Mat4 from_glm(const glm::mat4& glm_mat);
	};
}


#endif // RENDERING__MATH_UTILS__HPP