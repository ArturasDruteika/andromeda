#ifndef RENDERING__VERTEX_ATTRIBUTES__HPP
#define RENDERING__VERTEX_ATTRIBUTES__HPP


#include <stddef.h>


namespace andromeda::rendering
{
    /// @brief Describes a single vertex attribute.
    ///
    /// Defines how a vertex attribute is interpreted by the graphics pipeline,
    /// including its shader location, data format, and memory layout.
    struct VertexAttributes
    {
        /// @brief Attribute location in the shader program.
        unsigned int index = 0;

        /// @brief Number of components in the attribute (for example, 3 for a vec3).
        int size = -1;

        /// @brief Underlying graphics API data type (for example, GL_FLOAT).
        unsigned int type = 0;

        /// @brief Indicates whether integer values should be normalized.
        bool normalized = false;

        /// @brief Byte stride between consecutive vertex attributes.
        size_t stride = 0;

        /// @brief Byte offset of the attribute within the vertex structure.
        size_t offset = 0;
    };
}


#endif // RENDERING__VERTEX_ATTRIBUTES__HPP