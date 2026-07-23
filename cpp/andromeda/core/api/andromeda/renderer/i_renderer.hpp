#ifndef API__RENDERER__I_RENDERER__HPP
#define API__RENDERER__I_RENDERER__HPP


#include "i_grid_control.hpp"
#include "i_illumination_control.hpp"
#include "i_size_control.hpp"
#include "../space/scene/i_scene.hpp"
#include "../macro_exports/macro_exports.hpp"
#include "../components/graphics_backend.hpp"


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