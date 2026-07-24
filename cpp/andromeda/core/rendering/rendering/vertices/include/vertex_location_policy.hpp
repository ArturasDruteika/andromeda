#ifndef RENDERING__VERTICES__VERTEX_LOCATION_POLICY__HPP
#define RENDERING__VERTICES__VERTEX_LOCATION_POLICY__HPP


#include "vertex_format.hpp"
#include "pch.hpp"


namespace andromeda::rendering
{
    class VertexLocationPolicy
    {
    public:
        static uint32_t get_location(VertexSemantic semantic);
    };
}

#endif // RENDERING__VERTICES__VERTEX_LOCATION_POLICY__HPP