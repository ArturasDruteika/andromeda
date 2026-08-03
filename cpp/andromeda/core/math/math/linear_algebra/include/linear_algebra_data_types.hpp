#pragma once


#include <array>


namespace andromeda::math
{
    /// @brief Represents a two-dimensional floating-point vector.
    struct Vec2
    {
        /// @brief Stores the vector components.
        std::array<float, 2> data;

        /// @brief Constructs a zero vector.
        constexpr Vec2()
            : data{ 0.0f, 0.0f }
        {
        }

        /// @brief Constructs the vec2 with all vector components set to the same value.
        /// @param value Value assigned to each element.
        constexpr Vec2(float value)
            : data{ value, value }
        {
        }

        /// @brief Constructs the vec2 from individual components.
        /// @param x X component.
        /// @param y Y component.
        constexpr Vec2(float x, float y)
            : data{ x, y }
        {
        }

        /// @brief Copy constructor.
        /// @param other Vec2 to copy.
        constexpr Vec2(const Vec2& other)
            : data{ other.data[0], other.data[1] }
        {
        }

        /// @brief Provides mutable access to an element.
        /// @param index Zero-based element index.
        /// @return Reference to the requested element.
        float& operator[](int index)
        {
            return data[index];
        }

        /// @brief Provides read-only access to an element.
        /// @param index Zero-based element index.
        /// @return Constant reference to the requested element.
        constexpr const float& operator[](int index) const
        {
            return data[index];
        }

        /// @brief Adds another vec2 to this vec2.
        /// @param other Vec2 to add.
        /// @return Reference to this vec2.
        Vec2& operator+=(const Vec2& other)
        {
            data[0] += other[0];
            data[1] += other[1];
            return *this;
        }

        /// @brief Subtracts another vec2 from this vec2.
        /// @param other Vec2 to subtract.
        /// @return Reference to this vec2.
        Vec2& operator-=(const Vec2& other)
        {
            data[0] -= other[0];
            data[1] -= other[1];
            return *this;
        }

        /// @brief Adds two vec2 values.
        /// @param lhs Left-hand vec2.
        /// @param rhs Right-hand vec2.
        /// @return Sum of the two vec2 values.
        friend Vec2 operator+(Vec2 lhs, const Vec2& rhs)
        {
            return lhs += rhs;
        }

        /// @brief Subtracts one vec2 from another.
        /// @param lhs Left-hand vec2.
        /// @param rhs Right-hand vec2.
        /// @return Difference between the two vec2 values.
        friend Vec2 operator-(Vec2 lhs, const Vec2& rhs)
        {
            return lhs -= rhs;
        }

        /// @brief Compares two vec2 values for equality.
        /// @param other Vec2 to compare.
        /// @return `true` if all elements are equal; otherwise, `false`.
        bool operator==(const Vec2& other) const
        {
            return data[0] == other.data[0] && data[1] == other.data[1];
        }

        /// @brief Compares two vec2 values for inequality.
        /// @param other Vec2 to compare.
        /// @return `true` if any element differs; otherwise, `false`.
        bool operator!=(const Vec2& other) const
        {
            return !(*this == other);
        }

        /// @brief Returns the number of floating-point elements in the vector.
        /// @return Number of floating-point elements.
        static constexpr int size()
        {
            return sizeof(Vec2) / sizeof(float);
        }
    };

    /// @brief Represents a three-dimensional floating-point vector.
    struct Vec3
    {
        /// @brief Stores the vector components.
        std::array<float, 3> data;

        /// @brief Constructs a zero vector.
        constexpr Vec3()
            : data{ 0.0f, 0.0f, 0.0f }
        {
        }

        /// @brief Constructs the vec3 with all vector components set to the same value.
        /// @param value Value assigned to each element.
        constexpr Vec3(float value)
            : data{ value, value, value }
        {
        }

