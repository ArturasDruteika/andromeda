#ifndef MATH__MATH_OPERATIONS__HPP
#define MATH__MATH_OPERATIONS__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "../include/linear_algebra_data_types.hpp"


namespace andromeda::math
{
	/// @brief Provides common linear algebra operations for vectors and matrices.
	///
	/// Contains static utility functions for performing arithmetic,
	/// transformations, and geometric operations on vectors and matrices.
	class MATH_API LinAlgOps
	{
	public:
		// Vector-Vector Dot Products

		/// @brief Computes the dot product of two 2D vectors.
		static float dot_prod(const Vec2& a, const Vec2& b);

		/// @brief Computes the dot product of two 3D vectors.
		static float dot_prod(const Vec3& a, const Vec3& b);

		/// @brief Computes the dot product of two 4D vectors.
		static float dot_prod(const Vec4& a, const Vec4& b);

		// Vector-Matrix Multiplication

		/// @brief Multiplies a 2×2 matrix by a 2D vector.
		static Vec2 multiply(const Mat2& mat, const Vec2& vec);

		/// @brief Multiplies a 3×3 matrix by a 3D vector.
		static Vec3 multiply(const Mat3& mat, const Vec3& vec);

		/// @brief Multiplies a 4×4 matrix by a 4D vector.
		static Vec4 multiply(const Mat4& mat, const Vec4& vec);

		// Matrix-Matrix Multiplication

		/// @brief Multiplies two 2×2 matrices.
		static Mat2 multiply(const Mat2& a, const Mat2& b);

		/// @brief Multiplies two 3×3 matrices.
		static Mat3 multiply(const Mat3& a, const Mat3& b);

		/// @brief Multiplies two 4×4 matrices.
		static Mat4 multiply(const Mat4& a, const Mat4& b);

		// Length / magnitude

		/// @brief Computes the length of a 2D vector.
		static float length(const Vec2& v);

		/// @brief Computes the length of a 3D vector.
		static float length(const Vec3& v);

		/// @brief Computes the length of a 4D vector.
		static float length(const Vec4& v);

		// Normalize (returns unit vector). If length is ~0, returns the input unchanged.

		/// @brief Returns the normalized 2D vector.
		///
		/// If the vector length is less than `epsilon`, the original vector is returned.
		static Vec2 normalize(const Vec2& v, float epsilon = 1e-8f);

		/// @brief Returns the normalized 3D vector.
		///
		/// If the vector length is less than `epsilon`, the original vector is returned.
		static Vec3 normalize(const Vec3& v, float epsilon = 1e-8f);

		/// @brief Returns the normalized 4D vector.
		///
		/// If the vector length is less than `epsilon`, the original vector is returned.
		static Vec4 normalize(const Vec4& v, float epsilon = 1e-8f);

		// Cross product (3D)

		/// @brief Computes the cross product of two 3D vectors.
		static Vec3 cross(const Vec3& a, const Vec3& b);

		// Rotate vector around axis by angle (glm::rotate(vec, angle, axis))

		/// @brief Rotates a 2D vector about the origin.
		static Vec2 rotate(const Vec2& v, float angle_radians);

		/// @brief Rotates a 3D vector around the specified axis.
		static Vec3 rotate(const Vec3& v, float angle_radians, const Vec3& axis);

		/// @brief Rotates a 4D vector around the specified axis.
		static Vec4 rotate(const Vec4& v, float angle_radians, const Vec3& axis);

		/// @brief Applies a rotation to a transformation matrix.
		static Mat4 rotate(const Mat4& matrix, float angle_radians, const Vec3& axis);

		// Translation

		/// @brief Creates a translation matrix.
		static Mat4 translate(const Vec3& translation);

		/// @brief Applies a translation to a transformation matrix.
		static Mat4 translate(const Mat4& matrix, const Vec3& translation);

		// Scale

		// === Vector scaling ===

		/// @brief Uniformly scales a 2D vector.
		static Vec2 scale(const Vec2& v, float s);

		/// @brief Uniformly scales a 3D vector.
		static Vec3 scale(const Vec3& v, float s);

		/// @brief Uniformly scales a 4D vector.
		static Vec4 scale(const Vec4& v, float s);

		// === Matrix uniform scaling (scalar) ===

		/// @brief Uniformly scales a 2×2 matrix.
		static Mat2 scale(const Mat2& m, float s);

		/// @brief Uniformly scales a 3×3 matrix.
		static Mat3 scale(const Mat3& m, float s);

		/// @brief Uniformly scales a 4×4 matrix.
		static Mat4 scale(const Mat4& m, float s);

		// === Matrix non-uniform scaling (per-axis) ===

		/// @brief Applies non-uniform scaling to a 2×2 matrix.
		static Mat2 scale(const Mat2& m, const Vec2& s);   // x, y

		/// @brief Applies non-uniform scaling to a 3×3 matrix.
		static Mat3 scale(const Mat3& m, const Vec3& s);   // x, y, z

		/// @brief Applies non-uniform scaling to a 4×4 matrix.
		static Mat4 scale(const Mat4& m, const Vec3& s);   // x, y, z (TRS style)

		// Projection matrix (OpenGL-style)

		/// @brief Creates a perspective projection matrix.
		static Mat4 perspective(float fov_y_radians, float aspect, float z_near, float z_far);

		// View matrix (glm::lookAt analog, OpenGL-style RH, -Z forward, Y up)

		/// @brief Creates a right-handed view matrix using the look-at convention.
		static Mat4 look_at(const Vec3& eye, const Vec3& center, const Vec3& up);

		/// @brief Clamps a value to the specified range.
		///
		/// @tparam T Value type.
		/// @param value Value to clamp.
		/// @param min_value Minimum allowed value.
		/// @param max_value Maximum allowed value.
		/// @return Clamped value.
		template <typename T>
		static T clamp(const T& value, const T& min_value, const T& max_value)
		{
			if (value < min_value)
			{
				return min_value;
			}
			if (value > max_value)
			{
				return max_value;
			}
			return value;
		}
	};
}


#endif // MATH__MATH_OPERATIONS__HPP