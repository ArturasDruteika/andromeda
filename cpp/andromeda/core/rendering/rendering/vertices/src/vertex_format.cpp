#include "../include/vertex_format.hpp"


namespace andromeda::rendering
{
    std::size_t component_type_size_bytes(ComponentType type)
    {
        switch (type)
        {
        case ComponentType::Float32: return 4;
        case ComponentType::Int32:   return 4;
        case ComponentType::UInt32:  return 4;
        case ComponentType::UInt16:  return 2;
        case ComponentType::UInt8:   return 1;
        default:                     return 0;
        }
    }

    bool is_integer_component_type(ComponentType type)
    {
        switch (type)
        {
        case ComponentType::Int32:
        case ComponentType::UInt32:
        case ComponentType::UInt16:
        case ComponentType::UInt8:
            return true;

        case ComponentType::Float32:
        default:
            return false;
        }
    }
}