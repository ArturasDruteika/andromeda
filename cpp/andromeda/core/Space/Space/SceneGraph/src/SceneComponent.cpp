#include "../include/SceneComponent.hpp"
#include "andromeda/space/scene_graph/i_scene_node.hpp"


namespace andromeda::Space
{
    SceneComponent::SceneComponent()
        : m_node{ nullptr }
    {
	}

    SceneComponent::~SceneComponent() = default;

    void SceneComponent::OnAttach(ISceneNode& node)
    {
        m_node = &node;
    }

    void SceneComponent::OnDetach()
    {
        m_node = nullptr;
    }
}
