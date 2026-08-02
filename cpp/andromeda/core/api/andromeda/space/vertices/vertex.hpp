#ifndef API__SPACE__VERTICES__VERTEX__HPP
#define API__SPACE__VERTICES__VERTEX__HPP


#include "../colors/colors.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda
{
    /// @brief Represents a vertex in a mesh.
    ///
    /// A vertex stores its position, color, and surface normal for use during
    /// rendering.
    struct Vertex
    {
        /// @brief Vertex position in object space.
        math::Vec3 position;

        /// @brief Vertex color.
        Color color;

        /// @brief Vertex surface normal.
        math::Vec3 normal;

        /// @brief Constructs a default vertex.
        Vertex() = default;

        /// @brief Constructs a vertex with position and color.
        ///
        /// The normal is initialized to `(0, 0, 0)`.
        ///
        /// @param pos Vertex position.
        /// @param col Vertex color.
        Vertex(const math::Vec3& pos, const Color& col)
            : position{ pos }
            , color{ col }
            , normal{ 0.0f, 0.0f, 0.0f }
        {
        }

        /// @brief Constructs a vertex with position, color, and normal.
        ///
        /// @param pos Vertex position.
        /// @param col Vertex color.
        /// @param normal Vertex surface normal.
        Vertex(const math::Vec3& pos, const Color& col, const math::Vec3& normal)
            : position{ pos }
            , color{ col }
            , normal{ normal }
        {
        }

        /// @brief Compares two vertices for equality.
        ///
        /// @param other Vertex to compare against.
        /// @return `true` if all members are equal; otherwise, `false`.
        bool operator==(const Vertex& other) const
        {
            return position == other.position &&
                color == other.color &&
                normal == other.normal;
        }
    };
}


#endif // API__SPACE__VERTICES__VERTEX__HPP