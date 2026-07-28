#ifndef SPACE__SCENE_GRAPH__OBJECT_COMPONENT__HPP
#define SPACE__SCENE_GRAPH__OBJECT_COMPONENT__HPP


#include "scene_component.hpp"
#include "andromeda/space/objects/i_geometric_object.hpp"


namespace andromeda::space
{
    class SPACE_API ObjectComponent
        : public SceneComponent
    {
    public:
        ObjectComponent(int id, IGeometricObject* object);
        ~ObjectComponent() override;

        int get_id() const;
        IGeometricObject* get_object() const;

    private:
        int m_id;
        IGeometricObject* m_object;
    };
}


#endif // SPACE__SCENE_GRAPH__OBJECT_COMPONENT__HPP