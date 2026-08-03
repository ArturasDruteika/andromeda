#pragma once


#include "i_rotatable.hpp"
#include "i_scalable.hpp"
#include "i_translatable.hpp"
#include "math/linear_algebra/include/linear_algebra_data_types.hpp"


namespace andromeda
{
    /// @brief Defines the interface for a transformable object.
    ///
    /// Combines translation, rotation, and scaling capabilities into a single
    /// interface and provides access to the resulting model transformation.
    class ITransformable
        : public virtual IRotatable
        , public virtual IScalable
        , public virtual ITranslatable
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ITransformable() = default;

        // Getters

        /// @brief Checks whether the transformation state has changed.
        ///
        /// @return `true` if any transformation component has changed since the
        /// last reset; otherwise, `false`.
        virtual bool state_changed() const = 0;

        /// @brief Retrieves the model transformation matrix.
        ///
        /// @return The current model transformation matrix.
        virtual math::Mat4 get_model_matrix() = 0;

        // Setters

        /// @brief Sets the model transformation matrix.
        ///
        /// @param model_matrix Model transformation matrix.
        virtual void set_model_matrix(const math::Mat4& model_matrix) = 0;

        /// @brief Updates the model transformation matrix.
        ///
        /// Recomputes the model matrix from the current translation, rotation,
        /// and scale.
        virtual void update_model_matrix() = 0;

        /// @brief Resets the transformation change state.
        virtual void reset_state() = 0;
    };
}
