#ifndef RENDERING__VERTICES__VERTEX_LAYOUT_OPEN_GL__HPP
#define RENDERING__VERTICES__VERTEX_LAYOUT_OPEN_GL__HPP


#include "../../../vertices/include/vertex_layouts.hpp"


namespace andromeda::rendering
{
    /// @brief Applies a vertex layout to the currently bound OpenGL vertex array.
    ///
    /// Configures OpenGL vertex attribute pointers according to the supplied
    /// vertex layout description.
    class VertexLayoutOpenGL
    {
    public:
        /// @brief Applies the specified vertex layout.
        ///
        /// @param layout Vertex layout describing the vertex buffer format.
        static void apply(const VertexLayout& layout);
    };
}


#endif // RENDERING__VERTICES__VERTEX_LAYOUT_OPEN_GL__HPP