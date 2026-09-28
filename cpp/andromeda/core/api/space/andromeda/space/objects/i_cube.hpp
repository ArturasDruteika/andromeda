#pragma once


#include "i_geometric_object.hpp"
#include "i_surface_object.hpp"


namespace andromeda
{
    /// @brief Defines the interface for a cube object.
    ///
    /// A cube is a geometric surface object whose size is defined by a
    /// half-extent measured from its center to each face.
    class ICube
        : public virtual IGeometricObject
        , public virtual ISurfaceObject
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ICube() = default;

        /// @brief Retrieves the cube half-extent.
        ///
        /// @return Half the length of each cube edge.
        virtual float get_half_extent() const = 0;
    };
}
