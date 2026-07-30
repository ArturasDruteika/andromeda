#ifndef API__OBJECTS__I_SKYROOM__HPP
#define API__OBJECTS__I_SKYROOM__HPP


#include "i_geometric_object.hpp"
#include "i_surface_object.hpp"


namespace andromeda
{
    /// @brief Defines the interface for a skyroom object.
    ///
    /// A skyroom is a large enclosing geometric object used to render the
    /// surrounding environment. Its size is defined by a half-extent measured
    /// from its center to each face.
    class ISkyroom
        : public virtual IGeometricObject
        , public virtual ISurfaceObject
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ISkyroom() = default;

        // Getters

        /// @brief Retrieves the skyroom half-extent.
        ///
        /// @return Half the length of each side of the skyroom.
        virtual float get_half_extent() const = 0;

        // Setters

        /// @brief Sets the skyroom half-extent.
        ///
        /// @param half_extent Half the length of each side of the skyroom.
        virtual void set_half_extent(float half_extent) = 0;
    };
}


#endif // API__OBJECTS__I_SKYROOM__HPP