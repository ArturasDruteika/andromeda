#ifndef MATH__MATH_OPERATIONS__HPP
#define MATH__MATH_OPERATIONS__HPP


#include "../../MacroExports/include/macro_exports.hpp"
#include "../include/linear_algebra_data_types.hpp"


namespace Andromeda
{
	namespace Math
	{
		class MATH_API LinAlgOps
		{
		public:
			// Vector-Vector Dot Products
			static float dot_prod(const Vec2& a, const Vec2& b);
			static float dot_prod(const Vec3& a, const Vec3& b);
			static float dot_prod(const Vec4& a, const Vec4& b);
			// Vector-Matrix Multiplication
			static Vec2 multiply(const Mat2& mat, const Vec2& vec);
			static Vec3 multiply(const Mat3& mat, const Vec3& vec);
			static Vec4 multiply(const Mat4& mat, const Vec4& vec);
			// Matrix-Matrix Multiplication
			static Mat2 multiply(const Mat2& a, const Mat2& b);
			static Mat3 multiply(const Mat3& a, const Mat3& b);
			static Mat4 multiply(const Mat4& a, const Mat4& b);

			// Length / magnitude
			static float length(const Vec2& v);
			static float length(const Vec3& v);
			static float length(const Vec4& v);

			// Normalize (returns unit vector). If length is ~0, returns the input unchanged.
			static Vec2 normalize(const Vec2& v, float epsilon = 1e-8f);
			static Vec3 normalize(const Vec3& v, float epsilon = 1e-8f);
			static Vec4 normalize(const Vec4& v, float epsilon = 1e-8f);

			// Cross product (3D)
			static Vec3 cross(const Vec3& a, const Vec3& b);

			// Rotate vector around axis by angle (glm::rotate(vec, angle, axis))
			static Vec2 rotate(const Vec2& v, float angle_radians);
			static Vec3 rotate(const Vec3& v, float angle_radians, const Vec3& axis);
			static Vec4 rotate(const Vec4& v, float angle_radians, const Vec3& axis);
			static Mat4 rotate(const Mat4& matrix, float angle_radians, const Vec3& axis);

			// Translation
			static Mat4 translate(const Vec3& translation);
			static Mat4 translate(const Mat4& matrix, const Vec3& translation);

			// Scale
			// === Vector scaling ===
			static Vec2 scale(const Vec2& v, float s);
			static Vec3 scale(const Vec3& v, float s);
			static Vec4 scale(const Vec4& v, float s);
			// === Matrix uniform scaling (scalar) ===
			static Mat2 scale(const Mat2& m, float s);
			static Mat3 scale(const Mat3& m, float s);
			static Mat4 scale(const Mat4& m, float s);
			// === Matrix non-uniform scaling (per-axis) ===
			static Mat2 scale(const Mat2& m, const Vec2& s);   // x, y
			static Mat3 scale(const Mat3& m, const Vec3& s);   // x, y, z
			static Mat4 scale(const Mat4& m, const Vec3& s);   // x, y, z (TRS style)

			// Projection matrix (OpenGL-style)
			static Mat4 perspective(float fov_y_radians, float aspect, float z_near, float z_far);

			// View matrix (glm::lookAt analog, OpenGL-style RH, -Z forward, Y up)
			static Mat4 look_at(const Vec3& eye, const Vec3& center, const Vec3& up);

			// Clamps a value between minValue and maxValue
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
}


#endif // MATH__MATH_OPERATIONS__HPP
