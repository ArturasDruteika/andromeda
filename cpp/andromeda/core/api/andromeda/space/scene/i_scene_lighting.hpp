#ifndef API__SCENE__I_SCENE_LIGHTING__HPP
#define API__SCENE__I_SCENE_LIGHTING__HPP


#include "../light/i_directional_light.hpp"
#include "../light/i_point_light.hpp"
#include "../objects/i_light_object.hpp"
#include <map>


namespace andromeda
{
    /// @brief Defines the interface for accessing scene lighting.
    ///
    /// Provides read-only access to the light sources contained in a scene,
    /// including directional lights, point lights, and a unified collection of
    /// all light objects.
    class ISceneLighting
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ISceneLighting() = default;

        // Getters

        /// @brief Retrieves all directional lights in the scene.
        ///
        /// @return Reference to a map of directional lights indexed by object ID.
        virtual const std::unordered_map<int, const IDirectionalLight*>& get_directional_lights() const = 0;

        /// @brief Retrieves all point lights in the scene.
        ///
        /// @return Reference to a map of point lights indexed by object ID.
        virtual const std::unordered_map<int, const IPointLight*>& get_point_lights() const = 0;

        /// @brief Retrieves all light objects in the scene.
        ///
        /// @return Reference to a map of light objects indexed by object ID.
        virtual const std::unordered_map<int, const ILightObject*>& get_light_objects() const = 0;
    };
}


#endif // API__SCENE__I_SCENE_LIGHTING__HPP