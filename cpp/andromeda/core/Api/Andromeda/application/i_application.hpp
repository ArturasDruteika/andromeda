#ifndef API__APPLICATION__I_APPLICATION__HPP
#define API__APPLICATION__I_APPLICATION__HPP


#include "../Components/GraphicsBackend.hpp"
#include "../MacroExports/MacroExports.hpp"
#include "../Renderer/IRenderer.hpp"
#include "../Space/Scene/IScene.hpp"

#include <memory>


namespace Andromeda
{
    class IApplication
    {
    public:
        virtual ~IApplication() = default;

        // Getters
        virtual IRenderer* get_renderer() = 0;

        virtual bool init(unsigned int width, unsigned int height, const std::string& title) = 0;
        virtual void de_init() = 0;

        virtual void set_scene(IScene* p_scene) = 0;
        virtual int run() = 0;
    };

    ANDROMEDA_API std::unique_ptr<IApplication> CreateApp(const GraphicsBackend& graphics_backend);
}

#endif // API__APPLICATION__I_APPLICATION__HPP
