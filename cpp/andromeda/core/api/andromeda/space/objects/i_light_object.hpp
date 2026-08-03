#pragma once


#include "i_object.hpp"
#include "../light/light_types.hpp"


namespace andromeda
{
    /// @brief Defines the interface for a light object.
    ///
    /// A light object represents a scene object that emits light. It provides
    /// access to the type of light represented by the object.
    class ILightObject
        : public virtual IObject
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ILightObject() = default;

        // Getters

        /// @brief Retrieves the light type.
        ///
        /// @return Reference to the light type.
        virtual const LightType& get_light_type() const = 0;
    };
}
