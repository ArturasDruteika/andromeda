#ifndef RENDERING__MATH_UTILS__HPP
#define RENDERING__MATH_UTILS__HPP


#include "math/linear_algebra/include/linear_algebra_data_types.hpp"
#include <glm/glm.hpp>


namespace andromeda::rendering
{
	/// @brief Provides conversion utilities between engine and GLM math types.
	///
	/// Contains helper functions for converting vectors and matrices between
	/// Andromeda's math library and GLM.
	class MathUtils
	{
	public:
		/// @brief Converts a 2D vector to GLM.
		///
		/// @param vec Engine vector.
		/// @return Equivalent GLM vector.
		static glm::vec2 to_glm(const math::Vec2& vec);

		/// @brief Converts a GLM 2D vector to the engine type.
		///
		/// @param glm_vec GLM vector.
		/// @return Equivalent engine vector.
		static math::Vec2 from_glm(const glm::vec2& glm_vec);

		/// @brief Converts a 3D vector to GLM.
		///
		/// @param vec Engine vector.
		/// @return Equivalent GLM vector.
		static glm::vec3 to_glm(const math::Vec3& vec);

		/// @brief Converts a GLM 3D vector to the engine type.
		///
		/// @param glm_vec GLM vector.
		/// @return Equivalent engine vector.
		static math::Vec3 from_glm(const glm::vec3& glm_vec);

		/// @brief Converts a 4D vector to GLM.
		///
		/// @param vec Engine vector.
		/// @return Equivalent GLM vector.
		static glm::vec4 to_glm(const math::Vec4& vec);

		/// @brief Converts a GLM 4D vector to the engine type.
		///
		/// @param glm_vec GLM vector.
		/// @return Equivalent engine vector.
		static math::Vec4 from_glm(const glm::vec4& glm_vec);

		/// @brief Converts a 2×2 matrix to GLM.
		///
		/// @param mat Engine matrix.
		/// @return Equivalent GLM matrix.
		static glm::mat2 to_glm(const math::Mat2& mat);

		/// @brief Converts a GLM 2×2 matrix to the engine type.
		///
		/// @param glm_mat GLM matrix.
		/// @return Equivalent engine matrix.
		static math::Mat2 from_glm(const glm::mat2& glm_mat);

		/// @brief Converts a 3×3 matrix to GLM.
		///
		/// @param mat Engine matrix.
		/// @return Equivalent GLM matrix.
		static glm::mat3 to_glm(const math::Mat3& mat);

		/// @brief Converts a GLM 3×3 matrix to the engine type.
		///
		/// @param glm_mat GLM matrix.
		/// @return Equivalent engine matrix.
		static math::Mat3 from_glm(const glm::mat3& glm_mat);

		/// @brief Converts a 4×4 matrix to GLM.
		///
		/// @param mat Engine matrix.
		/// @return Equivalent GLM matrix.
		static glm::mat4 to_glm(const math::Mat4& mat);

		/// @brief Converts a GLM 4×4 matrix to the engine type.
		///
		/// @param glm_mat GLM matrix.
		/// @return Equivalent engine matrix.
		static math::Mat4 from_glm(const glm::mat4& glm_mat);
	};
}


#endif // RENDERING__MATH_UTILS__HPP