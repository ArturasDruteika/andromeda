#ifndef RENDERING__VERTICES__VERTEX_FORMAT__HPP
#define RENDERING__VERTICES__VERTEX_FORMAT__HPP


#include <cstddef>


namespace andromeda::rendering
{
    enum class VertexSemantic
    {
        Position,
        Color0,
        Normal,
        Tangent,
        Bitangent,
        TexCoord0,
        TexCoord1,
        Joints0,
        Weights0
    };

    enum class ComponentType
    {
        Float32,
        Int32,
        UInt32,
        UInt16,
        UInt8
    };

    std::size_t component_type_size_bytes(ComponentType type);
    bool is_integer_component_type(ComponentType type);
}


#endif // RENDERING__VERTICES__VERTEX_FORMAT__HPP