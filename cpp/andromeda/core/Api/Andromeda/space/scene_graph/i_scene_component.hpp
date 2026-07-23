#ifndef API__SPACE__SCENE__I_SCENE_COMPONENT__HPP
#define API__SPACE__SCENE__I_SCENE_COMPONENT__HPP


namespace Andromeda
{
    class ISceneNode;

    class ISceneComponent
    {
    public:
        virtual ~ISceneComponent() = default;

        virtual void on_attach(ISceneNode& node) = 0;
        virtual void on_detach() = 0;
    };
}

#endif // API__SPACE__SCENE__I_SCENE_COMPONENT__HPP