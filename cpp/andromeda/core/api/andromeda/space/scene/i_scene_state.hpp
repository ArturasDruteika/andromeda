#ifndef API__SCENE__I_SCENE_STATE__HPP
#define API__SCENE__I_SCENE_STATE__HPP


#include "../objects/i_geometric_object.hpp"


namespace andromeda
{
    /// @brief Defines the interface for tracking scene state changes.
    ///
    /// A scene state implementation determines whether the state of a
    /// collection of scene objects has changed since the last evaluation.
    class ISceneState
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ISceneState() = default;

        /// @brief Checks whether the scene state has changed.
        ///
        /// @param objects Map of scene objects indexed by object ID.
        /// @return `true` if the scene state has changed; otherwise, `false`.
        virtual bool state_changed(const std::unordered_map<int, IGeometricObject*>& objects) const = 0;
    };
}


#endif // API__SCENE__I_SCENE_STATE__HPP