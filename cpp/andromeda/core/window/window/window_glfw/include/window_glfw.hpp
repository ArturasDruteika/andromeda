#ifndef WINDOW__GLFW_WINDOW__HPP_HPP
#define WINDOW__GLFW_WINDOW__HPP_HPP


#include "andromeda/window/events/i_event.hpp"
#include "andromeda/window/window/i_window.hpp"
#include "pch.hpp"
#include "GLFW/glfw3.h"


constexpr int DEFAULT_WINDOW_WIDTH = 640;
constexpr int DEFAULT_WINDOW_HEIGHT = 640;


namespace andromeda::window
{
	class WindowGLFW
		: public IWindow
	{
	public:
		using event_callback_fn = std::function<void(IEvent&)>;

		WindowGLFW(
			int width = DEFAULT_WINDOW_WIDTH,
			int height = DEFAULT_WINDOW_HEIGHT,
			const std::string& title = "andromeda Window",
			bool init_window = true
		);
		~WindowGLFW() override;

		bool is_initialized() const override;
		unsigned int get_width() const override;
		unsigned int get_height() const override;
		std::string get_title() const override;
		void set_title(const std::string& title) override;
		virtual void poll_events() override;
		virtual bool should_close() const override;
		virtual void* get_native_handle() const override;
		void set_event_callback(const event_callback_fn& callback) override;

		GLFWwindow* get_window() const;

		void init();
		void de_init();
		void create_new_window();
		void set_callback_functions();

	private:
		// GLFW Callbacks
		static void resize_window(GLFWwindow* window, int width, int height);
		static void window_close(GLFWwindow* window);
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void mouse_scroll_callback(GLFWwindow* window, double x_offset, double y_offset);
		static void mouse_move_callback(GLFWwindow* window, double x_pos, double y_pos);

	private:
		bool m_is_initialized;
		int m_width, m_height;
		std::string m_title;
		event_callback_fn m_event_callback;
		GLFWwindow* m_window;
	};
}


#endif // WINDOW__GLFW_WINDOW__HPP_HPP