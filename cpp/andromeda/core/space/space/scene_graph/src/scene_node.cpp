#include "../include/scene_node.hpp"
#include "andromeda/space/scene_graph/i_scene_component.hpp"

#include "spdlog/spdlog.h"


namespace andromeda::space
{
    SceneNode::SceneNode(std::unique_ptr<ITransformable> transform)
        : m_transform(std::move(transform))
    {
        if (m_transform == nullptr)
        {
            spdlog::error("SceneNode requires a non-null transform.");
        }
    }

    SceneNode::~SceneNode()
    {
        // Detach components first (they may rely on child hierarchy still existing).
        for (std::unique_ptr<ISceneComponent>& component : m_components)
        {
            if (component != nullptr)
            {
                component->on_detach();
            }
        }
        m_components.clear();

        // Ensure children no longer reference this as a parent before they are destroyed.
        for (std::unique_ptr<ISceneNode>& child : m_children)
        {
            SceneNode* child_node = dynamic_cast<SceneNode*>(child.get());
            if (child_node != nullptr)
            {
                child_node->set_parent_internal(nullptr);
            }
        }
        m_children.clear();

        m_parent = nullptr;
        m_transform.reset();
    }

    ITransformable& SceneNode::get_transform()
    {
        if (m_transform == nullptr)
        {
            spdlog::error("SceneNode has no transform.");
        }
        return *m_transform;
    }

    const ITransformable& SceneNode::get_transform() const
    {
        if (m_transform == nullptr)
        {
            spdlog::error("SceneNode has no transform.");
        }
        return *m_transform;
    }

    ISceneNode* SceneNode::get_parent() const
    {
        return m_parent;
    }

    void SceneNode::attach_child(std::unique_ptr<ISceneNode> child)
    {
        if (child == nullptr)
        {
            return;
        }

        if (child.get() == this)
        {
            spdlog::error("Cannot attach node to itself.");
            return;
        }

        // Best-effort support for "removing from old parent" while still taking unique_ptr:
        // If the child reports a parent, attempt to detach it from that parent and use the returned ownership.
        // IMPORTANT: This only works safely if the caller is not still double-owning the same node elsewhere.
        ISceneNode* old_parent = child->get_parent();
        if (old_parent != nullptr)
        {
            std::unique_ptr<ISceneNode> transferred = old_parent->detach_child(*child);
            if (transferred != nullptr)
            {
                // Avoid double delete: release the passed-in unique_ptr and use the transferred ownership.
                child.release();
                child = std::move(transferred);
            }
            else
            {
                // Could not detach; refuse to attach to keep invariants safe.
                throw std::runtime_error("AttachChild failed: could not detach child from its old parent.");
            }
        }

        SceneNode* child_node = dynamic_cast<SceneNode*>(child.get());
        if (child_node == nullptr)
        {
            spdlog::error("AttachChild requires child to be a SceneNode instance.");
            return;
        }

        child_node->set_parent_internal(this);
        m_children.push_back(std::move(child));
    }

    std::unique_ptr<ISceneNode> SceneNode::detach_child(ISceneNode& child)
    {
        for (size_t i = 0; i < m_children.size(); ++i)
        {
            if (m_children[i].get() == &child)
            {
                SceneNode* child_node = dynamic_cast<SceneNode*>(m_children[i].get());
                if (child_node != nullptr)
                {
                    child_node->set_parent_internal(nullptr);
                }

                std::unique_ptr<ISceneNode> out = std::move(m_children[i]);
                m_children.erase(m_children.begin() + static_cast<long>(i));
                return out;
            }
        }

        return nullptr;
    }

    void SceneNode::for_each_child(const std::function<void(ISceneNode&)>& fn)
    {
        for (std::unique_ptr<ISceneNode>& child : m_children)
        {
            fn(*child);
        }
    }

    void SceneNode::for_each_child(const std::function<void(const ISceneNode&)>& fn) const
    {
        for (const std::unique_ptr<ISceneNode>& child : m_children)
        {
            fn(*child);
        }
    }

    ISceneComponent& SceneNode::add_component(std::unique_ptr<ISceneComponent> component)
    {
        if (component == nullptr)
        {
            spdlog::error("AddComponent requires a non-null component.");
        }

        component->on_attach(*this);
        m_components.push_back(std::move(component));
        return *m_components.back();
    }

    bool SceneNode::remove_component(ISceneComponent& component)
    {
        for (size_t i = 0; i < m_components.size(); ++i)
        {
            if (m_components[i].get() == &component)
            {
                m_components[i]->on_detach();
                m_components.erase(m_components.begin() + static_cast<long>(i));
                return true;
            }
        }

        return false;
    }

    void SceneNode::for_each_component(const std::function<void(ISceneComponent&)>& fn)
    {
        for (std::unique_ptr<ISceneComponent>& component : m_components)
        {
            fn(*component);
        }
    }

    void SceneNode::for_each_component(const std::function<void(const ISceneComponent&)>& fn) const
    {
        for (const std::unique_ptr<ISceneComponent>& component : m_components)
        {
            fn(*component);
        }
    }

    void SceneNode::set_parent_internal(SceneNode* parent)
    {
        m_parent = parent;
    }
}