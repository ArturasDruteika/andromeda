#include "../include/vertex_layout_open_gl.hpp"
#include "../../../vertices/include/vertex_format.hpp"
#include "../../../vertices/include/vertex_location_policy.hpp"

#include "glad/gl.h"


namespace andromeda::rendering
{
    static GLenum to_gl_component_type(ComponentType type)
    {
        switch (type)
        {
        case ComponentType::Float32: return GL_FLOAT;
        case ComponentType::Int32:   return GL_INT;
        case ComponentType::UInt32:  return GL_UNSIGNED_INT;
        case ComponentType::UInt16:  return GL_UNSIGNED_SHORT;
        case ComponentType::UInt8:   return GL_UNSIGNED_BYTE;
        default:                     return GL_FLOAT;
        }
    }

    static bool is_integer_type(ComponentType type)
    {
        return is_integer_component_type(type);
    }

    void VertexLayoutOpenGL::apply(const VertexLayout& layout)
    {
        const std::vector<VertexAttributeDesc>& attributes = layout.get_attributes();
        const GLsizei stride = static_cast<GLsizei>(layout.get_stride_bytes());

        for (const VertexAttributeDesc& attribute : attributes)
        {
            const GLuint location = static_cast<GLuint>(VertexLocationPolicy::get_location(attribute.semantic));

            const void* offset_ptr = reinterpret_cast<const void*>(attribute.offset_bytes);

            glEnableVertexAttribArray(location);

            if (is_integer_type(attribute.component_type))
            {
                glVertexAttribIPointer(
                    location,
                    static_cast<GLint>(attribute.component_count),
                    to_gl_component_type(attribute.component_type),
                    stride,
                    offset_ptr
                );
            }
            else
            {
                glVertexAttribPointer(
                    location,
                    static_cast<GLint>(attribute.component_count),
                    to_gl_component_type(attribute.component_type),
                    attribute.normalized ? GL_TRUE : GL_FALSE,
                    stride,
                    offset_ptr
                );
            }

            if (layout.get_input_rate() == InputRate::PerInstance)
            {
                glVertexAttribDivisor(location, 1);
            }
        }
    }
}