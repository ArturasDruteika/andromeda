#ifndef SPACE__SCENE__SCENE_LIGHTING__HPP
#define SPACE__SCENE__SCENE_LIGHTING__HPP


#include "../../light/include/directional_light.hpp"
#include "../../light/include/point_light.hpp"
#include "../../objects/include/light_object.hpp"
#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/scene/i_scene_lighting.hpp"


namespace andromeda::space
{
    /// @brief Manages the light sources contained within a scene.
    ///
    /// Maintains collections of directional lights, point lights, and generic
    /// light objects to support scene lighting and rendering.
    class SPACE_API SceneLighting
        : public virtual ISceneLighting
    {
    public:
        /// @brief Constructs a scene lighting manager.
        SceneLighting();

        /// @brief Destroys the scene lighting manager.
        ~SceneLighting() override;

        // Getters

        /// @brief Retrieves all directional lights in the scene.
        ///
        /// @return Map of directional lights indexed by object identifier.
        const std::unordered_map<int, const IDirectionalLight*>& get_directional_lights() const override;

        /// @brief Retrieves all point lights in the scene.
        ///
        /// @return Map of point lights indexed by object identifier.
        const std::unordered_map<int, const IPointLight*>& get_point_lights() const override;

        /// @brief Retrieves all light objects in the scene.
        ///
        /// @return Map of light objects indexed by object identifier.
        const std::unordered_map<int, const ILightObject*>& get_light_objects() const override;

        /// @brief Registers a light object with the scene.
        ///
        /// @param id Identifier of the light object.
        /// @param p_light_object Pointer to the light object.
        void add_light_object(int id, const ILightObject* p_light_object);

        /// @brief Removes a light object from the scene.
        ///
        /// @param id Identifier of the light object to remove.
        void remove_light_object(int id);

    protected:
        /// @brief Collection of directional lights indexed by object identifier.
        std::unordered_map<int, const IDirectionalLight*> m_directional_lights;

        /// @brief Collection of point lights indexed by object identifier.
        std::unordered_map<int, const IPointLight*> m_point_lights;

        /// @brief Collection of all light objects indexed by object identifier.
        std::unordered_map<int, const ILightObject*> m_light_objects;
    };
}


#endif // SPACE__SCENE__SCENE_LIGHTING__HPP