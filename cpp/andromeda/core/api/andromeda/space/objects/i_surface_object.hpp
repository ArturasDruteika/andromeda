#ifndef API__OBJECTS__I_SURFACE_OBJECT__HPP
#define API__OBJECTS__I_SURFACE_OBJECT__HPP


#include "../materials/i_material.hpp"


namespace Andromeda
{
    class ISurfaceObject
    {
    public:
        virtual ~ISurfaceObject() = default;

        virtual const IMaterial* get_material() const = 0;
        virtual void set_material(const IMaterial* material) = 0;
    };
}


#endif // API__OBJECTS__I_SURFACE_OBJECT__HPP