#pragma once


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/components/graphics_backend.hpp"
#include "andromeda/engine/i_engine.hpp"

#include "pch.hpp"


namespace andromeda::engine
{
    /// @brief Default implementation of the engine interface.
    ///
    /// Manages the renderer, processes application and input events, and
    /// coordinates interactions between the renderer and the active scene.
    class ENGINECORE_API Engine
        : public IEngine
    {
    public:
        /// @brief Constructs an engine for the specified graphics backend.
        ///
        /// @param graphics_backend Graphics backend to use.
        Engine(const GraphicsBackend& graphics_backend);

        /// @brief Destroys the engine.
        ~Engine() override;

        // Getters

        /// @brief Checks whether the engine has been initialized.
        ///
        /// @return `true` if the engine is initialized; otherwise, `false`.
        bool is_initialized() const override;

        /// @brief Retrieves the graphics backend used by the engine.
        ///
        /// @return Active graphics backend.
        GraphicsBackend get_graphics_backend() const override;

        /// @brief Retrieves the engine renderer.
        ///
        /// @return Pointer to the renderer instance.
        IRenderer* get_renderer() const override;

        /// @brief Initializes the engine.
        ///
        /// @return `true` if initialization succeeded; otherwise, `false`.
        bool init() override;

        /// @brief Shuts down the engine.
        void de_init() override;

        /// @brief Processes an application or input event.
        ///
        /// @param event Event to process.
        void on_event(IEvent& event) override;

        /// @brief Sets the active scene.
        ///
        /// The engine uses the active scene to access objects such as the
        /// currently active camera.
        ///
        /// @param p_scene Pointer to the active scene.
        void set_scene(IScene* p_scene);

    private:
        /// @brief Creates the renderer instance.
        void create_renderer();

        /// @brief Destroys the renderer instance.
        void destroy_renderer();

        /// @brief Handles a mouse wheel scroll event.
        void handle_mouse_scrolled(IEvent& event);

        /// @brief Handles a mouse button press event.
        void handle_mouse_button_pressed(IEvent& event);

        /// @brief Handles a mouse button release event.
        void handle_mouse_button_released(IEvent& event);

        /// @brief Handles a key press event.
        void handle_key_pressed(IEvent& event);

        /// @brief Handles a key release event.
        void handle_key_released(IEvent& event);

        /// @brief Handles a mouse movement event.
        void handle_mouse_moved(IEvent& event);

        /// @brief Handles a window resize event.
        void handle_window_resize(IEvent& event);

        /// @brief Handles a window close event.
        void handle_window_close(IEvent& event);

        /// @brief Handles a framebuffer resize event.
        void handle_framebuffer_resize(IEvent& event);

    private:
        /// @brief Indicates whether the engine has been initialized.
        bool m_initialized;

        /// @brief Selected graphics backend.
        GraphicsBackend m_graphics_backend;

        /// @brief Owned renderer instance.
        std::unique_ptr<IRenderer> m_renderer;

        /// @brief Active scene.
        IScene* m_p_scene;

        // Input state

        /// @brief Indicates whether the left mouse button is pressed.
        bool m_is_left_mouse_down;

        /// @brief Indicates whether the Control key is pressed.
        bool m_is_ctrl_down;

        /// @brief Indicates whether a previous mouse position is available.
        bool m_has_last_mouse_pos;

        /// @brief Previous mouse X position.
        float m_last_mouse_x;

        /// @brief Previous mouse Y position.
        float m_last_mouse_y;

        // Tunables

        /// @brief Mouse yaw sensitivity.
        float m_mouse_yaw_sensitivity;

        /// @brief Mouse pitch sensitivity.
        float m_mouse_pitch_sensitivity;

        /// @brief Mouse roll sensitivity.
        float m_mouse_roll_sensitivity;

        /// @brief Mouse wheel zoom sensitivity.
        float m_scroll_zoom_sensitivity;
    };
}
