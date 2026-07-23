#ifndef API__SPACE__SCENE__I_SCENE_NODE__HPP
#define API__SPACE__SCENE__I_SCENE_NODE__HPP


#include "../transformations/i_transformable.hpp"

#include <functional>
#include <memory>


namespace Andromeda
{
    class ISceneComponent;

    class ISceneNode
    {
    public:
        virtual ~ISceneNode() = default;

        // Transform
        virtual ITransformable& get_transform() = 0;
        virtual const ITransformable& get_transform() const = 0;

        // Hierarchy
        virtual ISceneNode* get_parent() const = 0;

        virtual void attach_child(std::unique_ptr<ISceneNode> child) = 0;
        virtual std::unique_ptr<ISceneNode> detach_child(ISceneNode& child) = 0;

        virtual void for_each_child(const std::function<void(ISceneNode&)>& fn) = 0;
        virtual void for_each_child(const std::function<void(const ISceneNode&)>& fn) const = 0;

        // Components
        virtual ISceneComponent& add_component(std::unique_ptr<ISceneComponent> component) = 0;
        virtual bool remove_component(ISceneComponent& component) = 0;

        virtual void for_each_component(const std::function<void(ISceneComponent&)>& fn) = 0;
        virtual void for_each_component(const std::function<void(const ISceneComponent&)>& fn) const = 0;
    };
}

#endif // API__SPACE__SCENE__I_SCENE_NODE__HPP