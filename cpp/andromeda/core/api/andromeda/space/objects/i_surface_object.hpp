#ifndef API__OBJECTS__I_SURFACE_OBJECT__HPP
#define API__OBJECTS__I_SURFACE_OBJECT__HPP


#include "../materials/i_material.hpp"


namespace andromeda
{
    /// @brief Defines the interface for an object with a surface material.
    ///
    /// A surface object provides access to the material used when rendering its
    /// surface.
    class ISurfaceObject
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ISurfaceObject() = default;

        // Getters

        /// @brief Retrieves the material assigned to the object.
        ///
        /// @return Pointer to the material, or `nullptr` if no material is assigned.
        virtual const IMaterial* get_material() const = 0;

        // Setters

        /// @brief Assigns a material to the object.
        ///
        /// @param material Pointer to the material to assign, or `nullptr` to
        ///                 remove the current material.
        virtual void set_material(const IMaterial* material) = 0;
    };
}


#endif // API__OBJECTS__I_SURFACE_OBJECT__HPP