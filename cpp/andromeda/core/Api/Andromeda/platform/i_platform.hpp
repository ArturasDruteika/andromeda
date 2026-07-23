#ifndef API__PLATFORM__I_PLATFORM__HPP
#define API__PLATFORM__I_PLATFORM__HPP


#include "../MacroExports/MacroExports.hpp"
#include "../Components/GraphicsBackend.hpp"
#include "../GraphicsContext/IGraphicsContext.hpp"
#include "../Window/Window/IWindow.hpp"
#include <memory>
#include <string>


namespace Andromeda
{
	class IPlatform
	{
	public:
		virtual ~IPlatform() = default;

		virtual bool is_initialized() const = 0;
		virtual GraphicsBackend get_graphics_backend() const = 0;
		virtual bool init(int width, int height, const std::string& title) = 0;
        virtual void shutdown() = 0;
        virtual IGraphicsContext* get_graphics_context() const = 0;
        virtual IWindow* get_window() const = 0;
	};

	ANDROMEDA_API std::unique_ptr<IPlatform> CreatePlatform(const GraphicsBackend& graphics_backend);
}


#endif // API__PLATFORM__I_PLATFORM__HPP