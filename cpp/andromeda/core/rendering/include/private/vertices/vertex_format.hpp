#pragma once


#include <cstddef>


namespace andromeda::rendering
{
    /// @brief Identifies the semantic meaning of a vertex attribute.
    enum class VertexSemantic
    {
        /// @brief Vertex position.
        Position,

        /// @brief Primary vertex color.
        Color0,

        /// @brief Surface normal.
        Normal,

        /// @brief Tangent vector.
        Tangent,

        /// @brief Bitangent vector.
        Bitangent,

        /// @brief Primary texture coordinates.
        TexCoord0,

        /// @brief Secondary texture coordinates.
        TexCoord1,

        /// @brief Joint indices used for skeletal animation.
        Joints0,

        /// @brief Joint weights used for skeletal animation.
        Weights0
    };

    /// @brief Enumerates supported vertex component data types.
    enum class ComponentType
    {
        /// @brief 32-bit floating-point value.
        Float32,

        /// @brief 32-bit signed integer.
        Int32,

        /// @brief 32-bit unsigned integer.
        UInt32,

        /// @brief 16-bit unsigned integer.
        UInt16,

        /// @brief 8-bit unsigned integer.
        UInt8
    };

    /// @brief Retrieves the size of a vertex component type.
    ///
    /// @param type Component type.
    /// @return Size of the component type in bytes.
    std::size_t component_type_size_bytes(ComponentType type);

    /// @brief Checks whether a component type is integral.
    ///
    /// @param type Component type.
    /// @return `true` if the component type is an integer type; otherwise,
    /// `false`.
    bool is_integer_component_type(ComponentType type);
}
