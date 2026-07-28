#include "../include/scene_component.hpp"
#include "andromeda/space/scene_graph/i_scene_node.hpp"


namespace andromeda::space
{
    SceneComponent::SceneComponent()
        : m_node{ nullptr }
    {
    }

    SceneComponent::~SceneComponent() = default;

    void SceneComponent::on_attach(ISceneNode& node)
    {
        m_node = &node;
    }

    void SceneComponent::on_detach()
    {
        m_node = nullptr;
    }
}