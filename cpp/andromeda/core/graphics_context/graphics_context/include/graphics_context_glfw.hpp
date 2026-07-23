#ifndef CONTEXT__GLFW_CONTEXT__HPP
#define CONTEXT__GLFW_CONTEXT__HPP


#include "andromeda/graphics_context/IGraphicsContext.hpp"
#include "andromeda/window/window/i_window.hpp"

#include "GLFW/glfw3.h"


namespace andromeda::graphics_context
{
	class GraphicsContextGLFW
		: public IGraphicsContext
	{
	public:
		GraphicsContextGLFW();
		~GraphicsContextGLFW() override;

		GraphicsContextGLFW(const GraphicsContextGLFW& other) = delete;	// Prevent Copy Constructor
		GraphicsContextGLFW& operator=(const GraphicsContextGLFW& other) = delete;	// Prevent Copy assignment
		GraphicsContextGLFW(GraphicsContextGLFW&& other) noexcept = delete;	// Prevent Move constructor
		GraphicsContextGLFW& operator=(const GraphicsContextGLFW&& other) noexcept = delete;	// Prevent Move assignment

		bool is_initialized() const override;
		bool init(IWindow& window) override;
		void make_current() override;
		void present() override;
		void set_context_hints();

	private:
		bool load_glad();

	private:
		bool m_initialized;
		GLFWwindow* m_p_glfw_window;
	};
}


#endif // CONTEXT__GLFW_CONTEXT__HPP