        /// @brief Constructs the vec3 from individual components.
        /// @param x X component.
        /// @param y Y component.
        /// @param z Z component.
        constexpr Vec3(float x, float y, float z)
            : data{ x, y, z }
        {
        }

        /// @brief Copy constructor.
        /// @param other Vec3 to copy.
        constexpr Vec3(const Vec3& other)
            : data{ other.data[0], other.data[1], other.data[2] }
        {
        }

        /// @brief Provides mutable access to an element.
        /// @param index Zero-based element index.
        /// @return Reference to the requested element.
        float& operator[](int index)
        {
            return data[index];
        }

                /// @brief Provides read-only access to an element.
        /// @param index Zero-based element index.
        /// @return Constant reference to the requested element.
        constexpr const float& operator[](int index) const
        {
            return data[index];
        }

        /// @brief Adds another vec3 to this vec3.
        /// @param other Vec3 to add.
        /// @return Reference to this vec3.
        Vec3& operator+=(const Vec3& other)
        {
            data[0] += other[0];
            data[1] += other[1];
            data[2] += other[2];
            return *this;
        }

        /// @brief Subtracts another vec3 from this vec3.
        /// @param other Vec3 to subtract.
        /// @return Reference to this vec3.
        Vec3& operator-=(const Vec3& other)
        {
            data[0] -= other[0];
            data[1] -= other[1];
            data[2] -= other[2];
            return *this;
        }

        /// @brief Adds two vec3 values.
        /// @param lhs Left-hand vec3.
        /// @param rhs Right-hand vec3.
        /// @return Sum of the two vec3 values.
        friend Vec3 operator+(Vec3 lhs, const Vec3& rhs)
        {
            return lhs += rhs;
        }

        /// @brief Subtracts one vec3 from another.
        /// @param lhs Left-hand vec3.
        /// @param rhs Right-hand vec3.
        /// @return Difference between the two vec3 values.
        friend Vec3 operator-(Vec3 lhs, const Vec3& rhs)
        {
            return lhs -= rhs;
        }

        /// @brief Compares two vec3 values for equality.
        /// @param other Vec3 to compare.
        /// @return `true` if all elements are equal; otherwise, `false`.
        bool operator==(const Vec3& other) const
        {
            return data[0] == other.data[0] &&
                data[1] == other.data[1] &&
                data[2] == other.data[2];
        }

        /// @brief Compares two vec3 values for inequality.
        /// @param other Vec3 to compare.
        /// @return `true` if any element differs; otherwise, `false`.
        bool operator!=(const Vec3& other) const
        {
            return !(*this == other);
        }

        /// @brief Returns the number of floating-point elements in the vector.
        /// @return Number of floating-point elements.
        static constexpr int size()
        {
            return sizeof(Vec3) / sizeof(float);
        }
    };

    /// @brief Represents a four-dimensional floating-point vector.
    struct Vec4
    {
        /// @brief Stores the vector components.
        std::array<float, 4> data;

        /// @brief Constructs a zero vector.
        constexpr Vec4()
            : data{ 0.0f, 0.0f, 0.0f, 0.0f }
        {
        }

        /// @brief Constructs the vec4 with all vector components set to the same value.
        /// @param value Value assigned to each element.
        constexpr Vec4(float value)
            : data{ value, value, value, value }
        {
        }

        /// @brief Constructs the vec4 from individual components.
        /// @param x X component.
        /// @param y Y component.
        /// @param z Z component.
        /// @param w W component.
        constexpr Vec4(float x, float y, float z, float w)
            : data{ x, y, z, w }
        {
        }

        /// @brief Copy constructor.
        /// @param other Vec4 to copy.
        constexpr Vec4(const Vec4& other)
            : data{ other.data[0], other.data[1], other.data[2], other.data[3] }
        {
        }

        /// @brief Provides mutable access to an element.
        /// @param index Zero-based element index.
        /// @return Reference to the requested element.
        float& operator[](int index)
        {
            return data[index];
        }

