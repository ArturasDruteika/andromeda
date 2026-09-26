#pragma once


#include "scene_component.hpp"
#include "andromeda/space/objects/i_light_object.hpp"


namespace andromeda::space
{
    /// @brief Scene component that associates a light object with a scene node.
    ///
    /// Stores a reference to a light object together with its identifier so it
    /// can be registered and managed as part of the scene graph.
    class SPACE_API LightComponent
        : public SceneComponent
    {
    public:
        /// @brief Constructs a light component.
        ///
        /// @param id Identifier of the light object.
        /// @param light_object Pointer to the associated light object.
        LightComponent(int id, const ILightObject* light_object);

        /// @brief Destroys the light component.
        ~LightComponent() override;

        /// @brief Retrieves the light object's identifier.
        ///
        /// @return Light object identifier.
        int get_id() const;

        /// @brief Retrieves the associated light object.
        ///
        /// @return Pointer to the associated light object.
        const ILightObject* get_light_object() const;

    private:
        /// @brief Identifier of the associated light object.
        int m_id;

        /// @brief Pointer to the associated light object.
        const ILightObject* m_light_object;
    };
}
