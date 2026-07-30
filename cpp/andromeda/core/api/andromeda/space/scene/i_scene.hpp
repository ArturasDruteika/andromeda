#ifndef API__SCENE__I_SCENE__HPP
#define API__SCENE__I_SCENE__HPP


#include "i_camera_handler.hpp"
#include "i_scene_environment.hpp"
#include "i_scene_node_manager.hpp"
#include "i_scene_state.hpp"


namespace andromeda
{
    /// @brief Defines the interface for a scene.
    ///
    /// A scene manages cameras, scene objects, lighting, environment settings,
    /// and scene state. It also provides lifecycle operations for updating and
    /// clearing the scene.
    class IScene
        : public virtual ICameraHandler
        , public virtual ISceneEnvironment
        , public virtual ISceneNodeManager
        , public virtual ISceneState
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IScene() = default;

        // Getters

        /// @brief Retrieves the center of the scene.
        ///
        /// @return Reference to the scene center in world space.
        virtual const math::Vec3& get_scene_center() const = 0;

        // Operations

        /// @brief Removes all objects and lights from the scene.
        virtual void clear_scene() = 0;

        /// @brief Resets the tracked scene state.
        ///
        /// After calling this function, the current scene becomes the new
        /// baseline for subsequent state change detection.
        virtual void reset_scene_state() = 0;

        /// @brief Updates the scene.
        ///
        /// Performs per-frame updates such as animations, transformations,
        /// and other time-dependent processing.
        ///
        /// @param delta_time Elapsed time since the previous update, in seconds.
        virtual void update(float delta_time) = 0;
    };
}


#endif // API__SCENE__I_SCENE__HPP