        /// @brief Provides read-only access to an element.
        /// @param index Zero-based element index.
        /// @return Constant reference to the requested element.
        constexpr const float& operator[](int index) const
        {
            return data[index];
        }

        /// @brief Adds another vec4 to this vec4.
        /// @param other Vec4 to add.
        /// @return Reference to this vec4.
        Vec4& operator+=(const Vec4& other)
        {
            data[0] += other[0];
            data[1] += other[1];
            data[2] += other[2];
            data[3] += other[3];
            return *this;
        }

        /// @brief Subtracts another vec4 from this vec4.
        /// @param other Vec4 to subtract.
        /// @return Reference to this vec4.
        Vec4& operator-=(const Vec4& other)
        {
            data[0] -= other[0];
            data[1] -= other[1];
            data[2] -= other[2];
            data[3] -= other[3];
            return *this;
        }

        /// @brief Adds two vec4 values.
        /// @param lhs Left-hand vec4.
        /// @param rhs Right-hand vec4.
        /// @return Sum of the two vec4 values.
        friend Vec4 operator+(Vec4 lhs, const Vec4& rhs)
        {
            return lhs += rhs;
        }

        /// @brief Subtracts one vec4 from another.
        /// @param lhs Left-hand vec4.
        /// @param rhs Right-hand vec4.

        /// @return Difference between the two vec4 values.
        friend Vec4 operator-(Vec4 lhs, const Vec4& rhs)
        {
            return lhs -= rhs;
        }

        /// @brief Compares two vec4 values for equality.
        /// @param other Vec4 to compare.
        /// @return `true` if all elements are equal; otherwise, `false`.
        bool operator==(const Vec4& other) const
        {
            return data[0] == other.data[0] &&
                data[1] == other.data[1] &&
                data[2] == other.data[2] &&
                data[3] == other.data[3];
        }

        /// @brief Compares two vec4 values for inequality.
        /// @param other Vec4 to compare.
        /// @return `true` if any element differs; otherwise, `false`.
        bool operator!=(const Vec4& other) const
        {
            return !(*this == other);
        }

        /// @brief Returns the number of floating-point elements in the vector.
        /// @return Number of floating-point elements.
        static constexpr int size()
        {
            return sizeof(Vec4) / sizeof(float);
        }
    };

    /// @brief Represents a 2x2 floating-point matrix.
    struct Mat2
    {
        /// @brief Stores the matrix rows.
        std::array<Vec2, 2> data;

        /// @brief Constructs an identity matrix.
        constexpr Mat2()
            : data{
                Vec2(1.0f, 0.0f),
                Vec2(0.0f, 1.0f)
            }
        {
        }

        /// @brief Constructs the mat2 with all matrix elements set to the same value.
        /// @param value Value assigned to each element.
        constexpr Mat2(float value)
            : data{ Vec2(value), Vec2(value) }
        {
        }

        /// @brief Constructs the mat2 from row vectors.
        /// @param row0 Matrix row.
        /// @param row1 Matrix row.
        constexpr Mat2(const Vec2& row0, const Vec2& row1)
            : data{ row0, row1 }
        {
        }

        /// @brief Copy constructor.
        /// @param other Mat2 to copy.
        constexpr Mat2(const Mat2& other)
            : data{ other.data[0], other.data[1] }
        {
        }

        /// @brief Provides mutable access to an element.
        /// @param index Zero-based element index.
        /// @return Reference to the requested element.
        Vec2& operator[](int index)
        {
            return data[index];
        }

        /// @brief Provides read-only access to an element.
        /// @param index Zero-based element index.
        /// @return Constant reference to the requested element.
        constexpr const Vec2& operator[](int index) const
        {
            return data[index];
        }

        /// @brief Compares two mat2 values for equality.
        /// @param other Mat2 to compare.
        /// @return `true` if all elements are equal; otherwise, `false`.
        bool operator==(const Mat2& other) const
        {
            return data[0] == other.data[0] && data[1] == other.data[1];
        }

