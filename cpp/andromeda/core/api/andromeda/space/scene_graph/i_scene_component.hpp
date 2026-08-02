#ifndef API__SPACE__SCENE__I_SCENE_COMPONENT__HPP
#define API__SPACE__SCENE__I_SCENE_COMPONENT__HPP


namespace andromeda
{
    class ISceneNode;

    /// @brief Defines the interface for a scene component.
    ///
    /// A scene component can be attached to or detached from a scene node,
    /// allowing it to participate in the node's behavior.
    class ISceneComponent
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ISceneComponent() = default;

        /// @brief Called when the component is attached to a scene node.
        ///
        /// @param node Scene node the component is attached to.
        virtual void on_attach(ISceneNode& node) = 0;

        /// @brief Called when the component is detached from its scene node.
        virtual void on_detach() = 0;
    };
}


#endif // API__SPACE__SCENE__I_SCENE_COMPONENT__HPP