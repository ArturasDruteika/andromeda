#ifndef API__SPACE__SCENE__SCENE_COMPONENT__HPP
#define API__SPACE__SCENE__SCENE_COMPONENT__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/space/scene_graph/i_scene_component.hpp"


namespace andromeda::space
{
    class SPACE_API SceneComponent
        : public ISceneComponent
    {
    public:
        SceneComponent();
        ~SceneComponent() override;

        void on_attach(ISceneNode& node) override;
        void on_detach() override;

    private:
        ISceneNode* m_node;
    };
}

#endif // API__SPACE__SCENE__SCENE_COMPONENT__HPP