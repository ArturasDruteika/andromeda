#ifndef API__SPACE__TRANSFORMATIONS__I_TRANSLATABLE__HPP
#define API__SPACE__TRANSFORMATIONS__I_TRANSLATABLE__HPP


#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda
{
    /// @brief Defines the interface for a translatable object.
    ///
    /// Provides access to an object's position and translation matrix, along
    /// with operations for modifying its position.
    class ITranslatable
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ITranslatable() = default;

        // Getters

        /// @brief Checks whether the translation state has changed.
        ///
        /// @return `true` if the position has changed since the last reset;
        /// otherwise, `false`.
        virtual bool state_changed() const = 0;

        /// @brief Retrieves the current position.
        ///
        /// @return Reference to the position in world space.
        virtual const math::Vec3& get_position() const = 0;

        /// @brief Retrieves the translation matrix.
        ///
        /// @return Reference to the translation transformation matrix.
        virtual const math::Mat4& get_translation_matrix() const = 0;

        // Setters

        /// @brief Resets the translation change state.
        virtual void reset_state() = 0;

        /// @brief Sets the object position.
        ///
        /// @param position New position in world space.
        virtual void set_position(const math::Vec3& position) = 0;

        /// @brief Applies a translation to the object.
        ///
        /// @param translation Translation offset in world space.
        virtual void translate(const math::Vec3& translation) = 0;
    };
}


#endif // API__SPACE__TRANSFORMATIONS__I_TRANSLATABLE__HPP