#ifndef API__SPACE__SCENE__I_SCENE_NODE__HPP
#define API__SPACE__SCENE__I_SCENE_NODE__HPP


#include "../transformations/i_transformable.hpp"

#include <functional>
#include <memory>


namespace andromeda
{
    class ISceneComponent;

    /// @brief Defines the interface for a scene graph node.
    ///
    /// A scene node stores a transform, participates in a parent-child
    /// hierarchy, and owns a collection of scene components.
    class ISceneNode
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ISceneNode() = default;

        // Transform

        /// @brief Retrieves the node transform.
        ///
        /// @return Reference to the node's transform.
        virtual ITransformable& get_transform() = 0;

        /// @brief Retrieves the node transform.
        ///
        /// @return Constant reference to the node's transform.
        virtual const ITransformable& get_transform() const = 0;

        // Hierarchy

        /// @brief Retrieves the parent node.
        ///
        /// @return Pointer to the parent node, or `nullptr` if this is the root node.
        virtual ISceneNode* get_parent() const = 0;

        /// @brief Attaches a child node.
        ///
        /// Ownership of the child node is transferred to this node.
        ///
        /// @param child Unique pointer to the child node.
        virtual void attach_child(std::unique_ptr<ISceneNode> child) = 0;

        /// @brief Detaches a child node.
        ///
        /// Ownership of the detached node is transferred to the caller.
        ///
        /// @param child Child node to detach.
        /// @return Unique pointer to the detached node.
        virtual std::unique_ptr<ISceneNode> detach_child(ISceneNode& child) = 0;

        /// @brief Invokes a function for each child node.
        ///
        /// @param fn Function to invoke for each child.
        virtual void for_each_child(const std::function<void(ISceneNode&)>& fn) = 0;

        /// @brief Invokes a function for each child node.
        ///
        /// @param fn Function to invoke for each child.
        virtual void for_each_child(const std::function<void(const ISceneNode&)>& fn) const = 0;

        // Components

        /// @brief Adds a component to the node.
        ///
        /// Ownership of the component is transferred to the node.
        ///
        /// @param component Unique pointer to the component.
        /// @return Reference to the added component.
        virtual ISceneComponent& add_component(std::unique_ptr<ISceneComponent> component) = 0;

        /// @brief Removes a component from the node.
        ///
        /// @param component Component to remove.
        /// @return `true` if the component was removed; otherwise, `false`.
        virtual bool remove_component(ISceneComponent& component) = 0;

        /// @brief Invokes a function for each component.
        ///
        /// @param fn Function to invoke for each component.
        virtual void for_each_component(const std::function<void(ISceneComponent&)>& fn) = 0;

        /// @brief Invokes a function for each component.
        ///
        /// @param fn Function to invoke for each component.
        virtual void for_each_component(const std::function<void(const ISceneComponent&)>& fn) const = 0;
    };
}


#endif // API__SPACE__SCENE__I_SCENE_NODE__HPP