#ifndef API__SCENE__I_SCENE_LIGHTING__HPP
#define API__SCENE__I_SCENE_LIGHTING__HPP


#include "../light/i_directional_light.hpp"
#include "../light/i_point_light.hpp"
#include "../objects/i_light_object.hpp"
#include <map>


namespace andromeda
{
    class ISceneLighting
    {
    public:
        virtual ~ISceneLighting() = default;

        // Getters
        virtual const std::unordered_map<int, const IDirectionalLight*>& get_directional_lights() const = 0;
        virtual const std::unordered_map<int, const IPointLight*>& get_point_lights() const = 0;
        virtual const std::unordered_map<int, const ILightObject*>& get_light_objects() const = 0;
    };
}


#endif // API__SCENE__I_SCENE_LIGHTING__HPP