#include "../include/surface_object.hpp"


namespace andromeda::space
{
    SurfaceObject::SurfaceObject()
        : m_p_material{ nullptr }
    {
    }

    SurfaceObject::~SurfaceObject() = default;

    const andromeda::IMaterial* SurfaceObject::get_material() const
    {
        return m_p_material;
    }

    void SurfaceObject::set_material(const andromeda::IMaterial* material)
    {
        m_p_material = material;
    }
}