        /// @brief Compares two mat2 values for inequality.
        /// @param other Mat2 to compare.
        /// @return `true` if any element differs; otherwise, `false`.
        bool operator!=(const Mat2& other) const
        {
            return !(*this == other);
        }

        /// @brief Returns the number of floating-point elements in the matrix.
        /// @return Number of floating-point elements.
        static constexpr int size()
        {
            return sizeof(Mat2) / sizeof(float);
        }
    };

    /// @brief Represents a 3x3 floating-point matrix.
    struct Mat3
    {
        /// @brief Stores the matrix rows.
        std::array<Vec3, 3> data;

        /// @brief Constructs an identity matrix.
        constexpr Mat3()
            : data{
                Vec3(1.0f, 0.0f, 0.0f),
                Vec3(0.0f, 1.0f, 0.0f),
                Vec3(0.0f, 0.0f, 1.0f)
            }
        {
        }

        /// @brief Constructs the mat3 with all matrix elements set to the same value.
        /// @param value Value assigned to each element.
        constexpr Mat3(float value)
            : data{ Vec3(value), Vec3(value), Vec3(value) }
        {
        }

        /// @brief Constructs the mat3 from row vectors.
        /// @param row0 Matrix row.
        /// @param row1 Matrix row.
        /// @param row2 Matrix row.
        constexpr Mat3(const Vec3& row0, const Vec3& row1, const Vec3& row2)
            : data{ row0, row1, row2 }
        {
        }

        /// @brief Copy constructor.
        /// @param other Mat3 to copy.
        constexpr Mat3(const Mat3& other)
            : data{ other.data[0], other.data[1], other.data[2] }
        {
        }

        /// @brief Provides mutable access to an element.
        /// @param index Zero-based element index.
        /// @return Reference to the requested element.
        Vec3& operator[](int index)
        {
            return data[index];
        }

        /// @brief Provides read-only access to an element.
        /// @param index Zero-based element index.
        /// @return Constant reference to the requested element.
        constexpr const Vec3& operator[](int index) const
        {
            return data[index];
        }

        /// @brief Compares two mat3 values for equality.
        /// @param other Mat3 to compare.
        /// @return `true` if all elements are equal; otherwise, `false`.
        bool operator==(const Mat3& other) const
        {
            return data[0] == other.data[0] &&
                data[1] == other.data[1] &&
                data[2] == other.data[2];
        }

        /// @brief Compares two mat3 values for inequality.
        /// @param other Mat3 to compare.
        /// @return `true` if any element differs; otherwise, `false`.
        bool operator!=(const Mat3& other) const
        {
            return !(*this == other);
        }

        /// @brief Returns the number of floating-point elements in the matrix.
        /// @return Number of floating-point elements.
        static constexpr int size()
        {
            return sizeof(Mat3) / sizeof(float);
        }
    };

    /// @brief Represents a 4x4 floating-point matrix.
    struct Mat4
    {
        /// @brief Stores the matrix rows.
        std::array<Vec4, 4> data;

        /// @brief Constructs an identity matrix.
        constexpr Mat4()
            : data{
                Vec4(1.0f, 0.0f, 0.0f, 0.0f),
                Vec4(0.0f, 1.0f, 0.0f, 0.0f),
                Vec4(0.0f, 0.0f, 1.0f, 0.0f),
                Vec4(0.0f, 0.0f, 0.0f, 1.0f)
            }
        {
        }

        /// @brief Constructs the mat4 with all matrix elements set to the same value.
        /// @param value Value assigned to each element.
        constexpr Mat4(float value)
            : data{ Vec4(value), Vec4(value), Vec4(value), Vec4(value) }
        {
        }

