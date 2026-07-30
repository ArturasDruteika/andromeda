#ifndef ANDROMEDA__LIGHT__LIGHT_TYPES__HPP
#define ANDROMEDA__LIGHT__LIGHT_TYPES__HPP


namespace andromeda
{
    /// @brief Enumerates the supported light source types.
    enum class LightType : int
    {
        /// @brief No light type.
        None = 0,

        /// @brief Directional light with parallel light rays.
        Directional = 1,

        /// @brief Point light emitting in all directions from a position.
        Point = 2,

        /// @brief Spot light emitting within a cone.
        Spot = 3
    };
}


#endif // ANDROMEDA__LIGHT__LIGHT_TYPES__HPP