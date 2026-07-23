#ifndef ENGINECORE__ENGINE__HPP
#define ENGINECORE__ENGINE__HPP


#include "../../macro_exports/include/macro_exports.hpp"
#include "andromeda/components/graphics_backend.hpp"
#include "andromeda/engine/i_engine.hpp"

#include "pch.hpp"


namespace andromeda::engine
{
    class ENGINECORE_API Engine
        : public IEngine
    {
    public:
        Engine(const GraphicsBackend& graphics_backend);
        ~Engine() override;

        bool is_initialized() const override;
        GraphicsBackend get_graphics_backend() const override;
        IRenderer* get_renderer() const override;

        bool init() override;
        void de_init() override;

        void on_event(IEvent& event) override;

        // New: engine needs scene access to reach active camera
        void set_scene(IScene* p_scene);

    private:
        void create_renderer();
        void destroy_renderer();

        void handle_mouse_scrolled(IEvent& event);
        void handle_mouse_button_pressed(IEvent& event);
        void handle_mouse_button_released(IEvent& event);
        void handle_key_pressed(IEvent& event);
        void handle_key_released(IEvent& event);
        void handle_mouse_moved(IEvent& event);
        void handle_window_resize(IEvent& event);
        void handle_window_close(IEvent& event);
        void handle_framebuffer_resize(IEvent& event);

    private:
        bool m_initialized;
        GraphicsBackend m_graphics_backend;
        std::unique_ptr<IRenderer> m_renderer;

        IScene* m_p_scene;

        // Input state
        bool m_is_left_mouse_down;
        bool m_is_ctrl_down;
        bool m_has_last_mouse_pos;
        float m_last_mouse_x;
        float m_last_mouse_y;

        // Tunables
        float m_mouse_yaw_sensitivity;
        float m_mouse_pitch_sensitivity;
        float m_mouse_roll_sensitivity;
        float m_scroll_zoom_sensitivity;
    };
}


#endif // ENGINECORE__ENGINE__HPP