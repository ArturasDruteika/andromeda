#include "../include/VertexLayoutOpenGL.hpp"
#include "../../../vertices/include/VertexFormat.hpp"
#include "../../../vertices/include/VertexLocationPolicy.hpp"

#include "glad/gl.h"


namespace andromeda::Rendering
{
    static GLenum ToGLComponentType(andromeda::Rendering::ComponentType type)
    {
        switch (type)
        {
        case andromeda::Rendering::ComponentType::Float32: return GL_FLOAT;
        case andromeda::Rendering::ComponentType::Int32:   return GL_INT;
        case andromeda::Rendering::ComponentType::UInt32:  return GL_UNSIGNED_INT;
        case andromeda::Rendering::ComponentType::UInt16:  return GL_UNSIGNED_SHORT;
        case andromeda::Rendering::ComponentType::UInt8:   return GL_UNSIGNED_BYTE;
        default:                                           return GL_FLOAT;
        }
    }

    static bool IsIntegerType(andromeda::Rendering::ComponentType type)
    {
        return andromeda::Rendering::IsIntegerComponentType(type);
    }

    void VertexLayoutOpenGL::Apply(const andromeda::Rendering::VertexLayout& layout)
    {
        const std::vector<VertexAttributeDesc>& attrs = layout.GetAttributes();
        const GLsizei stride = static_cast<GLsizei>(layout.GetStrideBytes());

        for (const VertexAttributeDesc& attr : attrs)
        {
            const GLuint location = static_cast<GLuint>(andromeda::Rendering::VertexLocationPolicy::GetLocation(attr.semantic));
            const void* offsetPtr = reinterpret_cast<const void*>(attr.offsetBytes);

            glEnableVertexAttribArray(location);

            if (IsIntegerType(attr.componentType))
            {
                glVertexAttribIPointer(
                    location,
                    static_cast<GLint>(attr.componentCount),
                    ToGLComponentType(attr.componentType),
                    stride,
                    offsetPtr
                );
            }
            else
            {
                glVertexAttribPointer(
                    location,
                    static_cast<GLint>(attr.componentCount),
                    ToGLComponentType(attr.componentType),
                    attr.normalized ? GL_TRUE : GL_FALSE,
                    stride,
                    offsetPtr
                );
            }

            if (layout.GetInputRate() == andromeda::Rendering::InputRate::PerInstance)
            {
                glVertexAttribDivisor(location, 1);
            }
        }
    }
}
