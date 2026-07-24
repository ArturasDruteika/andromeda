#ifndef API__SPACE__SCENE__SCENE_NODE__HPP
#define API__SPACE__SCENE__SCENE_NODE__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/scene_graph/i_scene_node.hpp"
#include "pch.hpp"


namespace andromeda::space
{
    class SPACE_API SceneNode
        : public ISceneNode
    {
    public:
        // SceneNode owns its transform implementation.
        explicit SceneNode(std::unique_ptr<ITransformable> transform);

        ~SceneNode() override;

        // Transform
        ITransformable& get_transform() override;
        const ITransformable& get_transform() const override;

        // Hierarchy
        ISceneNode* get_parent() const override;

        void attach_child(std::unique_ptr<ISceneNode> child) override;
        std::unique_ptr<ISceneNode> detach_child(ISceneNode& child) override;

        void for_each_child(const std::function<void(ISceneNode&)>& fn) override;
        void for_each_child(const std::function<void(const ISceneNode&)>& fn) const override;

        // Components
        ISceneComponent& add_component(std::unique_ptr<ISceneComponent> component) override;
        bool remove_component(ISceneComponent& component) override;

        void for_each_component(const std::function<void(ISceneComponent&)>& fn) override;
        void for_each_component(const std::function<void(const ISceneComponent&)>& fn) const override;

    private:
        // Internal helper to keep parent pointer consistent.
        // Only SceneNode modifies SceneNode parent pointers.
        void set_parent_internal(SceneNode* parent);

    private:
        // Non-owning parent pointer.
        SceneNode* m_parent = nullptr;

        // Owned transform.
        std::unique_ptr<ITransformable> m_transform;

        // Owned children and components.
        std::vector<std::unique_ptr<ISceneNode>> m_children;
        std::vector<std::unique_ptr<ISceneComponent>> m_components;
    };
}

#endif // API__SPACE__SCENE__SCENE_NODE__HPP