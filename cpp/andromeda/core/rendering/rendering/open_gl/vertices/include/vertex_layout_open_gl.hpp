#ifndef RENDERING__VERTICES__VERTEX_LAYOUT_OPEN_GL__HPP
#define RENDERING__VERTICES__VERTEX_LAYOUT_OPEN_GL__HPP


#include "../../../vertices/include/vertex_layouts.hpp"


namespace andromeda::rendering
{
    class VertexLayoutOpenGL
    {
    public:
        static void apply(const VertexLayout& layout);
    };
}


#endif // RENDERING__VERTICES__VERTEX_LAYOUT_OPEN_GL__HPP