        /// @brief Constructs the mat4 from row vectors.
        /// @param row0 Matrix row.
        /// @param row1 Matrix row.
        /// @param row2 Matrix row.
        /// @param row3 Matrix row.
        constexpr Mat4(const Vec4& row0, const Vec4& row1, const Vec4& row2, const Vec4& row3)
            : data{ row0, row1, row2, row3 }
        {
        }

        /// @brief Copy constructor.
        /// @param other Mat4 to copy.
        constexpr Mat4(const Mat4& other)
            : data{ other.data[0], other.data[1], other.data[2], other.data[3] }
        {
        }

        /// @brief Provides mutable access to an element.
        /// @param index Zero-based element index.
        /// @return Reference to the requested element.
        Vec4& operator[](int index)
        {
            return data[index];
        }

        /// @brief Provides read-only access to an element.
        /// @param index Zero-based element index.
        /// @return Constant reference to the requested element.
        constexpr const Vec4& operator[](int index) const
        {
            return data[index];
        }

        /// @brief Compares two mat4 values for equality.
        /// @param other Mat4 to compare.
        /// @return `true` if all elements are equal; otherwise, `false`.
        bool operator==(const Mat4& other) const
        {
            return data[0] == other.data[0] &&
                data[1] == other.data[1] &&
                data[2] == other.data[2] &&
                data[3] == other.data[3];
        }

        /// @brief Compares two mat4 values for inequality.
        /// @param other Mat4 to compare.
        /// @return `true` if any element differs; otherwise, `false`.
        bool operator!=(const Mat4& other) const
        {
            return !(*this == other);
        }

        /// @brief Returns the number of floating-point elements in the matrix.
        /// @return Number of floating-point elements.
        static constexpr int size()
        {
            return sizeof(Mat4) / sizeof(float);
        }
    };

    // ============================================================
    // VECTOR * SCALAR
    // ============================================================

    /// @brief Multiplies a vec2 by a scalar.
    /// @param v Vec2 to multiply.
    /// @param s Scalar multiplier.
    /// @return Scaled vec2.
    inline Vec2 operator*(const Vec2& v, float s)
    {
        return Vec2(v[0] * s, v[1] * s);
    }

    /// @brief Multiplies a vec3 by a scalar.
    /// @param v Vec3 to multiply.
    /// @param s Scalar multiplier.
    /// @return Scaled vec3.
    inline Vec3 operator*(const Vec3& v, float s)
    {
        return Vec3(v[0] * s, v[1] * s, v[2] * s);
    }

    /// @brief Multiplies a vec4 by a scalar.
    /// @param v Vec4 to multiply.
    /// @param s Scalar multiplier.
    /// @return Scaled vec4.
    inline Vec4 operator*(const Vec4& v, float s)
    {
        return Vec4(v[0] * s, v[1] * s, v[2] * s, v[3] * s);
    }

    /// @brief Multiplies a scalar by a vector.
    /// @param s Scalar multiplier.
    /// @param v Vec2 to multiply.
    /// @return Scaled vec2.
    inline Vec2 operator*(float s, const Vec2& v)
    {
        return v * s;
    }

    /// @brief Multiplies a scalar by a vector.
    /// @param s Scalar multiplier.
    /// @param v Vec3 to multiply.
    /// @return Scaled vec3.
    inline Vec3 operator*(float s, const Vec3& v)
    {
        return v * s;
    }

    /// @brief Multiplies a scalar by a vector.
    /// @param s Scalar multiplier.
    /// @param v Vec4 to multiply.
    /// @return Scaled vec4.
    inline Vec4 operator*(float s, const Vec4& v)
    {
        return v * s;
    }

    // ============================================================
    // MATRIX * VECTOR
    // ============================================================

    /// @brief Multiplies a mat2 by a vec2.
    /// @param m Mat2 operand.
    /// @param v Vec2 operand.
    /// @return Transformed vec2.
    inline Vec2 operator*(const Mat2& m, const Vec2& v)
    {
        return Vec2(
            m[0][0] * v[0] + m[0][1] * v[1],
            m[1][0] * v[0] + m[1][1] * v[1]
        );
    }

