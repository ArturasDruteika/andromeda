#ifndef SPACE__OBJECTS__SURFACE_OBJECT__HPP
#define SPACE__OBJECTS__SURFACE_OBJECT__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/objects/i_surface_object.hpp"


namespace andromeda::space
{
    class Material;

    /// @brief Represents a scene object with an associated surface material.
    ///
    /// Provides access to a material used for rendering the object's surface.
    class SPACE_API SurfaceObject
        : public virtual ISurfaceObject
    {
    public:
        /// @brief Constructs a surface object.
        SurfaceObject();

        /// @brief Destroys the surface object.
        ~SurfaceObject() override;

        /// @brief Retrieves the material assigned to the surface.
        ///
        /// @return Pointer to the assigned material, or `nullptr` if none is set.
        const IMaterial* get_material() const override;

        /// @brief Assigns a material to the surface.
        ///
        /// @param material Pointer to the material to assign.
        void set_material(const IMaterial* material) override;

    private:
        /// @brief Pointer to the assigned surface material.
        const IMaterial* m_p_material;
    };
}

#endif // SPACE__OBJECTS__SURFACE_OBJECT__HPP