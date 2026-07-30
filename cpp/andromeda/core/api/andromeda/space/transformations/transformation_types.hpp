#ifndef API__SPACE__TRANSFORMATIONS__TRANSFORMATION_TYPES__HPP
#define API__SPACE__TRANSFORMATIONS__TRANSFORMATION_TYPES__HPP


namespace andromeda
{
    /// @brief Enumerates the supported transformation types.
    enum class TransformationType
    {
        /// @brief Translation transformation.
        Translation,

        /// @brief Rotation transformation.
        Rotation,

        /// @brief Scale transformation.
        Scale,

        /// @brief All transformation types.
        All
    };
}


#endif // API__SPACE__TRANSFORMATIONS__TRANSFORMATION_TYPES__HPP