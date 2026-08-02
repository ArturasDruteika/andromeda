#pragma once


#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda
{
    /// @brief Represents an RGBA color.
    ///
    /// Stores red, green, blue, and alpha components as normalized floating-
    /// point values in the range `[0.0f, 1.0f]`.
    ///
    /// @note Consider using `math::Vec4` directly for improved memory layout
    /// and SIMD performance.
    struct Color
    {
        /// @brief Red color component.
        float r = 1.0f;

        /// @brief Green color component.
        float g = 1.0f;

        /// @brief Blue color component.
        float b = 1.0f;

        /// @brief Alpha (opacity) component.
        float a = 1.0f;

        /// @brief Returns the number of floating-point components in a color.
        ///
        /// @return The number of `float` values contained in a `Color`.
        static constexpr int size()
        {
            return sizeof(Color) / sizeof(float);
        }

        /// @brief Compares two colors for equality.
        ///
        /// @param other Color to compare against.
        /// @return `true` if all RGBA components are equal; otherwise, `false`.
        bool operator==(const Color& other) const
        {
            return r == other.r && g == other.g && b == other.b && a == other.a;
        }

        /// @brief Converts the color to a four-component vector.
        ///
        /// @return A `math::Vec4` containing the RGBA components.
        math::Vec4 return_as_vec4() const
        {
            return { r, g, b, a };
        }
    };
}
