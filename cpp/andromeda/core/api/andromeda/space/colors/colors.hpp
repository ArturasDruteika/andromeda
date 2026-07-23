#ifndef API__SPACE__COLORS__COLORS__HPP
#define API__SPACE__COLORS__COLORS__HPP


#include "Math/LinearAlgebra/include/linear_algebra_data_types.hpp"


namespace andromeda
{
    // TODO: consider using Math::Vec4 vector to store data for speed
    struct Color
    {
        float r = 1.0f;
        float g = 1.0f;
        float b = 1.0f;
        float a = 1.0f;

        static constexpr int size()
        {
            return sizeof(Color) / sizeof(float);
        }

        bool operator==(const Color& other) const
        {
            return r == other.r && g == other.g && b == other.b && a == other.a;
        }

        Math::Vec4 return_as_vec4() const
		{
            return { r, g, b, a };
		}
    };
}


#endif // API__SPACE__COLORS__COLORS__HPP