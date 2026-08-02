#ifndef API__SPACE__SCENE__SCENE_NODE__HPP
#define API__SPACE__SCENE__SCENE_NODE__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/scene_graph/i_scene_node.hpp"
#include "pch.hpp"


namespace andromeda::space
{
    /// @brief Represents a node in the scene graph.
    ///
    /// Owns a transform, child nodes, and attached components, forming the
    /// hierarchical structure of a scene.
    class SPACE_API SceneNode
        : public ISceneNode
    {
    public:
        /// @brief Constructs a scene node.
        ///
        /// @param transform Transform owned by the node.
        explicit SceneNode(std::unique_ptr<ITransformable> transform);

        /// @brief Destroys the scene node.
        ~SceneNode() override;

        // Transform

        /// @brief Retrieves the node's transform.
        ///
        /// @return Reference to the owned transform.
        ITransformable& get_transform() override;

        /// @brief Retrieves the node's transform.
        ///
        /// @return Constant reference to the owned transform.
        const ITransformable& get_transform() const override;

        // Hierarchy

        /// @brief Retrieves the parent node.
        ///
        /// @return Pointer to the parent node, or `nullptr` if this is the root.
        ISceneNode* get_parent() const override;

        /// @brief Attaches a child node.
        ///
        /// @param child Child node to attach.
        void attach_child(std::unique_ptr<ISceneNode> child) override;

        /// @brief Detaches a child node.
        ///
        /// @param child Child node to detach.
        /// @return Ownership of the detached child node.
        std::unique_ptr<ISceneNode> detach_child(ISceneNode& child) override;

        /// @brief Invokes a function for each child node.
        ///
        /// @param fn Function to invoke.
        void for_each_child(const std::function<void(ISceneNode&)>& fn) override;

        /// @brief Invokes a function for each child node.
        ///
        /// @param fn Function to invoke.
        void for_each_child(const std::function<void(const ISceneNode&)>& fn) const override;

        // Components

        /// @brief Attaches a component to the node.
        ///
        /// @param component Component to attach.
        /// @return Reference to the attached component.
        ISceneComponent& add_component(std::unique_ptr<ISceneComponent> component) override;

        /// @brief Removes a component from the node.
        ///
        /// @param component Component to remove.
        /// @return `true` if the component was removed; otherwise, `false`.
        bool remove_component(ISceneComponent& component) override;

        /// @brief Invokes a function for each attached component.
        ///
        /// @param fn Function to invoke.
        void for_each_component(const std::function<void(ISceneComponent&)>& fn) override;

        /// @brief Invokes a function for each attached component.
        ///
        /// @param fn Function to invoke.
        void for_each_component(const std::function<void(const ISceneComponent&)>& fn) const override;

    private:
        /// @brief Sets the node's parent.
        ///
        /// Internal helper used to keep parent pointers consistent.
        ///
        /// @param parent New parent node.
        void set_parent_internal(SceneNode* parent);

    private:
        /// @brief Non-owning pointer to the parent node.
        SceneNode* m_parent = nullptr;

        /// @brief Transform owned by this node.
        std::unique_ptr<ITransformable> m_transform;

        /// @brief Child nodes owned by this node.
        std::vector<std::unique_ptr<ISceneNode>> m_children;

        /// @brief Components attached to this node.
        std::vector<std::unique_ptr<ISceneComponent>> m_components;
    };
}


#endif // API__SPACE__SCENE__SCENE_NODE__HPP