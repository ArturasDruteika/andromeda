#include "../include/light_component.hpp"


namespace andromeda::space
{
    LightComponent::LightComponent(int id, const ILightObject* light_object)
        : m_id{ id }
        , m_light_object{ light_object }
    {
    }

    LightComponent::~LightComponent() = default;

    int LightComponent::get_id() const
    {
        return m_id;
    }

    const ILightObject* LightComponent::get_light_object() const
    {
        return m_light_object;
    }
}