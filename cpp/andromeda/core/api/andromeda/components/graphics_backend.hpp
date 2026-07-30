#ifndef API__ENGINE__GRAPHICS_BACKEND__HPP
#define API__ENGINE__GRAPHICS_BACKEND__HPP


#include <string_view>


namespace andromeda
{
    /// @brief Enumerates the graphics APIs supported by the engine.
    enum class GraphicsBackend : int
    {
        /// @brief No graphics backend selected.
        None = 0,

        /// @brief OpenGL graphics backend.
        OpenGL = 1,

        /// @brief Vulkan graphics backend.
        Vulkan = 2
    };

    /// @brief Converts a graphics backend to its string representation.
    ///
    /// @param backend Graphics backend to convert.
    /// @return A string view containing the backend name, or `"Unknown"` if the
    ///         value is not recognized.
    constexpr std::string_view graphics_backend_string(const GraphicsBackend& backend) noexcept
    {
        switch (backend)
        {
            case GraphicsBackend::None:   return "None";
            case GraphicsBackend::OpenGL: return "OpenGL";
            case GraphicsBackend::Vulkan: return "Vulkan";
            default:                      return "Unknown";
        }
    }
}

#endif // API__ENGINE__GRAPHICS_BACKEND__HPP