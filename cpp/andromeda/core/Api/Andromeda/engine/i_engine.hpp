#ifndef API__ENGINE__I_ENGINE__HPP
#define API__ENGINE__I_ENGINE__HPP


#include "../MacroExports/MacroExports.hpp"
#include "../Components/GraphicsBackend.hpp"
#include "../Renderer/IRenderer.hpp"
#include "../Space/Scene/IScene.hpp"
#include "Andromeda/window/events/i_event.hpp"
#include <memory>


namespace Andromeda
{
	class IEngine
	{
	public:
		virtual ~IEngine() = default;

			virtual bool is_initialized() const = 0;
			virtual GraphicsBackend get_graphics_backend() const = 0;
			virtual IRenderer* get_renderer() const = 0;

			virtual bool init() = 0;
			virtual void de_init() = 0;

			virtual void on_event(IEvent& event) = 0;
	};

	ANDROMEDA_API std::unique_ptr<IEngine> CreateEngine(const GraphicsBackend& graphics_backend);
}


#endif // API__ENGINE__I_ENGINE__HPP