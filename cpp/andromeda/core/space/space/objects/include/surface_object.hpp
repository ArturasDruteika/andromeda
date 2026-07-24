#ifndef SPACE__OBJECTS__SURFACE_OBJECT__HPP
#define SPACE__OBJECTS__SURFACE_OBJECT__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/objects/i_surface_object.hpp"


namespace andromeda::space
{
    class Material;

    class SPACE_API SurfaceObject
        : public virtual ISurfaceObject
    {
    public:
        SurfaceObject();
        ~SurfaceObject() override;

        const IMaterial* get_material() const override;
        void set_material(const IMaterial* material) override;

    private:
        const IMaterial* m_p_material;
    };
}

#endif // SPACE__OBJECTS__SURFACE_OBJECT__HPP