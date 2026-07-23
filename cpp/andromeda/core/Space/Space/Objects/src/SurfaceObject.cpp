#include "../include/SurfaceObject.hpp"


namespace andromeda::Space
{
    SurfaceObject::SurfaceObject()
		: m_pMaterial{ nullptr }
    {
    }

    SurfaceObject::~SurfaceObject() = default;

    const andromeda::IMaterial* SurfaceObject::GetMaterial() const
    {
        return m_pMaterial;
    }

    void SurfaceObject::SetMaterial(const andromeda::IMaterial* material)
    {
        m_pMaterial = material;
    }
}