#ifndef SPACE__SCENE_GRAPH__LIGHT_COMPONENT__HPP
#define SPACE__SCENE_GRAPH__LIGHT_COMPONENT__HPP


#include "scene_component.hpp"
#include "andromeda/space/objects/i_light_object.hpp"


namespace andromeda::space
{
    class SPACE_API LightComponent
        : public SceneComponent
    {
    public:
        LightComponent(int id, const ILightObject* light_object);
        ~LightComponent() override;

        int get_id() const;
        const ILightObject* get_light_object() const;

    private:
        int m_id;
        const ILightObject* m_light_object;
    };
}


#endif // SPACE__SCENE_GRAPH__LIGHT_COMPONENT__HPP