#pragma once


#include "linear_algebra_data_types.hpp"
#include "../../macro_exports/include/macro_exports.hpp"


namespace andromeda::math
{
    /// @brief Represents a quaternion.
    ///
    /// A quaternion is commonly used to represent 3D rotations without
    /// suffering from gimbal lock.
    struct Quaternion
    {
        /// @brief Scalar component.
        float w;

        /// @brief X component of the vector part.
        float x;

        /// @brief Y component of the vector part.
        float y;

        /// @brief Z component of the vector part.
        float z;

        /// @brief Constructs the identity quaternion.
        Quaternion()
            : w(1.0f)
            , x(0.0f)
            , y(0.0f)
            , z(0.0f)
        {
        }

        /// @brief Constructs a quaternion from its components.
        ///
        /// @param w_ Scalar component.
        /// @param x_ X component.
        /// @param y_ Y component.
        /// @param z_ Z component.
        Quaternion(float w_, float x_, float y_, float z_)
            : w(w_)
            , x(x_)
            , y(y_)
            , z(z_)
        {
        }

        /// @brief Returns the identity quaternion.
        ///
        /// @return Identity quaternion.
        static Quaternion identity()
        {
            return Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
        }
    };

    /// @brief Provides quaternion utility functions.
    ///
    /// Contains static operations for constructing, manipulating, interpolating,
    /// and converting quaternions.
    class MATH_API QuaternionOps
    {
    public:
        // Construction

        /// @brief Returns the identity quaternion.
        static Quaternion identity();

        /// @brief Creates a quaternion from an axis-angle rotation.
        ///
        /// @param axis Rotation axis.
        /// @param angle_radians Rotation angle in radians.
        /// @return Resulting quaternion.
        static Quaternion from_axis_angle(const Vec3& axis, float angle_radians);

        // Basic properties

        /// @brief Computes the length of a quaternion.
        static float length(const Quaternion& q);

        /// @brief Computes the squared length of a quaternion.
        static float length_squared(const Quaternion& q);

        // Unary ops

        /// @brief Returns the normalized quaternion.
        ///
        /// If the quaternion length is less than `epsilon`, the original
        /// quaternion is returned.
        static Quaternion normalize(const Quaternion& q, float epsilon = 1e-6f);

        /// @brief Returns the conjugate of a quaternion.
        static Quaternion conjugate(const Quaternion& q);

        /// @brief Returns the inverse of a quaternion.
        static Quaternion inverse(const Quaternion& q, float epsilon = 1e-6f);

        // Arithmetic

        /// @brief Multiplies two quaternions.
        static Quaternion multiply(const Quaternion& a, const Quaternion& b);

        /// @brief Adds two quaternions.
        static Quaternion add(const Quaternion& a, const Quaternion& b);

        /// @brief Subtracts one quaternion from another.
        static Quaternion sub(const Quaternion& a, const Quaternion& b);

        // Dot

        /// @brief Computes the dot product of two quaternions.
        static float dot(const Quaternion& a, const Quaternion& b);

        // Spherical linear interpolation, t in [0, 1]

        /// @brief Performs spherical linear interpolation between two quaternions.
        ///
        /// @param a Starting quaternion.
        /// @param b Ending quaternion.
        /// @param t Interpolation factor in the range `[0, 1]`.
        /// @param epsilon Tolerance used for numerical stability.
        /// @return Interpolated quaternion.
        static Quaternion slerp(const Quaternion& a, const Quaternion& b, float t, float epsilon = 1e-6f);

        // Rotate a vector by a quaternion (q * v * q^-1)

        /// @brief Rotates a 3D vector using a quaternion.
        static Vec3 rotate_vector(const Quaternion& q, const Vec3& v);

		// Create a quaternion representing a rotation of angleRadians around axis

        /// @brief Creates a quaternion representing a rotation around an axis.
        static Quaternion angle_axis(float angle_radians, const Vec3& axis);

		// Rotate vector v by quaternion q

        /// @brief Rotates a 3D vector using a quaternion.
        static Vec3 rotate(const Quaternion& q, const Vec3& v);

        // Conversion

        /// @brief Creates a quaternion from XYZ Euler angles.
        static Quaternion from_euler_xyz(float x_radians, float y_radians, float z_radians);

        /// @brief Converts a quaternion to XYZ Euler angles.
        static Vec3 to_euler_xyz(const Quaternion& q);

        /// @brief Converts a quaternion to a 4×4 rotation matrix.
        static Mat4 to_mat4(const Quaternion& q);
    };
}
