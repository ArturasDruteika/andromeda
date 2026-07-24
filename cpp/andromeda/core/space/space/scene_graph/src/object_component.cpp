#include "../include/object_component.hpp"


namespace andromeda::space
{
    ObjectComponent::ObjectComponent(int id, IGeometricObject* object)
        : m_id{ id }
        , m_object{ object }
    {
    }

    ObjectComponent::~ObjectComponent() = default;

    int ObjectComponent::get_id() const
    {
        return m_id;
    }

    IGeometricObject* ObjectComponent::get_object() const
    {
        return m_object;
    }
}