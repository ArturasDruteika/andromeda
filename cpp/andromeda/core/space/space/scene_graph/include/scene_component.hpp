#ifndef API__SPACE__SCENE__SCENE_COMPONENT__HPP
#define API__SPACE__SCENE__SCENE_COMPONENT__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/scene_graph/i_scene_component.hpp"


namespace andromeda::space
{
    /// @brief Base implementation of a scene graph component.
    ///
    /// Provides default attach and detach behavior while maintaining a
    /// reference to the scene node that owns the component.
    class SPACE_API SceneComponent
        : public ISceneComponent
    {
    public:
        /// @brief Constructs a scene component.
        SceneComponent();

        /// @brief Destroys the scene component.
        ~SceneComponent() override;

        /// @brief Attaches the component to a scene node.
        ///
        /// @param node Scene node that will own the component.
        void on_attach(ISceneNode& node) override;

        /// @brief Detaches the component from its owning scene node.
        void on_detach() override;

    private:
        /// @brief Pointer to the owning scene node.
        ISceneNode* m_node;
    };
}

#endif // API__SPACE__SCENE__SCENE_COMPONENT__HPP