#ifndef API__OBJECTS__I_SPHERE__HPP
#define API__OBJECTS__I_SPHERE__HPP


#include "i_geometric_object.hpp"
#include "i_surface_object.hpp"


namespace andromeda
{
    /// @brief Defines the interface for a sphere object.
    ///
    /// A sphere is a geometric surface object whose size is defined by its
    /// radius measured from its center to its surface.
    class ISphere
        : public virtual IGeometricObject
        , public virtual ISurfaceObject
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ISphere() = default;

        // Getters

        /// @brief Retrieves the sphere radius.
        ///
        /// @return Radius of the sphere.
        virtual float get_radius() const = 0;
    };
}


#endif // API__OBJECTS__I_SPHERE__HPP