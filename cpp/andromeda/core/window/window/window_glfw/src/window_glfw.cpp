#include "pch.hpp"
#include "../include/window_glfw.hpp"
#include "../../events/include/frame_buffer_events.hpp"
#include "../../events/include/key_events.hpp"
#include "../../events/include/mouse_events.hpp"
#include "spdlog/spdlog.h"


namespace andromeda::window
{
	WindowGLFW::WindowGLFW(int width, int height, const std::string& title, bool init_window)
		: m_width{ width }
		, m_height{ height }
		, m_title{ title }
		, m_window{ nullptr }
		, m_is_initialized{ false }
	{
		if (init_window)
		{
			init();
		}
	}

	WindowGLFW::~WindowGLFW()
	{
		de_init();
	}

	bool WindowGLFW::is_initialized() const
	{
		return m_is_initialized;
	}

	unsigned int WindowGLFW::get_width() const
	{
		return m_width;
	}

	unsigned int WindowGLFW::get_height() const
	{
		return m_height;
	}

	std::string WindowGLFW::get_title() const
	{
		return m_title;
	}

	void WindowGLFW::set_title(const std::string& title)
	{
		m_title = title;
	}

	void WindowGLFW::poll_events()
	{
		glfwPollEvents();
	}

	bool WindowGLFW::should_close() const
	{
		if (!m_window)
		{
			// If there is no window, treat it as "should close"
			return true;
		}

		return glfwWindowShouldClose(m_window) != 0;
	}

	void* WindowGLFW::get_native_handle() const
	{
		// This is what your GraphicsContextGLFW will cast back to GLFWwindow*
		return static_cast<void*>(m_window);
	}

	void WindowGLFW::init()
	{
		if (!m_is_initialized)
		{
			try
			{
				create_new_window();
				set_callback_functions();
				m_is_initialized = true;
			}
			catch (const std::exception& e)
			{
				spdlog::error("Initialization failed: {}", e.what());
				de_init();
			}
		}
	}

	void WindowGLFW::de_init()
	{
		if (m_is_initialized)
		{
			glfwDestroyWindow(m_window);
			m_is_initialized = false;
		}
	}

	void WindowGLFW::create_new_window()
	{
		m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

		if (!m_window)
		{
			spdlog::error("Failed to create GLFW window.");
			return;
		}

		// Associate this instance with the GLFW window
		glfwSetWindowUserPointer(m_window, this);
	}

	void WindowGLFW::set_callback_functions()
	{
		glfwSetFramebufferSizeCallback(m_window, resize_window);
		glfwSetWindowCloseCallback(m_window, window_close);
		glfwSetKeyCallback(m_window, key_callback);
		glfwSetMouseButtonCallback(m_window, mouse_button_callback);
		glfwSetScrollCallback(m_window, mouse_scroll_callback);
		glfwSetCursorPosCallback(m_window, mouse_move_callback);
	}

	GLFWwindow* WindowGLFW::get_window() const
	{
		return m_window;
	}

	void WindowGLFW::set_event_callback(const event_callback_fn& callback)
	{
		m_event_callback = callback;
	}

	void WindowGLFW::resize_window(GLFWwindow* window, int width, int height)
	{
		WindowGLFW* instance = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
		if (instance)
		{
			instance->m_width = width;
			instance->m_height = height;
			// spdlog::debug("Window resized to {}x{}", width, height);

			if (instance->m_event_callback)
			{
				WindowResizeEvent event(width, height);
				instance->m_event_callback(event);
			}
		}
	}

	void WindowGLFW::window_close(GLFWwindow* window)
	{
		WindowGLFW* instance = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
		if (instance)
		{
			// spdlog::debug("Window close event triggered.");
			if (instance->m_event_callback)
			{
				WindowCloseEvent event;
				instance->m_event_callback(event);
			}
		}
	}

	void WindowGLFW::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		WindowGLFW* instance = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
		if (instance)
		{
			if (instance->m_event_callback)
			{
				if (action == GLFW_PRESS || action == GLFW_REPEAT)
				{
					KeyPressedEvent event(static_cast<KeyCode>(key), action == GLFW_REPEAT);
					// spdlog::debug("Key Pressed: {} (Repeat: {})", key, action == GLFW_REPEAT);
					instance->m_event_callback(event);
				}
				else if (action == GLFW_RELEASE)
				{
					KeyReleasedEvent event(static_cast<KeyCode>(key));
					// spdlog::debug("Key Released: {}", key);
					instance->m_event_callback(event);
				}
			}
		}
	}

	void WindowGLFW::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		WindowGLFW* instance = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
		if (instance)
		{
			if (instance->m_event_callback)
			{
				if (action == GLFW_PRESS)
				{
					MouseButtonPressedEvent event(static_cast<MouseCode>(button));
					// spdlog::debug("Mouse Button Pressed: {}", button);
					instance->m_event_callback(event);
				}
				else if (action == GLFW_RELEASE)
				{
					MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
					// spdlog::debug("Mouse Button Released: {}", button);
					instance->m_event_callback(event);
				}
			}
		}
	}

	void WindowGLFW::mouse_scroll_callback(GLFWwindow* window, double x_offset, double y_offset)
	{
		WindowGLFW* instance = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
		if (instance)
		{
			if (instance->m_event_callback)
			{
				MouseScrolledEvent event(static_cast<float>(x_offset), static_cast<float>(y_offset));
				// spdlog::debug("Mouse Scrolled: X Offset = {}, Y Offset = {}", x_offset, y_offset);
				instance->m_event_callback(event);
			}
		}
	}

	void WindowGLFW::mouse_move_callback(GLFWwindow* window, double x_pos, double y_pos)
	{
		WindowGLFW* instance = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
		if (instance)
		{
			if (instance->m_event_callback)
			{
				MouseMovedEvent event(static_cast<float>(x_pos), static_cast<float>(y_pos));
				// spdlog::debug("Mouse Moved: X = {}, Y = {}", x_pos, y_pos);
				instance->m_event_callback(event);
			}
		}
	}
}