    /// @brief Multiplies a mat3 by a vec3.
    /// @param m Mat3 operand.
    /// @param v Vec3 operand.
    /// @return Transformed vec3.
    inline Vec3 operator*(const Mat3& m, const Vec3& v)
    {
        return Vec3(
            m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2],
            m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2],
            m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2]
        );
    }

    /// @brief Multiplies a mat4 by a vec4.
    /// @param m Mat4 operand.
    /// @param v Vec4 operand.
    /// @return Transformed vec4.
    inline Vec4 operator*(const Mat4& m, const Vec4& v)
    {
        return Vec4(
            m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2] + m[0][3] * v[3],
            m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2] + m[1][3] * v[3],
            m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2] + m[2][3] * v[3],
            m[3][0] * v[0] + m[3][1] * v[1] + m[3][2] * v[2] + m[3][3] * v[3]
        );
    }

    // ============================================================
    // MATRIX * MATRIX
    // ============================================================

    /// @brief Multiplies two mat2 values.
    /// @param a Left-hand mat2.
    /// @param b Right-hand mat2.
    /// @return Product of the two mat2 values.
    inline Mat2 operator*(const Mat2& a, const Mat2& b)
    {
        Mat2 result;

        for (int r = 0; r < 2; ++r)
        {
            for (int c = 0; c < 2; ++c)
            {
                float sum =
                    a[r][0] * b[0][c] +
                    a[r][1] * b[1][c];

                result[r][c] = sum;
            }
        }

        return result;
    }

    /// @brief Multiplies two mat3 values.
    /// @param a Left-hand mat3.
    /// @param b Right-hand mat3.
    /// @return Product of the two mat3 values.
    inline Mat3 operator*(const Mat3& a, const Mat3& b)
    {
        Mat3 result;

        for (int r = 0; r < 3; ++r)
        {
            for (int c = 0; c < 3; ++c)
            {
                float sum =
                    a[r][0] * b[0][c] +
                    a[r][1] * b[1][c] +
                    a[r][2] * b[2][c];

                result[r][c] = sum;
            }
        }

        return result;
    }

    /// @brief Multiplies two mat4 values.
    /// @param a Left-hand mat4.
    /// @param b Right-hand mat4.
    /// @return Product of the two mat4 values.
    inline Mat4 operator*(const Mat4& a, const Mat4& b)
    {
        Mat4 result;

        for (int r = 0; r < 4; ++r)
        {
            for (int c = 0; c < 4; ++c)
            {
                float sum =
                    a[r][0] * b[0][c] +
                    a[r][1] * b[1][c] +
                    a[r][2] * b[2][c] +
                    a[r][3] * b[3][c];

                result[r][c] = sum;
            }
        }

        return result;
    }

    // ============================================================
    // MATRIX *= MATRIX
    // ============================================================

    /// @brief Multiplies a mat2 by another mat2 in place.
    /// @param a Mat2 to modify.
    /// @param b Mat2 multiplier.
    /// @return Reference to the modified mat2.
    inline Mat2& operator*=(Mat2& a, const Mat2& b)
    {
        a = a * b;
        return a;
    }

    /// @brief Multiplies a mat3 by another mat3 in place.
    /// @param a Mat3 to modify.
    /// @param b Mat3 multiplier.
    /// @return Reference to the modified mat3.
    inline Mat3& operator*=(Mat3& a, const Mat3& b)
    {
        a = a * b;
        return a;
    }

    /// @brief Multiplies a mat4 by another mat4 in place.
    /// @param a Mat4 to modify.
    /// @param b Mat4 multiplier.
    /// @return Reference to the modified mat4.
    inline Mat4& operator*=(Mat4& a, const Mat4& b)
    {
        a = a * b;
        return a;
    }

}
