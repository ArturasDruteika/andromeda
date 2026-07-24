#ifndef RENDERING__VERTICES__VERTEX_LAYOUT_OPENGL__HPP
#define RENDERING__VERTICES__VERTEX_LAYOUT_OPENGL__HPP


#include "../../../vertices/include/VertexLayouts.hpp"


namespace andromeda::Rendering
{
    class VertexLayoutOpenGL
    {
    public:
        static void Apply(const VertexLayout& layout);
    };
}

#endif // RENDERING__VERTICES__VERTEX_LAYOUT_OPENGL__HPP
