#ifndef RENDERING__VERTICES__VERTEX_LOCATION_POLICY__HPP
#define RENDERING__VERTICES__VERTEX_LOCATION_POLICY__HPP


#include "vertex_format.hpp"
#include "pch.hpp"


namespace andromeda::rendering
{
    /// @brief Maps vertex semantics to shader attribute locations.
    ///
    /// Provides a centralized policy for assigning fixed attribute locations
    /// used by vertex layouts and shader programs.
    class VertexLocationPolicy
    {
    public:
        /// @brief Retrieves the shader attribute location for a vertex semantic.
        ///
        /// @param semantic Vertex attribute semantic.
        /// @return Shader attribute location.
        static uint32_t get_location(VertexSemantic semantic);
    };
}

#endif // RENDERING__VERTICES__VERTEX_LOCATION_POLICY__HPP