#ifndef API__RENDERER__I_RENDERER__HPP
#define API__RENDERER__I_RENDERER__HPP


#include "IGridControl.hpp"
#include "IIlluminationControl.hpp"
#include "ISizeControl.hpp"
#include "../Space/Scene/IScene.hpp"
#include "../MacroExports/MacroExports.hpp"
#include "../Components/GraphicsBackend.hpp"


namespace Andromeda
{
	class IRenderer 
		: public IGridControl
		, public IIlluminationControl
		, public ISizeControl
	{
	public:
		virtual ~IRenderer() = default;

		// Getters
		virtual bool is_initialized() const = 0;
		virtual void* get_frame_texture_handle() const = 0;

		virtual void init(int width, int height, bool illumination_mode = false) = 0;
		virtual void de_init() = 0;
		virtual void render_frame(IScene& scene) = 0;
	};

	ANDROMEDA_API std::unique_ptr<IRenderer> CreateRenderer(const GraphicsBackend& graphics_backend);
}


#endif // API__RENDERER__I_RENDERER__HPP