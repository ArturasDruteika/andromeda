#ifndef SPACE__SCENE__SCENE_LIGHTING__HPP
#define SPACE__SCENE__SCENE_LIGHTING__HPP


#include "../../light/include/directional_light.hpp"
#include "../../light/include/point_light.hpp"
#include "../../objects/include/light_object.hpp"
#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/scene/i_scene_lighting.hpp"


namespace andromeda::space
{
    class SPACE_API SceneLighting
        : public virtual ISceneLighting
    {
    public:
        SceneLighting();
        ~SceneLighting() override;

        // Getters
        const std::unordered_map<int, const IDirectionalLight*>& get_directional_lights() const override;
        const std::unordered_map<int, const IPointLight*>& get_point_lights() const override;
        const std::unordered_map<int, const ILightObject*>& get_light_objects() const override;

        void add_light_object(int id, const ILightObject* p_light_object);
        void remove_light_object(int id);

    protected:
        std::unordered_map<int, const IDirectionalLight*> m_directional_lights;
        std::unordered_map<int, const IPointLight*> m_point_lights;
        std::unordered_map<int, const ILightObject*> m_light_objects;
    };
}


#endif // SPACE__SCENE__SCENE_LIGHTING__HPP