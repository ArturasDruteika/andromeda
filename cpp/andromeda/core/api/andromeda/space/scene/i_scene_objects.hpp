#pragma once


#include "../objects/i_geometric_object.hpp"
#include "../objects/i_light_object.hpp"
#include "../transformations/i_transformable.hpp"
#include <map>


namespace andromeda
{
    /// @brief Defines the interface for managing scene objects.
    ///
    /// Provides access to the geometric objects contained in a scene and their
    /// associated transformations. It also exposes operations for adding and
    /// removing objects from the scene.
    class ISceneObjects
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ISceneObjects() = default;

        // Getters

        /// @brief Retrieves all geometric objects in the scene.
        ///
        /// @return Reference to a map of objects indexed by object ID.
        virtual const std::unordered_map<int, IGeometricObject*>& get_objects() const = 0;

        /// @brief Retrieves the transforms associated with scene objects.
        ///
        /// @return Reference to a map of object transforms indexed by object ID.
        virtual const std::unordered_map<int, ITransformable*>& get_object_transforms() const = 0;

        // Modifiers

        /// @brief Adds an object to the scene.
        ///
        /// @param id Unique identifier of the object.
        /// @param object Pointer to the object to add.
        virtual void add_object(int id, IGeometricObject* object) = 0;

        /// @brief Removes an object from the scene.
        ///
        /// @param id Unique identifier of the object to remove.
        virtual void remove_object(int id) = 0;
    };
}
