#ifndef SPACE__SCENE_GRAPH__OBJECT_COMPONENT__HPP
#define SPACE__SCENE_GRAPH__OBJECT_COMPONENT__HPP


#include "scene_component.hpp"
#include "andromeda/space/objects/i_geometric_object.hpp"


namespace andromeda::space
{
    /// @brief Scene component that associates a geometric object with a scene node.
    ///
    /// Stores a reference to a geometric object together with its identifier
    /// so it can be registered and managed as part of the scene graph.
    class SPACE_API ObjectComponent
        : public SceneComponent
    {
    public:
        /// @brief Constructs an object component.
        ///
        /// @param id Identifier of the geometric object.
        /// @param object Pointer to the associated geometric object.
        ObjectComponent(int id, IGeometricObject* object);

        /// @brief Destroys the object component.
        ~ObjectComponent() override;

        /// @brief Retrieves the geometric object's identifier.
        ///
        /// @return Geometric object identifier.
        int get_id() const;

        /// @brief Retrieves the associated geometric object.
        ///
        /// @return Pointer to the associated geometric object.
        IGeometricObject* get_object() const;

    private:
        /// @brief Identifier of the associated geometric object.
        int m_id;

        /// @brief Pointer to the associated geometric object.
        IGeometricObject* m_object;
    };
}


#endif // SPACE__SCENE_GRAPH__OBJECT_COMPONENT__HPP