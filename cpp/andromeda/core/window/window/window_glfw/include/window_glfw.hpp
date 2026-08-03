#pragma once


#include "andromeda/window/events/i_event.hpp"
#include "andromeda/window/window/i_window.hpp"
#include "pch.hpp"
#include "GLFW/glfw3.h"


/// @brief Default application window width in pixels.
constexpr int DEFAULT_WINDOW_WIDTH = 640;

/// @brief Default application window height in pixels.
constexpr int DEFAULT_WINDOW_HEIGHT = 640;


namespace andromeda::window
{
	/// @brief GLFW implementation of the window interface.
	///
	/// Manages a GLFW window, dispatches window and input events, and exposes
	/// the native window handle required by graphics APIs.
	class WindowGLFW
		: public IWindow
	{
	public:
		/// @brief Callback function type used for window and input events.
		using event_callback_fn = std::function<void(IEvent&)>;

		/// @brief Constructs a GLFW window.
		///
		/// @param width Initial window width in pixels.
		/// @param height Initial window height in pixels.
		/// @param title Initial window title.
		/// @param init_window `true` to initialize the window immediately;
		/// otherwise, `false`.
		WindowGLFW(
			int width = DEFAULT_WINDOW_WIDTH,
			int height = DEFAULT_WINDOW_HEIGHT,
			const std::string& title = "Andromeda Window",
			bool init_window = true
		);

		/// @brief Destroys the GLFW window.
		~WindowGLFW() override;

		/// @brief Checks whether the window has been initialized.
		///
		/// @return `true` if the window is initialized; otherwise, `false`.
		bool is_initialized() const override;

		/// @brief Retrieves the window width.
		///
		/// @return Window width in pixels.
		unsigned int get_width() const override;

		/// @brief Retrieves the window height.
		///
		/// @return Window height in pixels.
		unsigned int get_height() const override;

		/// @brief Retrieves the window title.
		///
		/// @return Window title.
		std::string get_title() const override;

		/// @brief Sets the window title.
		///
		/// @param title New window title.
		void set_title(const std::string& title) override;

		/// @brief Processes pending GLFW events.
		virtual void poll_events() override;

		/// @brief Checks whether the window should close.
		///
		/// @return `true` if a close request has been received; otherwise,
		/// `false`.
		virtual bool should_close() const override;

		/// @brief Retrieves the native GLFW window handle.
		///
		/// @return Pointer to the native GLFW window.
		virtual void* get_native_handle() const override;

		/// @brief Sets the event callback function.
		///
		/// @param callback Callback invoked for generated window and input events.
		void set_event_callback(const event_callback_fn& callback) override;

		/// @brief Retrieves the GLFW window handle.
		///
		/// @return Pointer to the GLFW window.
		GLFWwindow* get_window() const;

		/// @brief Initializes GLFW and creates the window.
		void init();

		/// @brief Deinitializes the window and releases GLFW resources.
		void de_init();

		/// @brief Creates a new GLFW window.
		void create_new_window();

		/// @brief Registers GLFW callback functions.
		void set_callback_functions();

	private:
		// GLFW Callbacks

		/// @brief Handles GLFW window resize callbacks.
		///
		/// @param window GLFW window that generated the callback.
		/// @param width New window width in pixels.
		/// @param height New window height in pixels.
		static void resize_window(GLFWwindow* window, int width, int height);

		/// @brief Handles GLFW window close callbacks.
		///
		/// @param window GLFW window that generated the callback.
		static void window_close(GLFWwindow* window);

		/// @brief Handles GLFW keyboard callbacks.
		///
		/// @param window GLFW window that generated the callback.
		/// @param key Keyboard key code.
		/// @param scancode Platform-specific key scancode.
		/// @param action Key action.
		/// @param mods Modifier key flags.
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		/// @brief Handles GLFW mouse button callbacks.
		///
		/// @param window GLFW window that generated the callback.
		/// @param button Mouse button code.
		/// @param action Button action.
		/// @param mods Modifier key flags.
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

		/// @brief Handles GLFW mouse scroll callbacks.
		///
		/// @param window GLFW window that generated the callback.
		/// @param x_offset Horizontal scroll offset.
		/// @param y_offset Vertical scroll offset.
		static void mouse_scroll_callback(GLFWwindow* window, double x_offset, double y_offset);

		/// @brief Handles GLFW mouse movement callbacks.
		///
		/// @param window GLFW window that generated the callback.
		/// @param x_pos Cursor X-coordinate.
		/// @param y_pos Cursor Y-coordinate.
		static void mouse_move_callback(GLFWwindow* window, double x_pos, double y_pos);

	private:
		/// @brief Indicates whether the window has been initialized.
		bool m_is_initialized;

		/// @brief Current window width and height in pixels.
		int m_width, m_height;

		/// @brief Current window title.
		std::string m_title;

		/// @brief Callback used to dispatch window and input events.
		event_callback_fn m_event_callback;

		/// @brief Native GLFW window handle.
		GLFWwindow* m_window;
	};
}
