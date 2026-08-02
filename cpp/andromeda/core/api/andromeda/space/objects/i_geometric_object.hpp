#pragma once


#include "i_object.hpp"
#include "i_mesh.hpp"
#include "../colors/colors.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda
{
    /// @brief Defines the interface for a geometric object.
    ///
    /// A geometric object represents a scene object with renderable geometry.
    /// It provides access to the object's mesh and display color.
    class IGeometricObject
        : public virtual IObject
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IGeometricObject() = default;

        // Getters

        /// @brief Retrieves the mesh associated with the object.
        ///
        /// @return Reference to the object's mesh.
        virtual const IMesh& get_mesh() const = 0;

        /// @brief Retrieves the object's display color.
        ///
        /// @return Reference to the object's color.
        virtual const Color& get_color() const = 0;

        // Setters

        /// @brief Sets the object's display color.
        ///
        /// @param color New color of the object.
        virtual void set_color(const Color& color) = 0;
    };
}
