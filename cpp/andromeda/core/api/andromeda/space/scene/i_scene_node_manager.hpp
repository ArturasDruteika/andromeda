#ifndef API__SCENE__I_SCENE_NODE_MANAGER__HPP
#define API__SCENE__I_SCENE_NODE_MANAGER__HPP


#include "andromeda/space/scene/i_scene_lighting.hpp"
#include "andromeda/space/scene/i_scene_objects.hpp"
#include "andromeda/space/scene_graph/i_scene_node.hpp"

#include <memory>


namespace andromeda
{
    /// @brief Defines the interface for managing scene nodes.
    ///
    /// Combines scene object and lighting management with the ability to attach
    /// nodes to the scene graph.
    class ISceneNodeManager
        : public virtual ISceneObjects
        , public virtual ISceneLighting
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ISceneNodeManager() = default;

        /// @brief Attaches a node to the scene graph.
        ///
        /// Ownership of the node is transferred to the scene manager.
        ///
        /// @param node Unique pointer to the scene node to attach.
        virtual void attach_node(std::unique_ptr<ISceneNode> node) = 0;
    };
}


#endif // API__SCENE__I_SCENE_NODE_MANAGER__HPP