#pragma once


#include "../../linear_algebra/include/linear_algebra_data_types.hpp"

#include <limits>


namespace andromeda::math
{
    /// @brief The mathematical constant π.
    constexpr float PI = 3.14159265358979323846f;

    /// @brief Half of π.
    constexpr float PI_HALF = PI / 2.0f;

    /// @brief Default tolerance for floating-point comparisons.
    constexpr float EPSILON = 1e-6f;

    /// @brief Positive infinity.
    constexpr float INFINITY_VALUE = std::numeric_limits<float>::infinity();

    /// @brief Negative infinity.
    constexpr float NEGATIVE_INFINITY_VALUE = -std::numeric_limits<float>::infinity();

    /// @brief Unit vector along the positive X axis.
    constexpr math::Vec3 X_AXIS{ 1.0f, 0.0f, 0.0f };

    /// @brief Unit vector along the positive Y axis.
    constexpr math::Vec3 Y_AXIS{ 0.0f, 1.0f, 0.0f };

    /// @brief Unit vector along the negative Z axis.
    constexpr math::Vec3 NEGATIVE_Z_AXIS{ 0.0f, 0.0f, -1.0f };
}
